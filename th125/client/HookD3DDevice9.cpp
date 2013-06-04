#include "directx_hook.h"

HookD3DDevice9::HookD3DDevice9(IDirect3DDevice9* dev,HWND hWnd)
	: Dummy_D3DDevice9(dev,hWnd)
{
}

HookD3DDevice9::~HookD3DDevice9()
{
}

HRESULT HookD3DDevice9::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS *pRasterStatus)
{
	HRESULT hr = Device9->GetRasterStatus(iSwapChain,pRasterStatus);

	pRasterStatus->InVBlank = TRUE;

	return hr;
}

HRESULT HookD3DDevice9::EndScene()
{
	HRESULT ret = Device9->EndScene();

	return ret;

}