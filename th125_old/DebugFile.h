#pragma once

#include <Windows.h>

//�f�o�b�O�t�@�C���쐬�A��������
bool OpenDebugFile(const char *sDebugFileName);
void WriteDebugFile(const char *szString);
void CloseDebugFile();