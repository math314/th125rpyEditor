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
//プロセスを指定して入れるだけなので、
//どのようなタイミングでも挿入することができます。 
//返り値は、ロードしたDLLの、マッピングされたアドレスです。
//失敗した場合は、NULLを返します。
HANDLE __stdcall DllInjectionW(PROCESS_INFORMATION *pi,	//プロセスの情報
							const wchar_t *szDllName);//Dllファイル名

HANDLE __stdcall  DllInjectionA(PROCESS_INFORMATION *pi,	//プロセスの情報
							const char *szDllName);//Dllファイル名
#ifdef _UNICODE
#define DllInjection DllInjectionW
#else 
#define DllInjection DllInjectionA
#endif

//----------------------------------------------------------------------------------------
//			ExecuteRemoteProcess
//----------------------------------------------------------------------------------------
//別プロセスの関数を、スレッドとして実行します。
//スレッド実行用関数と同じ形である必要があります。(PTHREAD_START_ROUTINE)
//返り値	その関数が成功したか。
bool __stdcall ExecuteRemoteProcess(HANDLE hProcess,	//プロセスのハンドル
									PTHREAD_START_ROUTINE pRemoteThreadAddress,	//リモートプロセス内関数のアドレス
									LPVOID lpParam,	//自身のプロセス内での、値の入ったアドレス
									DWORD size,		//パラメータのサイズ
									DWORD *pExitCode);	//終了コード保存場所	NULLだと保存しない

//----------------------------------------------------------------------------------------
//			CreateProcessAndInjectDll
//----------------------------------------------------------------------------------------
//指定された名前のプロセスを作成し、
//指定された名前のdllを組み込みます。
BOOL __stdcall CreateProcessAndInjectDllW(const wchar_t *szTargetName,//ターゲットの名前
							   const wchar_t *szDllName);	//いれるdll名

BOOL __stdcall CreateProcessAndInjectDllA(const char *szTargetName,//ターゲットの名前
							   const char *szDllName);	//いれるdll名

#ifdef _UNICODE
#define CreateProcessAndInjectDll CreateProcessAndInjectDllW
#else 
#define CreateProcessAndInjectDll CreateProcessAndInjectDllA
#endif

//----------------------------------------------------------------------------------------
//			CreateSuspendedProcess
//----------------------------------------------------------------------------------------
//指定した名前のプロセスを作成し、
//メインスレッドを停止した状態のプロセスの情報を返します。
//失敗した場合はNULLが返ります。
PROCESS_INFORMATION * __stdcall CreateSuspendedProcessW(const wchar_t *szTargetName);//ターゲットの名前

PROCESS_INFORMATION * __stdcall CreateSuspendedProcessA(const char *szTargetName);//ターゲットの名前

#ifdef _UNICODE
#define CreateSuspendedProcess CreateSuspendedProcessW
#else 
#define CreateSuspendedProcess CreateSuspendedProcessA

#endif
//----------------------------------------------------------------------------------------
//			ResumeProcess
//----------------------------------------------------------------------------------------
//メインスレッドを停止した状態のプロセスの情報を受け取り、
//メインスレッドを開始させます。
void __stdcall ResumeProcess(PROCESS_INFORMATION *pi);

//----------------------------------------------------------------------------------------
//			CloseProcess
//----------------------------------------------------------------------------------------
//作ったプロセス情報を破棄します。
void __stdcall CloseProcess(PROCESS_INFORMATION *pi);
