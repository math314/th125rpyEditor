#pragma once

#include <windows.h>

//========================================================================================
//
//			dllinjection.cpp
//
//========================================================================================

//----------------------------------------------------------------------------------------
//			DllInjection
//----------------------------------------------------------------------------------------
//�v���Z�X���w�肵�ē���邾���Ȃ̂ŁA
//�ǂ̂悤�ȃ^�C�~���O�ł��}�����邱�Ƃ��ł��܂��B 
//�Ԃ�l�́A���[�h����DLL�́A�}�b�s���O���ꂽ�A�h���X�ł��B
//���s�����ꍇ�́ANULL��Ԃ��܂��B
HANDLE __stdcall DllInjectionW(PROCESS_INFORMATION *pi,	//�v���Z�X�̏��
							const wchar_t *szDllName);//Dll�t�@�C����

HANDLE __stdcall  DllInjectionA(PROCESS_INFORMATION *pi,	//�v���Z�X�̏��
							const char *szDllName);//Dll�t�@�C����
#ifdef _UNICODE
#define DllInjection DllInjectionW
#else 
#define DllInjection DllInjectionA
#endif

//----------------------------------------------------------------------------------------
//			ExecuteRemoteProcess
//----------------------------------------------------------------------------------------
//�ʃv���Z�X�̊֐����A�X���b�h�Ƃ��Ď��s���܂��B
//�X���b�h���s�p�֐��Ɠ����`�ł���K�v������܂��B(PTHREAD_START_ROUTINE)
//�Ԃ�l	���̊֐��������������B
bool __stdcall ExecuteRemoteProcess(HANDLE hProcess,	//�v���Z�X�̃n���h��
									PTHREAD_START_ROUTINE pRemoteThreadAddress,	//�����[�g�v���Z�X���֐��̃A�h���X
									LPVOID lpParam,	//���g�̃v���Z�X���ł́A�l�̓������A�h���X
									DWORD size,		//�p�����[�^�̃T�C�Y
									DWORD *pExitCode);	//�I���R�[�h�ۑ��ꏊ	NULL���ƕۑ����Ȃ�

//----------------------------------------------------------------------------------------
//			CreateProcessAndInjectDll
//----------------------------------------------------------------------------------------
//�w�肳�ꂽ���O�̃v���Z�X���쐬���A
//�w�肳�ꂽ���O��dll��g�ݍ��݂܂��B
BOOL __stdcall CreateProcessAndInjectDllW(const wchar_t *szTargetName,//�^�[�Q�b�g�̖��O
							   const wchar_t *szDllName);	//�����dll��

BOOL __stdcall CreateProcessAndInjectDllA(const char *szTargetName,//�^�[�Q�b�g�̖��O
							   const char *szDllName);	//�����dll��

#ifdef _UNICODE
#define CreateProcessAndInjectDll CreateProcessAndInjectDllW
#else 
#define CreateProcessAndInjectDll CreateProcessAndInjectDllA
#endif

//----------------------------------------------------------------------------------------
//			CreateSuspendedProcess
//----------------------------------------------------------------------------------------
//�w�肵�����O�̃v���Z�X���쐬���A
//���C���X���b�h���~������Ԃ̃v���Z�X�̏���Ԃ��܂��B
//���s�����ꍇ��NULL���Ԃ�܂��B
PROCESS_INFORMATION * __stdcall CreateSuspendedProcessW(const wchar_t *szTargetName);//�^�[�Q�b�g�̖��O

PROCESS_INFORMATION * __stdcall CreateSuspendedProcessA(const char *szTargetName);//�^�[�Q�b�g�̖��O

#ifdef _UNICODE
#define CreateSuspendedProcess CreateSuspendedProcessW
#else 
#define CreateSuspendedProcess CreateSuspendedProcessA

#endif
//----------------------------------------------------------------------------------------
//			ResumeProcess
//----------------------------------------------------------------------------------------
//���C���X���b�h���~������Ԃ̃v���Z�X�̏����󂯎��A
//���C���X���b�h���J�n�����܂��B
void __stdcall ResumeProcess(PROCESS_INFORMATION *pi);

//----------------------------------------------------------------------------------------
//			CloseProcess
//----------------------------------------------------------------------------------------
//������v���Z�X����j�����܂��B
void __stdcall CloseProcess(PROCESS_INFORMATION *pi);
