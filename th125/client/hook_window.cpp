#include "hook.h"
#include "..\AntTweakBar\AntTweakBar.h"

#include <Windows.h>

const HWND *pMAIN_WND = (HWND *)0x004D17D8;
static WNDPROC oldWndProc = NULL;
HRESULT CALLBACK HookWindowProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam){
	// Send event message to AntTweakBar
    if( TwEventWin(hWnd, msg, wParam, lParam) ){
        return 0;   // Event has been handled by AntTweakBar
	}

	return oldWndProc(hWnd,msg,wParam,lParam);
}

void hook_window()
{
	oldWndProc = (WNDPROC)GetWindowLongPtr(*pMAIN_WND,GWLP_WNDPROC);
	SetWindowLongPtr(*pMAIN_WND,GWLP_WNDPROC,(LONG)HookWindowProc);
}