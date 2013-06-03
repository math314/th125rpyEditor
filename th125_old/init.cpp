#include "init.h"
#include "DirectX9/d3d9_dummy.h"
#include "DebugFile.h"
#include "injectionCodes/injectionCodes.h"

#define DEBUG_FILE "th125Debug.txt"

static INITIALIZE g_inidata = {0};	//初期情報
const char sInitFileName[] = "rpyEditor_th125.cfg";

//初期情報取得
bool __stdcall LoadInitData(char *sExePass)
{
	DWORD dwAcc;

	HANDLE hFile = CreateFileA(sInitFileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE){
		g_inidata.bCreateDebugStringFile = FALSE;
		for(int i = 0; i < 10; i++){
			g_inidata.fFPS[i] = 60.0f;
		}
		g_inidata.iSaveReplayIndex = 26;
		g_inidata.ReplayIndex_Max = 9999;
		g_inidata.stringColor = (DWORD)D3DCOLOR_ARGB(128,128,128,128);
		return false;
	}

	ReadFile(hFile,&g_inidata,sizeof(g_inidata),&dwAcc,NULL);
	if(dwAcc != sizeof(g_inidata)){
		g_inidata.bCreateDebugStringFile = FALSE;
		for(int i = 0; i < 10; i++){
			g_inidata.fFPS[i] = 60.0f;
		}
		g_inidata.iSaveReplayIndex = 26;
		g_inidata.ReplayIndex_Max = 9999;
		g_inidata.stringColor = (DWORD)D3DCOLOR_ARGB(128,128,128,128);
		CloseHandle(hFile);
		return false;
	}

	ReadFile(hFile,sExePass,1024,&dwAcc,NULL);
	if(dwAcc != 1024){sExePass[0] = '\0';}
	sExePass[1023] = '\0';

	//例外処理
	if(g_inidata.bCreateDebugStringFile != FALSE && g_inidata.bCreateDebugStringFile != TRUE){ g_inidata.bCreateDebugStringFile = FALSE;}
	for(int i = 0 ;i < 10; i++){
		if( g_inidata.fFPS[i] < 3.0f || g_inidata.fFPS[i] > 600.0f){g_inidata.fFPS[i] = 60.0f;}
	}
	if(g_inidata.iSaveReplayIndex < -1 || g_inidata.iSaveReplayIndex > 10000){g_inidata.iSaveReplayIndex = 26;}
	if(g_inidata.ReplayIndex_Max < 0 || g_inidata.ReplayIndex_Max >10000){g_inidata.ReplayIndex_Max = 9999;}

	CloseHandle(hFile);

	return true;
}

bool __stdcall SaveInitData(char *sExePass)
{

	DWORD dwAcc;
	HANDLE hFile = CreateFileA(sInitFileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE){
		return false;
	}
	WriteFile(hFile,&g_inidata,sizeof(g_inidata),&dwAcc,NULL);

	char s[1024] = {0};
	lstrcpyA(s,sExePass);
	WriteFile(hFile,s,1024,&dwAcc,NULL);

	CloseHandle(hFile);

	return true;
}


void __stdcall  GetInitData(PINITIALIZE pInit)
{
	(*pInit) = g_inidata;
}

void __stdcall SetInitData(PINITIALIZE pInit)
{
	g_inidata = (*pInit);
}

DWORD __stdcall Initalize(PINITIALIZE pInit)
{

	//初期情報の取得
	SetInitData(pInit);

	if(pInit->bCreateDebugStringFile){
		OpenDebugFile(DEBUG_FILE);
	}

	//------------------------------インジェクションコードの展開
	InjectCodes();

	return 0;
}