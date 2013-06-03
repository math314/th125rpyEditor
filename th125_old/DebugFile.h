#pragma once

#include <Windows.h>

//デバッグファイル作成、書き込み
bool OpenDebugFile(const char *sDebugFileName);
void WriteDebugFile(const char *szString);
void CloseDebugFile();