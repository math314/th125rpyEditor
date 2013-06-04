#include "hook.h"
#include "../debug.h"
#include "..\AntTweakBar\AntTweakBar.h"

#include <Windows.h>

const HWND *pMAIN_WND = (HWND *)0x004D17D8;
static WNDPROC oldWndProc = NULL;
HRESULT CALLBACK HookWindowProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam){
	
	//AntTweakBarは、ウィンドウのサイズとdirectXのBackBufferサイズが違う場合に対応していない
	//ので、此方側で対応する。
	if(msg == WM_MOUSEMOVE){
		RECT rc;
		GetClientRect(hWnd,&rc);

		int x = ((short)LOWORD(lParam)) * 640 / (rc.right - rc.left);
		int y = ((short)HIWORD(lParam)) * 480 / (rc.bottom - rc.top);

        // send signed! mouse coordinates
        int handled = TwMouseMotion(x,y);
		if(handled != 0){
			return 0; //handled by AntTweakBar(TwMouseMotion)
		}
	} else {
		// Send event message to AntTweakBar
		if( TwEventWin(hWnd, msg, wParam, lParam) ){
			return 0;   // Event has been handled by AntTweakBar
		}
	}

	return oldWndProc(hWnd,msg,wParam,lParam);
}

void hook_window()
{
	oldWndProc = (WNDPROC)GetWindowLongPtr(*pMAIN_WND,GWLP_WNDPROC);
	SetWindowLongPtr(*pMAIN_WND,GWLP_WNDPROC,(LONG)HookWindowProc);
}