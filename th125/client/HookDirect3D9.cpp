#include "directx_hook.h"

HookDirect3D9::HookDirect3D9(IDirect3D9* direct3D)
	: Dummy_Direct3D9(direct3D)
{
}

HookDirect3D9::~HookDirect3D9()
{
}

HRESULT HookDirect3D9::CreateDevice(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
	pPresentationParameters->PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//‚’¼“¯Šú‚Ì–³Œø‰»

	HRESULT res = Direct3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	if (SUCCEEDED(res)) {
		//D3DDevice9‚ÌƒtƒbƒN
		*ppReturnedDeviceInterface = new HookD3DDevice9(*ppReturnedDeviceInterface,hFocusWindow);
	}

	return res;
}
