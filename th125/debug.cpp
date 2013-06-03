#include "debug.h"

#include <Windows.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void DebugINT3(){ __asm{int 3} }


void DebugStr(const char *_format, ...){
	va_list arg;

    va_start(arg, _format);

	char buf[2048];
    vsprintf_s(buf, _format, arg);

	OutputDebugStringA(buf);

    va_end(arg);
}
