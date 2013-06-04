#pragma once

#include "directx_dummy.h"

void hook_dx_funcs();

class HookD3DDevice9 : public Dummy_D3DDevice9
{

public:
	HookD3DDevice9(IDirect3DDevice9* dev,HWND hWnd);
	~HookD3DDevice9();

	STDMETHOD(GetRasterStatus)(THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus);

	STDMETHOD(EndScene)(THIS);
};


class HookDirect3D9 : public Dummy_Direct3D9
{

public:

	//コンストラクタ
	HookDirect3D9(IDirect3D9* direct3D);
	//デストラクタ
	~HookDirect3D9();

	STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface);
};
