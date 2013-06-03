#pragma once

#include <Windows.h>
#include "init.h"

bool InjectMyself(const char *sTargetPass,	//ターゲットへのパス
				  INITIALIZE *pInit);		//初期情報
