#pragma once

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(me)		{ if(me){ (me)->Release();	( me )=NULL; } }
#endif
class DrawScreen 
{

	IDirect3DDevice9* dev;
	HWND hWnd;

public:
	DrawScreen(IDirect3DDevice9* dev,HWND hWnd);
	~DrawScreen();

	void Draw(LPCSTR str,int x,int y, D3DCOLOR color);
};