#include "../const.h"
#include "Server.h"

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <cassert>

using namespace std;

static void getDirectoryNameByFileName(char *szDest,	//出力先
								const char *szFileName)	//ファイル名
{
	int iSize = 0;	// '/'或いは'\'が最後に出たところ。

	for(int i = 0; szFileName[i] != '\0'; i++){
		if(szFileName[i] == '\\' || szFileName[i] == '/'){
			iSize = i;
		}
	}

	//後はコピー
	memcpy(szDest,szFileName,iSize);
	szDest[iSize] = '\0';

	return;
}

PROCESS_INFORMATION * CreateSuspendedProcess(const char *szTargetName)//ターゲットの名前
{
	//ディレクトリ名保存用
	char szDirectory[MAX_PATH];
	getDirectoryNameByFileName(szDirectory,szTargetName);
	//構造体の準備
	STARTUPINFO si = {0};
	PROCESS_INFORMATION *pi = (PROCESS_INFORMATION *)malloc(sizeof(PROCESS_INFORMATION));
	//プロセスの作成
	if(!CreateProcess(szTargetName,NULL,NULL,NULL,FALSE,CREATE_SUSPENDED | NORMAL_PRIORITY_CLASS ,
		NULL,(szDirectory[0] == '\0') ? NULL : szDirectory,&si,pi)){
		//setErrorStringEx("%s --- 見つかりませんでした。",szTargetName);
		return NULL;
	}

	return pi;
}

HANDLE DllInjection(PROCESS_INFORMATION *pi,	//プロセスの情報
								   const char *szDllName)//Dllファイル名
{

	HANDLE hProcess = pi->hProcess;

	//dllファイルの絶対パスを保存する変数
	TCHAR szLibFile[MAX_PATH];
	//dllファイルの絶対パスの文字列の長さ + 1(\0までの長さを保存する)
	int szLibFileLen;

	//もし相対パスなら、
	//自身の絶対パスの取得をして、dllまでの絶対パスを作る。
	//(例 X:/-----/--.... というパスは、1バイト目が':'なので、絶対パスとなる。)
	//絶対パスなら、そのままコピーするだけ。
	if(szDllName[1] != ':'){
		GetModuleFileName(NULL, szLibFile, sizeof(szLibFile));
		lstrcpy(_tcsrchr(szLibFile, '\\') + 1, szDllName);
	} else {
		lstrcpy(szLibFile,szDllName);
	}
	//長さ(使うメモリ領域)の計算
	szLibFileLen = lstrlen(szLibFile) + 1;
	szLibFileLen = szLibFileLen * sizeof(TCHAR);

	//プロセス内にメモリ領域の確保
	LPSTR RemoteProcessMemory;
	RemoteProcessMemory = (LPSTR)VirtualAllocEx( hProcess, NULL, szLibFileLen, MEM_COMMIT, PAGE_READWRITE);
	if(RemoteProcessMemory == NULL){
		//MessageBox(NULL,"プロセス内にメモリが確保できませんでした。","",0);
		return NULL;  
	}

	//書き込み
	if(WriteProcessMemory(hProcess, RemoteProcessMemory, (PVOID)szLibFile, szLibFileLen, NULL) == 0){
		//MessageBox(NULL,"プロセスに書き込みができませんでした。","",0);
		return NULL;
	}

	//LoadLibraryW関数が始まるポインタの取得
	PTHREAD_START_ROUTINE pfnThreadRtn; 
	pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress( GetModuleHandle(_TEXT("Kernel32")), "LoadLibraryA");
	if (pfnThreadRtn == NULL){
		//MessageBox(NULL,"LoadLibraryが見つかりませんでした。","",0);
		return NULL;  
	}

	//スレッド作成
	HANDLE hThread;
	hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, RemoteProcessMemory,CREATE_SUSPENDED, NULL);
	if (hThread == NULL){
		MessageBox(NULL,"スレッドが作れませんでした。","",0);
		return NULL;
	}

	//スレッド実行
	ResumeThread(hThread);
	BYTE *modulePointer = (BYTE *)WaitForSingleObject(hThread,INFINITE);
	DWORD dwExitCode;	//終了コード
	GetExitCodeThread(hThread,&dwExitCode);
	CloseHandle(hThread);	//スレッドを閉じる
	
	//プロセス内に確保したメモリの開放
	VirtualFreeEx(hProcess,RemoteProcessMemory,260,MEM_DECOMMIT);

	return (HANDLE)dwExitCode;
}

