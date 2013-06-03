#include "DebugFile.h"

static HANDLE hDebugFile = NULL;

bool OpenDebugFile(const char *sDebugFileName)
{
	hDebugFile = CreateFileA(sDebugFileName,GENERIC_WRITE,FILE_SHARE_READ, NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);	//デバッグ用のファイル出力用
	
	return (hDebugFile) ? true : false;
}

void WriteDebugFile(const char *szString)
{
	DWORD dwAcc;
	if(hDebugFile){WriteFile(hDebugFile,szString,lstrlenA(szString),&dwAcc,NULL);}
}

void CloseDebugFile()
{
	if(hDebugFile){CloseHandle(hDebugFile);}
}

