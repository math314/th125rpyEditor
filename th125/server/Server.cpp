#include "../const.h"
#include "Server.h"

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <cassert>

using namespace std;

static void getDirectoryNameByFileName(char *szDest,	//�o�͐�
								const char *szFileName)	//�t�@�C����
{
	int iSize = 0;	// '/'������'\'���Ō�ɏo���Ƃ���B

	for(int i = 0; szFileName[i] != '\0'; i++){
		if(szFileName[i] == '\\' || szFileName[i] == '/'){
			iSize = i;
		}
	}

	//��̓R�s�[
	memcpy(szDest,szFileName,iSize);
	szDest[iSize] = '\0';

	return;
}

PROCESS_INFORMATION * CreateSuspendedProcess(const char *szTargetName)//�^�[�Q�b�g�̖��O
{
	//�f�B���N�g�����ۑ��p
	char szDirectory[MAX_PATH];
	getDirectoryNameByFileName(szDirectory,szTargetName);
	//�\���̂̏���
	STARTUPINFO si = {0};
	PROCESS_INFORMATION *pi = (PROCESS_INFORMATION *)malloc(sizeof(PROCESS_INFORMATION));
	//�v���Z�X�̍쐬
	if(!CreateProcess(szTargetName,NULL,NULL,NULL,FALSE,CREATE_SUSPENDED | NORMAL_PRIORITY_CLASS ,
		NULL,(szDirectory[0] == '\0') ? NULL : szDirectory,&si,pi)){
		//setErrorStringEx("%s --- ������܂���ł����B",szTargetName);
		return NULL;
	}

	return pi;
}

HANDLE DllInjection(PROCESS_INFORMATION *pi,	//�v���Z�X�̏��
								   const char *szDllName)//Dll�t�@�C����
{

	HANDLE hProcess = pi->hProcess;

	//dll�t�@�C���̐�΃p�X��ۑ�����ϐ�
	TCHAR szLibFile[MAX_PATH];
	//dll�t�@�C���̐�΃p�X�̕�����̒��� + 1(\0�܂ł̒�����ۑ�����)
	int szLibFileLen;

	//�������΃p�X�Ȃ�A
	//���g�̐�΃p�X�̎擾�����āAdll�܂ł̐�΃p�X�����B
	//(�� X:/-----/--.... �Ƃ����p�X�́A1�o�C�g�ڂ�':'�Ȃ̂ŁA��΃p�X�ƂȂ�B)
	//��΃p�X�Ȃ�A���̂܂܃R�s�[���邾���B
	if(szDllName[1] != ':'){
		GetModuleFileName(NULL, szLibFile, sizeof(szLibFile));
		lstrcpy(_tcsrchr(szLibFile, '\\') + 1, szDllName);
	} else {
		lstrcpy(szLibFile,szDllName);
	}
	//����(�g���������̈�)�̌v�Z
	szLibFileLen = lstrlen(szLibFile) + 1;
	szLibFileLen = szLibFileLen * sizeof(TCHAR);

	//�v���Z�X���Ƀ������̈�̊m��
	LPSTR RemoteProcessMemory;
	RemoteProcessMemory = (LPSTR)VirtualAllocEx( hProcess, NULL, szLibFileLen, MEM_COMMIT, PAGE_READWRITE);
	if(RemoteProcessMemory == NULL){
		//MessageBox(NULL,"�v���Z�X���Ƀ��������m�ۂł��܂���ł����B","",0);
		return NULL;  
	}

	//��������
	if(WriteProcessMemory(hProcess, RemoteProcessMemory, (PVOID)szLibFile, szLibFileLen, NULL) == 0){
		//MessageBox(NULL,"�v���Z�X�ɏ������݂��ł��܂���ł����B","",0);
		return NULL;
	}

	//LoadLibraryW�֐����n�܂�|�C���^�̎擾
	PTHREAD_START_ROUTINE pfnThreadRtn; 
	pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress( GetModuleHandle(_TEXT("Kernel32")), "LoadLibraryA");
	if (pfnThreadRtn == NULL){
		//MessageBox(NULL,"LoadLibrary��������܂���ł����B","",0);
		return NULL;  
	}

	//�X���b�h�쐬
	HANDLE hThread;
	hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, RemoteProcessMemory,CREATE_SUSPENDED, NULL);
	if (hThread == NULL){
		MessageBox(NULL,"�X���b�h�����܂���ł����B","",0);
		return NULL;
	}

	//�X���b�h���s
	ResumeThread(hThread);
	BYTE *modulePointer = (BYTE *)WaitForSingleObject(hThread,INFINITE);
	DWORD dwExitCode;	//�I���R�[�h
	GetExitCodeThread(hThread,&dwExitCode);
	CloseHandle(hThread);	//�X���b�h�����
	
	//�v���Z�X���Ɋm�ۂ����������̊J��
	VirtualFreeEx(hProcess,RemoteProcessMemory,260,MEM_DECOMMIT);

	return (HANDLE)dwExitCode;
}