bool __stdcall ExecuteRemoteProcess(HANDLE hProcess,	//プロセスのハンドル
									PTHREAD_START_ROUTINE pRemoteThreadAddress,	//リモートプロセス内関数のアドレス
									LPVOID lpParam,	//自身のプロセス内での、値の入ったアドレス
									DWORD size,		//パラメータのサイズ
									DWORD *pExitCode)	//終了コード保存場所	NULLだと保存しない
{

	//終了コードの初期化
	if(pExitCode) pExitCode= 0;

	//プロセス内にメモリ領域の確保
	LPSTR RemoteProcessMemory;
	RemoteProcessMemory = (LPSTR)VirtualAllocEx( hProcess, NULL, size, MEM_COMMIT, PAGE_READWRITE);
	if(RemoteProcessMemory == NULL){
		//setErrorString("プロセス内にメモリが確保できませんでした。");
		return false;  
	}
	//書き込み
	if(WriteProcessMemory(hProcess, RemoteProcessMemory, lpParam, size, NULL) == 0){
		//setErrorString("プロセスに書き込みができませんでした。");
		return false;
	} 
 
	//スレッド作成
	HANDLE hThread;
	hThread = CreateRemoteThread(hProcess, NULL, 0, pRemoteThreadAddress, RemoteProcessMemory,CREATE_SUSPENDED, NULL);
	if (hThread == NULL){
		//setErrorString("スレッドが作れませんでした。");
		return false;
	}

	//スレッド実行
	ResumeThread(hThread);
	BYTE *modulePointer = (BYTE *)WaitForSingleObject(hThread,INFINITE);
	if(pExitCode){
		GetExitCodeThread(hThread,pExitCode);
	}
	CloseHandle(hThread);	//スレッドを閉じる
	
	//プロセス内に確保したメモリの開放
	VirtualFreeEx(hProcess,RemoteProcessMemory,size,MEM_DECOMMIT);

	return true;
}


bool CallThreadStartRoutin(HANDLE hProcess,const char* func_name,void *remote_dll_pointer,void *arg,int arg_size,DWORD *ret = NULL){
	HMODULE hMyModule = GetModuleHandle(MY_DLL_NAME);
	FARPROC pfunc = GetProcAddress(hMyModule,func_name);

	//リモートプロセス内での、DLLのモジュールのアドレスから、リモートプロセス内の関数の場所を特定、呼び出し。
	LPTHREAD_START_ROUTINE lpRemoteFunc = (LPTHREAD_START_ROUTINE)((DWORD)pfunc - (DWORD)hMyModule + (DWORD)remote_dll_pointer);
		
	DWORD remote_ret;
	bool succeed = ExecuteRemoteProcess(hProcess,lpRemoteFunc,arg,arg_size,&remote_ret);
	if(ret) *ret = remote_ret;

	return succeed;
}

RemoteClientInitializer::RemoteClientInitializer(const string& dll_path,const string& target_path) : 
	m_DllPath(dll_path),m_TargetPath(target_path),m_pi(NULL)
{
}

RemoteClientInitializer::~RemoteClientInitializer(){

	if(m_pi != NULL){
		//スレッドを閉じる
		CloseHandle(m_pi->hThread);
		//プロセスを閉じる
		CloseHandle(m_pi->hProcess);
		//開放
		free(m_pi);
		m_pi = NULL;
	}
}

//クライアントプロセスの作成
bool RemoteClientInitializer::CreateClientProcess(){
	assert(m_pi == NULL);

	m_pi = CreateSuspendedProcess(m_TargetPath.c_str());
	return m_pi != NULL;
}

//dll injectionを行う
bool RemoteClientInitializer::Injection(){
	assert(m_pi != NULL);

	m_RemoteDllPointer = DllInjection(m_pi,m_DllPath.c_str());
	return m_RemoteDllPointer != NULL;

}

void RemoteClientInitializer::StartMainThread(){
	assert(m_pi != NULL);

	ResumeThread(m_pi->hThread);
}

bool RemoteClientInitializer::CallClientInitializer(){
	int dummy;
	//クライアント初期化関数を呼び出す
	if(!CallThreadStartRoutin(m_pi->hProcess,"InitClient",m_RemoteDllPointer,&dummy,sizeof(dummy))){
		return false;
	}

	return true;
}


RemoteClient::RemoteClient(DWORD processID,void* remoteDllPointer) : 
	m_ProcessID(processID) , m_RemoteDllPointer(remoteDllPointer)
{
}

std::pair<bool,int> RemoteClient::CallFunction(const string& func_name,void *arg,int arg_size){
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,m_ProcessID);

	DWORD ret;
	bool succeed = CallThreadStartRoutin(hProcess,func_name.c_str(),m_RemoteDllPointer,arg,arg_size,&ret);

	CloseHandle(hProcess);

	return make_pair(succeed,0);
}
