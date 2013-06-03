#define __GLOBAL__

#include "MyDirectX.h"

#include "../init.h"
#include "../injectionCodes/injectionCodes.h"
#include <stdio.h>

#include "../AntTweakBar/AntTweakBar.h"
#include "../AntTweakBar/global.h"

using namespace TW_Global;

//------------------------------デバック文字列描画用
static char szDebugString0[256] = {0};
static char szDebugString1[256] = {0};
static char szDebugString2[256] = {0};
static char szDebugString3[256] = {0};
static char szDebugString4[256] = {0};
static char szDebugString5[256] = {0};
static char szDebugString6[256] = {0};
static char szDebugString7[256] = {0};
static char szDebugString8[256] = {0};
static char szDebugString9[256] = {0};

static int CurrentFreeStr = 0;

static char *pszDebugString[10] = {szDebugString0,szDebugString1,szDebugString2,szDebugString3,szDebugString4,
								  szDebugString5,szDebugString6,szDebugString7,szDebugString8,szDebugString9};

static bool bDrawDebugString = true;

void setDebugString(char *str)
{
	lstrcpy(pszDebugString[CurrentFreeStr],str);
	if(++CurrentFreeStr == 10) CurrentFreeStr = 0;

	/*char s[1024];
	wsprintf(s,"%s/%s",sBarName,sDebugString);
	for(int i =0; i < 10; i++){
		TwSetParam(bar, sDebugString,s,TW_PARAM_CSTRING,1,TW_Global::sRewindRate);
	}*/
}

void setdrawDebugStringFlag(bool flag){bDrawDebugString = flag;}

static char szFPSString[128] = {0};

void setFPSString(float deal,float real)
{
	sprintf(szFPSString,"FPS:設定 : %3.3ffps\n    実際 : %3.3ffps",deal,real);
}

//コンストラクタ
MyDirect3D9::MyDirect3D9(IDirect3D9* direct3D) : Dummy_Direct3D9(direct3D)
{
}
//デストラクタ
MyDirect3D9::~MyDirect3D9()
{
}

MyDevice9::MyDevice9(IDirect3DDevice9* dev,HWND hWnd) : Dummy_Device9(dev,hWnd)
{
	Device9 = dev;
	this->hWnd = hWnd;
	
	drawScreen = new DrawScreen(dev,hWnd);


	//AntTweakBar
	TwInit(TW_DIRECT3D9,dev);

	RECT rc;
	const static HWND *pMainWnd = (HWND *)0x004D17D8;
	GetWindowRect(*pMainWnd,&rc);

	int ret = TwWindowSize(640,480);
	if(ret == 0){
		MessageBoxA(NULL,TwGetLastError(),"rpyeditor",0);
	}

	// Create a tweak bar
	bar = TwNewBar(sBarName);
    TwDefine(" GLOBAL help='th125RpyEditor\nThis tool make th125-rpy file freedom !' "); // Message added to the help bar.
	char s[1024];
	lstrcpy(s,sBarName);
	lstrcat(s," color='128 224 160' text=dark ");
    TwDefine(s); // Change TweakBar color and use dark text

    /*// Add 'numSec' to 'bar': it is a modifiable (RW) variable of type TW_TYPE_INT32. Its shortcuts are [s] and [S].
    TwAddVarRW(bar, "NumSec", TW_TYPE_INT32, &numSec, 
               " label='Strip length' min=1 max=1000 keyIncr=s keyDecr=S help='Number of segments of the strip.' ");

    // Add 'color' to 'bar': it is a modifiable variable of type TW_TYPE_COLOR3F (3 floats color)
    TwAddVarRW(bar, "Color", TW_TYPE_COLOR3F, &color, " label='Strip color' ");

    // Add 'bgColor' to 'bar': it is a modifiable variable of type TW_TYPE_COLOR32 (32 bits color)
    TwAddVarRW(bar, "BgColor", TW_TYPE_COLOR32, &bgColor, " label='Background color' ");
	*/
}

MyDevice9::~MyDevice9()
{
	SAFE_DELETE(Device9);
	SAFE_DELETE(drawScreen);

	TwTerminate();
}

HRESULT MyDevice9::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS *pRasterStatus)
{
	HRESULT hr = Device9->GetRasterStatus(iSwapChain,pRasterStatus);

	pRasterStatus->InVBlank = TRUE;

	return hr;
}

static BYTE g_diks[256];
static BYTE g_diksOld[256];

HRESULT MyDevice9::EndScene()
{
	INITIALIZE init;
	GetInitData(&init);

//------------------------------デバッグ文字列の描画
	static BYTE bDrawDebugString = 1;
	if((g_diks[DIK_D] & 0x80) && (!(g_diksOld[DIK_D] & 0x80))){ bDrawDebugString ^= 1;}
	if(bDrawDebugString){
		RECT rect = {370,180,640,480};
		char szPrint[256*10];
		wsprintf(szPrint,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
			pszDebugString[(CurrentFreeStr + 0)%10],pszDebugString[(CurrentFreeStr + 1)%10],
			pszDebugString[(CurrentFreeStr + 2)%10],pszDebugString[(CurrentFreeStr + 3)%10],pszDebugString[(CurrentFreeStr + 4)%10],
			pszDebugString[(CurrentFreeStr + 5)%10],pszDebugString[(CurrentFreeStr + 6)%10],
			pszDebugString[(CurrentFreeStr + 7)%10],pszDebugString[(CurrentFreeStr + 8)%10],pszDebugString[(CurrentFreeStr + 9)%10],
			"[D]ボタンで表示/非表示の切り替え");

		drawScreen->Draw(szPrint,340,150,init.stringColor);
	}
//------------------------------FPSの描画

	drawScreen->Draw(szFPSString,0,430,init.stringColor);

	//if(TwDraw() == 0){
	//	drawScreen->Draw(TwGetLastError(),200,430,init.stringColor);
	//}

	HRESULT ret = Device9->EndScene();

	return ret;

}


