#pragma once

#include <windows.h>

#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <dsound.h>

#ifdef GLOBAL
#	define EXTERN
#else
#	define EXTERN extern
#endif

EXTERN IDirect3DDevice9 *g_D3DDev;
