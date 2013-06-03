#pragma once

#ifdef __GLOBAL__
#	define GLOBAL
#else 
#	define GLOBAL extern
#endif

#include "AntTweakBar.h"

namespace TW_Global{
	GLOBAL TwBar *bar;

	GLOBAL const char sBarName[] = "rpyEditor";
	GLOBAL const char sRewindRate[] = "RewindRate";
	GLOBAL const char sDebugString[] = "DebugString";
}