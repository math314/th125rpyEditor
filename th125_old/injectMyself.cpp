#include "injectMyself.h"
#include "init.h"
#include "dllInjection/dllinjection.h"

#define MYNAME TEXT("th125.dll")
#define TW_DLL_NAME TEXT("AntTweakBar.dll")

bool InjectMyself(const char *sTargetPass,	//ターゲットへのパス
				  INITIALIZE *pInit)		//初期情報
{
	PROCESS_INFORMATION *pi = CreateSuspendedProcessA(sTargetPass);
	//NULLなら失敗
	if(pi == NULL){ return FALSE; }

	//AntTweakBar.dllの挿入
	if(!DllInjection(pi,TW_DLL_NAME)){
		ResumeProcess(pi);
		CloseProcess(pi);
		return false;
	}

	//自身の挿入
	HANDLE hRemoteModule = DllInjection(pi,MYNAME);

	if(hRemoteModule){
		//自分のDLLの、このプロセス内でのアドレスを取得
		HANDLE hMyModule = GetModuleHandle(MYNAME);
		if(hMyModule== NULL){
			//setErrorStringEx("%s ---- 自身のモジュールアドレスの取得に失敗しました。",MYNAME);
			ResumeProcess(pi);
			CloseProcess(pi);
			return false;
		}
		//リモートプロセス内での、DLLのモジュールのアドレスから、リモートプロセス内の、Initalize関数の場所を特定、呼び出し。
		LPTHREAD_START_ROUTINE lpRemoteInitalize = (LPTHREAD_START_ROUTINE)((DWORD)Initalize - (DWORD)hMyModule + (DWORD)hRemoteModule);
		
		//リモートプロセス内関数呼び出し
		if(!ExecuteRemoteProcess(pi->hProcess,lpRemoteInitalize,pInit,sizeof(INITIALIZE),NULL)){
			ResumeProcess(pi);
			CloseProcess(pi);
			return false; 
		}
	}

	ResumeProcess(pi);
	CloseProcess(pi);


	if(!hRemoteModule){return false;}
	return true;
}