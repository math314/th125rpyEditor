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

//�ʃv���Z�X�̊֐����A�X���b�h�Ƃ��Ď��s���܂��B
//�X���b�h���s�p�֐��Ɠ����`�ł���K�v������܂��B(PTHREAD_START_ROUTINE)
//�Ԃ�l	���̊֐��������������B
bool __stdcall ExecuteRemoteProcess(HANDLE hProcess,	//�v���Z�X�̃n���h��
									PTHREAD_START_ROUTINE pRemoteThreadAddress,	//�����[�g�v���Z�X���֐��̃A�h���X
									LPVOID lpParam,	//���g�̃v���Z�X���ł́A�l�̓������A�h���X
									DWORD size,		//�p�����[�^�̃T�C�Y
									DWORD *pExitCode)	//�I���R�[�h�ۑ��ꏊ	NULL���ƕۑ����Ȃ�
{

	//�I���R�[�h�̏�����
	if(pExitCode){*pExitCode = 0;}

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

HANDLE __stdcall DllInjectionW(PROCESS_INFORMATION *pi,	//�v���Z�X�̏��
								   const wchar_t *szDllName)//Dll�t�@�C����
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
		lstrcpy(_tcsrchr(szLibFile, _TEXT('\\')) + 1, szDllName);
	} else {
		lstrcpyW(szLibFile,szDllName);
	}
	//����(�g���������̈�)�̌v�Z
	szLibFileLen = lstrlen(szLibFile) + 1;
	szLibFileLen = szLibFileLen * sizeof(TCHAR);

	//�v���Z�X���Ƀ������̈�̊m��
	LPSTR RemoteProcessMemory;
	RemoteProcessMemory = (LPSTR)VirtualAllocEx( hProcess, NULL, szLibFileLen, MEM_COMMIT, PAGE_READWRITE);
	if(RemoteProcessMemory == NULL){
		//setErrorString("�v���Z�X���Ƀ��������m�ۂł��܂���ł����B");
		return NULL;  
	}
	//��������
	if(WriteProcessMemory(hProcess, RemoteProcessMemory, (PVOID)szLibFile, szLibFileLen, NULL) == 0){
		//setErrorString("�v���Z�X�ɏ������݂��ł��܂���ł����B");
		return NULL;
	} 
	//LoadLibraryW�֐����n�܂�|�C���^�̎擾
	PTHREAD_START_ROUTINE pfnThreadRtn; 
	pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress( GetModuleHandle(_TEXT("Kernel32")), "LoadLibraryW");
	if (pfnThreadRtn == NULL){
		//setErrorString("LoadLibrary��������܂���ł����B(���́H)");
		return NULL;  
	} 
	//�X���b�h�쐬
	HANDLE hThread;
	hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, RemoteProcessMemory,CREATE_SUSPENDED, NULL);
	if (hThread == NULL){
		//setErrorString("�X���b�h�����܂���ł����B");
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

	if(dwExitCode == NULL){
		char a_szLibName[MAX_PATH];
		BOOL bDummy;
		WideCharToMultiByte(CP_ACP,0,szLibFile,-1,a_szLibName,MAX_PATH,"<�s���ȃ��C�u����>",&bDummy);
		//setErrorStringEx("%s ---- DLL�����[�h�ł��܂���ł����B",a_szLibName);
		return NULL;
	}

	return (HANDLE)dwExitCode;
}

BOOL __stdcall CreateProcessAndInjectDllW(const wchar_t *szTargetName,//�^�[�Q�b�g�̖��O
							   const wchar_t *szDllName)	//�����dll��
{ 
	PROCESS_INFORMATION *pi = CreateSuspendedProcessW(szTargetName);
	//NULL�Ȃ玸�s
	if(pi == NULL){ return FALSE; }

	HANDLE bRet= DllInjectionW(pi,szDllName);

	ResumeProcess(pi);
	CloseProcess(pi);

	if(!bRet){return FALSE;}

	

	return TRUE;
} 

static void getDirectoryNameByFileName(wchar_t *szDest,	//�o�͐�
								const wchar_t *szFileName)	//�t�@�C����
{
	int iSize = 0;	// '/'������'\'���Ō�ɏo���Ƃ���B

	for(int i = 0; szFileName[i] != '\0'; i++){
		if(szFileName[i] == '\\' || szFileName[i] == '/'){
			iSize = i;
		}
	}

	//��̓R�s�[
	memcpy(szDest,szFileName,iSize * 2);
	szDest[iSize] = '\0';

	return;
}

PROCESS_INFORMATION * __stdcall CreateSuspendedProcessW(const wchar_t *szTargetName)//�^�[�Q�b�g�̖��O
{
	//�f�B���N�g�����ۑ��p
	wchar_t szDirectory[MAX_PATH];
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

void __stdcall ResumeProcess(PROCESS_INFORMATION *pi)
{
	//���C���X���b�h�̎��s
	ResumeThread(pi->hThread);
}

void __stdcall CloseProcess(PROCESS_INFORMATION *pi)
{
	//�X���b�h�����
	CloseHandle(pi->hThread);
	//�v���Z�X�����
	CloseHandle(pi->hProcess);
	//�J��
	free(pi);
}

HANDLE __stdcall DllInjectionA(PROCESS_INFORMATION *pi,	//�v���Z�X�̏��
							const char *szDllName)//Dll�t�@�C����
{
	//Unicode�����z��p��
	wchar_t w_szDllName[MAX_PATH];
	//Ansi--->Unicode
	MultiByteToWideChar(CP_ACP,0,szDllName,-1,w_szDllName,MAX_PATH);

	return DllInjectionW(pi,w_szDllName);
}

BOOL __stdcall CreateProcessAndInjectDllA(const char *szTargetName,//�^�[�Q�b�g�̖��O
								   const char *szDllName)//Dll�t�@�C����
{
	//Unicode�����z��p��
	wchar_t w_szDllName[MAX_PATH];
	wchar_t w_szTargetName[MAX_PATH];
	//Ansi--->Unicode
	MultiByteToWideChar(CP_ACP,0,szTargetName,-1,w_szTargetName,MAX_PATH);
	MultiByteToWideChar(CP_ACP,0,szDllName,-1,w_szDllName,MAX_PATH);

	return CreateProcessAndInjectDllW(w_szTargetName,w_szDllName);
}

PROCESS_INFORMATION * __stdcall CreateSuspendedProcessA(const char *szTargetName)//�^�[�Q�b�g�̖��O
{
	//Unicode�����z��p��
	wchar_t w_szTargetName[MAX_PATH];
	//Ansi--->Unicode
	MultiByteToWideChar(CP_ACP,0,szTargetName,-1,w_szTargetName,MAX_PATH);

	return CreateSuspendedProcessW(w_szTargetName);
}