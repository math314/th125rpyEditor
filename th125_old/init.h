/*
 * 初期情報関係取得
 */
#pragma once

#include <Windows.h>

typedef struct tag_INITIALIZE
{
	BYTE bCreateDebugStringFile;
	//BYTE bUseVpatch;
	//BYTE bUseExtractDataFiles;
	float fFPS[10];
	int iSaveReplayIndex;
	int ReplayIndex_Max;
	DWORD stringColor;

}INITIALIZE,*PINITIALIZE;


//このコードを実行すると、メモリ上での書き換えがすべて行われます。
DWORD __stdcall Initalize(PINITIALIZE pInit);

bool __stdcall LoadInitData(char *sExePass);
bool __stdcall SaveInitData(char *sExePass);
void __stdcall GetInitData(PINITIALIZE pInit);
void __stdcall SetInitData(PINITIALIZE pInit);