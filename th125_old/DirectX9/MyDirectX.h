#pragma once

#include "d3d9_dummy.h"
#include "../AntTweakBar/AntTweakBar.h"

//================================================
//
//			d3d9_dummy.cpp
//
//================================================

//������Ⴂ�܂��B
IDirect3D9* __stdcall myDirect3DCreate9(UINT SDKVersion);
//������Ⴂ�܂���B
HRESULT __stdcall myDirectInput8Create(HINSTANCE hinst,DWORD dwVersion,REFIID riidltf,LPVOID *ppvOut,LPUNKNOWN punkOuter);
//����B
HRESULT __stdcall myDirectSoundCreate8(LPCGUID pcGuidDevice,LPDIRECTSOUND8 *ppDS8,LPUNKNOWN pUnkOuter);
//IAT��u�������܂��B
BOOL replaceIAT(char *szModule,char *szImportName,void *DummyFunc);
//�f�o�b�O�������ݒ肵�܂��B
void setDebugString(char *str);

//FPS��\�����邽�߂ɁA������ɕϊ����āA�`��p�ɓo�^���܂��B
void setFPSString(float deal,float real);

//MyDevice9
class MyDevice9 : public Dummy_Device9 {
private:

	DrawScreen *drawScreen;

public:
	MyDevice9(IDirect3DDevice9* dev,HWND hWnd);
	~MyDevice9();

	STDMETHOD(GetRasterStatus)(THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus);

	STDMETHOD(EndScene)(THIS);
};


//MyDirect3D9

class MyDirect3D9 : public Dummy_Direct3D9
{

public:

	//�R���X�g���N�^
	MyDirect3D9(IDirect3D9* direct3D);
	//�f�X�g���N�^
	~MyDirect3D9();

	STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
	{
		pPresentationParameters->PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//���������̖�����

		char buf[1024];
		HRESULT res = Direct3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
		wsprintf(buf,"Handle = %08X,ret = %08X",*ppReturnedDeviceInterface,res);
		MessageBox(NULL,buf,"Direct3DDevice������1���",0);
		if (SUCCEEDED(res)) {
			*ppReturnedDeviceInterface = new MyDevice9(*ppReturnedDeviceInterface,hFocusWindow);
		}

		return res;
	}
	

};

//MyDirectInputDevice8

class MyDirectInputDevice8 : public Dummy_DirectInputDevice8
{

public:

	//�R���X�g���N�^
	MyDirectInputDevice8(IDirectInputDevice8* directInputDevice) : Dummy_DirectInputDevice8(directInputDevice){
	}
	//�f�X�g���N�^
	~MyDirectInputDevice8(){ }

	STDMETHOD(GetDeviceState)(THIS_ DWORD cbData,LPVOID lpvData);

};

//MyDirectInput8

class MyDirectInput8 : public Dummy_DirectInput8
{

public:

	//�R���X�g���N�^
	MyDirectInput8(IDirectInput8* directInput) : Dummy_DirectInput8(directInput){}
	//�f�X�g���N�^
	~MyDirectInput8(){}

	
	STDMETHOD(CreateDevice)(THIS_ REFGUID x,LPDIRECTINPUTDEVICE8 * y,LPUNKNOWN z)
	{ 
		HRESULT res = DInput->CreateDevice(x,y,z);
		if (SUCCEEDED(res)) {
				*y = new MyDirectInputDevice8(*y);
			}
		return res;
	}
};


//MyDirectSound8

class MyDirectSound8 : public Dummy_DirectSound8
{

public:

	//�R���X�g���N�^
	MyDirectSound8(IDirectSound8* directSound) :Dummy_DirectSound8(directSound) {}
	//�f�X�g���N�^
	~MyDirectSound8(){}


};
