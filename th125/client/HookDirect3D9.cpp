#include "directx_hook.h"
#include "global.h"
#include "../AntTweakBar/AntTweakBar.h"

HookDirect3D9::HookDirect3D9(IDirect3D9* direct3D)
	: Dummy_Direct3D9(direct3D)
{
}

HookDirect3D9::~HookDirect3D9()
{
}

HRESULT HookDirect3D9::CreateDevice(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
	pPresentationParameters->PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//���������̖�����

	HRESULT res = Direct3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	//D3D���O���[�o����
	g_D3DDev = *ppReturnedDeviceInterface;

	//AntTweakBar��������
	TwInit(TW_DIRECT3D9, g_D3DDev);

	if (SUCCEEDED(res)) {
		//D3DDevice9�̃t�b�N
		*ppReturnedDeviceInterface = new HookD3DDevice9(*ppReturnedDeviceInterface,hFocusWindow);
	}


	return res;
}
