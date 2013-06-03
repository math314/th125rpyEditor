#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include "dllinjection.h"

#include "../init.h"

#include <stdio.h>
#include <tchar.h>

//別プロセスの関数を、スレッドとして実行します。
//スレッド実行用関数と同じ形である必要があります。(PTHREAD_START_ROUTINE)
//返り値	その関数が成功したか。
bool __stdcall ExecuteRemoteProcess(HANDLE hProcess,	//プロセスのハンドル
									PTHREAD_START_ROUTINE pRemoteThreadAddress,	//リモートプロセス内関数のアドレス
									LPVOID lpParam,	//自身のプロセス内での、値の入ったアドレス
									DWORD size,		//パラメータのサイズ
									DWORD *pExitCode)	//終了コード保存場所	NULLだと保存しない
{

	//終了コードの初期化
	if(pExitCode){*pExitCode = 0;}

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

HANDLE __stdcall DllInjectionW(PROCESS_INFORMATION *pi,	//プロセスの情報
								   const wchar_t *szDllName)//Dllファイル名
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
		lstrcpy(_tcsrchr(szLibFile, _TEXT('\\')) + 1, szDllName);
	} else {
		lstrcpyW(szLibFile,szDllName);
	}
	//長さ(使うメモリ領域)の計算
	szLibFileLen = lstrlen(szLibFile) + 1;
	szLibFileLen = szLibFileLen * sizeof(TCHAR);

	//プロセス内にメモリ領域の確保
	LPSTR RemoteProcessMemory;
	RemoteProcessMemory = (LPSTR)VirtualAllocEx( hProcess, NULL, szLibFileLen, MEM_COMMIT, PAGE_READWRITE);
	if(RemoteProcessMemory == NULL){
		//setErrorString("プロセス内にメモリが確保できませんでした。");
		return NULL;  
	}
	//書き込み
	if(WriteProcessMemory(hProcess, RemoteProcessMemory, (PVOID)szLibFile, szLibFileLen, NULL) == 0){
		//setErrorString("プロセスに書き込みができませんでした。");
		return NULL;
	} 
	//LoadLibraryW関数が始まるポインタの取得
	PTHREAD_START_ROUTINE pfnThreadRtn; 
	pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress( GetModuleHandle(_TEXT("Kernel32")), "LoadLibraryW");
	if (pfnThreadRtn == NULL){
		//setErrorString("LoadLibraryが見つかりませんでした。(何故？)");
		return NULL;  
	} 
	//スレッド作成
	HANDLE hThread;
	hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, RemoteProcessMemory,CREATE_SUSPENDED, NULL);
	if (hThread == NULL){
		//setErrorString("スレッドが作れませんでした。");
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

	if(dwExitCode == NULL){
		char a_szLibName[MAX_PATH];
		BOOL bDummy;
		WideCharToMultiByte(CP_ACP,0,szLibFile,-1,a_szLibName,MAX_PATH,"<不明なライブラリ>",&bDummy);
		//setErrorStringEx("%s ---- DLLがロードできませんでした。",a_szLibName);
		return NULL;
	}

	return (HANDLE)dwExitCode;
}

BOOL __stdcall CreateProcessAndInjectDllW(const wchar_t *szTargetName,//ターゲットの名前
							   const wchar_t *szDllName)	//いれるdll名
{ 
	PROCESS_INFORMATION *pi = CreateSuspendedProcessW(szTargetName);
	//NULLなら失敗
	if(pi == NULL){ return FALSE; }

	HANDLE bRet= DllInjectionW(pi,szDllName);

	ResumeProcess(pi);
	CloseProcess(pi);

	if(!bRet){return FALSE;}

	

	return TRUE;
} 

static void getDirectoryNameByFileName(wchar_t *szDest,	//出力先
								const wchar_t *szFileName)	//ファイル名
{
	int iSize = 0;	// '/'或いは'\'が最後に出たところ。

	for(int i = 0; szFileName[i] != '\0'; i++){
		if(szFileName[i] == '\\' || szFileName[i] == '/'){
			iSize = i;
		}
	}

	//後はコピー
	memcpy(szDest,szFileName,iSize * 2);
	szDest[iSize] = '\0';

	return;
}

PROCESS_INFORMATION * __stdcall CreateSuspendedProcessW(const wchar_t *szTargetName)//ターゲットの名前
{
	//ディレクトリ名保存用
	wchar_t szDirectory[MAX_PATH];
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

void __stdcall ResumeProcess(PROCESS_INFORMATION *pi)
{
	//メインスレッドの実行
	ResumeThread(pi->hThread);
}

void __stdcall CloseProcess(PROCESS_INFORMATION *pi)
{
	//スレッドを閉じる
	CloseHandle(pi->hThread);
	//プロセスを閉じる
	CloseHandle(pi->hProcess);
	//開放
	free(pi);
}

HANDLE __stdcall DllInjectionA(PROCESS_INFORMATION *pi,	//プロセスの情報
							const char *szDllName)//Dllファイル名
{
	//Unicode文字配列用意
	wchar_t w_szDllName[MAX_PATH];
	//Ansi--->Unicode
	MultiByteToWideChar(CP_ACP,0,szDllName,-1,w_szDllName,MAX_PATH);

	return DllInjectionW(pi,w_szDllName);
}

BOOL __stdcall CreateProcessAndInjectDllA(const char *szTargetName,//ターゲットの名前
								   const char *szDllName)//Dllファイル名
{
	//Unicode文字配列用意
	wchar_t w_szDllName[MAX_PATH];
	wchar_t w_szTargetName[MAX_PATH];
	//Ansi--->Unicode
	MultiByteToWideChar(CP_ACP,0,szTargetName,-1,w_szTargetName,MAX_PATH);
	MultiByteToWideChar(CP_ACP,0,szDllName,-1,w_szDllName,MAX_PATH);

	return CreateProcessAndInjectDllW(w_szTargetName,w_szDllName);
}

PROCESS_INFORMATION * __stdcall CreateSuspendedProcessA(const char *szTargetName)//ターゲットの名前
{
	//Unicode文字配列用意
	wchar_t w_szTargetName[MAX_PATH];
	//Ansi--->Unicode
	MultiByteToWideChar(CP_ACP,0,szTargetName,-1,w_szTargetName,MAX_PATH);

	return CreateSuspendedProcessW(w_szTargetName);
}