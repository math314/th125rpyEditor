/*
 * �������֌W�擾
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


//���̃R�[�h�����s����ƁA��������ł̏������������ׂčs���܂��B
DWORD __stdcall Initalize(PINITIALIZE pInit);

bool __stdcall LoadInitData(char *sExePass);
bool __stdcall SaveInitData(char *sExePass);
void __stdcall GetInitData(PINITIALIZE pInit);
void __stdcall SetInitData(PINITIALIZE pInit);