HRESULT MyDirectInputDevice8::GetDeviceState(DWORD cbData,LPVOID lpvData)
{
	HRESULT hr = DIDevice->GetDeviceState(cbData,lpvData);

	//失敗なら帰る。
	if(FAILED(hr)){return hr;}


	//デバイスの種類の取得
	DIDEVICEINSTANCE DIDeviceInstance;
	DIDeviceInstance.dwSize = sizeof(DIDEVICEINSTANCE);
	HRESULT hr2 = DIDevice->GetDeviceInfo(&DIDeviceInstance);
	//失敗なら帰る。
	if(FAILED(hr2)){return hr;}

	if( (DIDeviceInstance.dwDevType &0xFF ) == DI8DEVTYPE_KEYBOARD){//キーボードなら
		SetFPS((BYTE *)lpvData);
		memcpy(g_diksOld,g_diks,256);	//1個前のを保存
		memcpy(g_diks,lpvData,256);		//現在の入力を保存
	}

	//ASM_INT3

	return hr;
}



//IATを置き換えます。
BOOL replaceIAT(char *szModule,char *szImportName,void *DummyFunc)
{
  HMODULE                  base = GetModuleHandle(NULL);
  DWORD                    size;
  PIMAGE_IMPORT_DESCRIPTOR imgDesc = (PIMAGE_IMPORT_DESCRIPTOR)(ImageDirectoryEntryToData(base, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &size));
	
  while(imgDesc->Name) {
    char* module = (char*)((DWORD)(base) + imgDesc->Name);
    if(!lstrcmp(module, szModule)) {
      break; 
	}
	++imgDesc;
  }

  if(imgDesc->Name) {

    PIMAGE_THUNK_DATA pIAT,pINT;
    pIAT = (PIMAGE_THUNK_DATA)((DWORD)(base) + imgDesc->FirstThunk);
    pINT = (PIMAGE_THUNK_DATA)((DWORD)(base) + imgDesc->OriginalFirstThunk);
    while(pIAT->u1.Function) {
	  if(IMAGE_SNAP_BY_ORDINAL(pINT->u1.Ordinal)) {
        continue;
	  }
	  PIMAGE_IMPORT_BY_NAME pImportName = (PIMAGE_IMPORT_BY_NAME)((DWORD)(base)+pINT->u1.AddressOfData);

	  if(!lstrcmp((const char*)(pImportName->Name), szImportName)) {
	    DWORD oldProtect;
	    VirtualProtect(&pIAT->u1.Function, sizeof(DWORD), PAGE_READWRITE, &oldProtect);
	    pIAT->u1.Function = (DWORD)(DummyFunc);
	    VirtualProtect(&pIAT->u1.Function,sizeof(DWORD),oldProtect,&oldProtect);
      }

      ++pIAT;
      ++pINT;
    }
  }

  return TRUE;
}

//作っちゃいます。
IDirect3D9* __stdcall myDirect3DCreate9(UINT SDKVersion)
{
	IDirect3D9* direct3D = Direct3DCreate9(SDKVersion);
	if(direct3D == NULL){
		return NULL;
	}
	MyDirect3D9 *dummy_3D = new MyDirect3D9(direct3D);

	//MessageBox(NULL,"myDirect3DCreate9","Injection",MB_OK);

  return dummy_3D;
}

//作っちゃいますよ。
HRESULT __stdcall myDirectInput8Create(HINSTANCE hinst,DWORD dwVersion,REFIID riidltf,LPVOID *ppvOut,LPUNKNOWN punkOuter)
{
	HRESULT hr = DirectInput8Create(hinst,dwVersion,riidltf,ppvOut,punkOuter);

	//失敗なら普通に戻る
	if(hr != S_OK){return hr;}

	MyDirectInput8 * myInput = new MyDirectInput8((IDirectInput8 *)*ppvOut);

	*ppvOut = (LPVOID)myInput;
	
	//MessageBox(NULL,"DirectInput8Create","Injection",MB_OK);
	return hr;
}

HRESULT __stdcall myDirectSoundCreate8(LPCGUID pcGuidDevice,LPDIRECTSOUND8 *ppDS8,LPUNKNOWN pUnkOuter)
{
	IDirectSound8 *DSound8;
	HRESULT hr = DirectSoundCreate8(pcGuidDevice,&DSound8,pUnkOuter);
	//失敗したら戻る
	if( hr != S_OK){
		*ppDS8 = DSound8;
		return hr;
	}

	MyDirectSound8 *pMySound8 = new MyDirectSound8(DSound8);

	*ppDS8 = (LPDIRECTSOUND8)pMySound8;
	
	//MessageBox(NULL,"myDirectSoundCreate8","Injection",MB_OK);
	return hr;
}