bool __stdcall ExecuteRemoteProcess(HANDLE hProcess,	//�v���Z�X�̃n���h��
									PTHREAD_START_ROUTINE pRemoteThreadAddress,	//�����[�g�v���Z�X���֐��̃A�h���X
									LPVOID lpParam,	//���g�̃v���Z�X���ł́A�l�̓������A�h���X
									DWORD size,		//�p�����[�^�̃T�C�Y
									DWORD *pExitCode)	//�I���R�[�h�ۑ��ꏊ	NULL���ƕۑ����Ȃ�
{

	//�I���R�[�h�̏�����
	if(pExitCode) pExitCode= 0;

	//�v���Z�X���Ƀ������̈�̊m��
	LPSTR RemoteProcessMemory;
	RemoteProcessMemory = (LPSTR)VirtualAllocEx( hProcess, NULL, size, MEM_COMMIT, PAGE_READWRITE);
	if(RemoteProcessMemory == NULL){
		//setErrorString("�v���Z�X���Ƀ��������m�ۂł��܂���ł����B");
		return false;  
	}
	//��������
	if(WriteProcessMemory(hProcess, RemoteProcessMemory, lpParam, size, NULL) == 0){
		//setErrorString("�v���Z�X�ɏ������݂��ł��܂���ł����B");
		return false;
	} 
 
	//�X���b�h�쐬
	HANDLE hThread;
	hThread = CreateRemoteThread(hProcess, NULL, 0, pRemoteThreadAddress, RemoteProcessMemory,CREATE_SUSPENDED, NULL);
	if (hThread == NULL){
		//setErrorString("�X���b�h�����܂���ł����B");
		return false;
	}

	//�X���b�h���s
	ResumeThread(hThread);
	BYTE *modulePointer = (BYTE *)WaitForSingleObject(hThread,INFINITE);
	if(pExitCode){
		GetExitCodeThread(hThread,pExitCode);
	}
	CloseHandle(hThread);	//�X���b�h�����
	
	//�v���Z�X���Ɋm�ۂ����������̊J��
	VirtualFreeEx(hProcess,RemoteProcessMemory,size,MEM_DECOMMIT);

	return true;
}


bool CallThreadStartRoutin(HANDLE hProcess,const char* func_name,void *remote_dll_pointer,void *arg,int arg_size,DWORD *ret = NULL){
	HMODULE hMyModule = GetModuleHandle(MY_DLL_NAME);
	FARPROC pfunc = GetProcAddress(hMyModule,func_name);

	//�����[�g�v���Z�X���ł́ADLL�̃��W���[���̃A�h���X����A�����[�g�v���Z�X���̊֐��̏ꏊ�����A�Ăяo���B
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
		//�X���b�h�����
		CloseHandle(m_pi->hThread);
		//�v���Z�X�����
		CloseHandle(m_pi->hProcess);
		//�J��
		free(m_pi);
		m_pi = NULL;
	}
}

//�N���C�A���g�v���Z�X�̍쐬
bool RemoteClientInitializer::CreateClientProcess(){
	assert(m_pi == NULL);

	m_pi = CreateSuspendedProcess(m_TargetPath.c_str());
	return m_pi != NULL;
}

//dll injection���s��
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
	//�N���C�A���g�������֐����Ăяo��
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
