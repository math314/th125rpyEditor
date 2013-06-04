#pragma once

#include "directx_dummy.h"

class HookD3DDevice9 : public Dummy_D3DDevice9 {
private:

public:
	HookD3DDevice9(IDirect3DDevice9* dev,HWND hWnd) :
		Dummy_D3DDevice9(dev,hWnd)
	{
	}

	~HookD3DDevice9(){ }

	STDMETHOD(GetRasterStatus)(THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus){
		HRESULT hr = 
		
		pRasterStatus->InVBlank = TRUE;

	}

	STDMETHOD(EndScene)(THIS);
};