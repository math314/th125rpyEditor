#include "DrawScreen.h"
#include <d3d9.h>

DrawScreen::DrawScreen(IDirect3DDevice9* dev,HWND hWnd)
{
	this->dev = dev;
	this->hWnd = hWnd;

}
DrawScreen::~DrawScreen()
{
}

void DrawScreen::Draw(LPCSTR str,int x,int y, D3DCOLOR color)
{
	RECT rect = {x,y,640,480};
}