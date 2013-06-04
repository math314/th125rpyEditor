#include "directx_hook.h"
#include "global.h"
#include "add_AntTweakBar.h"

HookDirect3D9::HookDirect3D9(IDirect3D9* direct3D)
	: Dummy_Direct3D9(direct3D)
{
}

HookDirect3D9::~HookDirect3D9()
{
}

HRESULT HookDirect3D9::CreateDevice(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
	pPresentationParameters->PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//垂直同期の無効化

	HRESULT res = Direct3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	//D3Dをグローバルに
	g_D3DDev = *ppReturnedDeviceInterface;

	if (SUCCEEDED(res)) {
		//D3DDevice9のフック
		*ppReturnedDeviceInterface = new HookD3DDevice9(*ppReturnedDeviceInterface,hFocusWindow);
	}

	add_AntTweakBar();

	return res;
}
