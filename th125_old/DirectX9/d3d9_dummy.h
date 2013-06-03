#pragma once

#ifdef UNICODE
#undef UNICODE
#endif
#ifdef _UNICODE
#undef _UNICODE
#endif

#include <windows.h>

#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <dsound.h>
#include <imagehlp.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"imagehlp.lib")

#include "DrawScreen.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(me)			{ if(me){ delete (me);		( me )=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{if(p){(p)->Release();(p)=NULL;} }
#endif

//================================================
//
//			d3d9_dummy.cpp
//
//================================================

//IDirect3DDevice9のダミー作成
class Dummy_Device9 : public IDirect3DDevice9 {
protected:

	IDirect3DDevice9*  Device9;
	HWND hWnd;

public:
	Dummy_Device9(IDirect3DDevice9* dev,HWND hWnd)
	{
	Device9 = dev;
	hWnd = hWnd;
	}
	~Dummy_Device9()
	{SAFE_DELETE(Device9);}

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{ return Device9->QueryInterface(riid,ppvObj) ;}

    STDMETHOD_(ULONG,AddRef)(THIS)
	{ return Device9->AddRef() ;}

    STDMETHOD_(ULONG,Release)(THIS)
	{ __asm{ int 3} return Device9->Release() ;}

    /*** IDirect3DDevice9 methods ***/
    STDMETHOD(TestCooperativeLevel)(THIS)
	{ return Device9->TestCooperativeLevel() ;}

    STDMETHOD_(UINT, GetAvailableTextureMem)(THIS)
	{ return Device9->GetAvailableTextureMem() ;}

    STDMETHOD(EvictManagedResources)(THIS)
	{ return Device9->EvictManagedResources();}

    STDMETHOD(GetDirect3D)(THIS_ IDirect3D9** ppD3D9)
	{ return Device9->GetDirect3D(ppD3D9) ;}

    STDMETHOD(GetDeviceCaps)(THIS_ D3DCAPS9* pCaps)
	{ return Device9->GetDeviceCaps(pCaps) ;}

    STDMETHOD(GetDisplayMode)(THIS_ UINT iSwapChain,D3DDISPLAYMODE* pMode)
	{ return Device9->GetDisplayMode(iSwapChain,pMode); }

    STDMETHOD(GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters)
	{ return Device9->GetCreationParameters(pParameters); }

    STDMETHOD(SetCursorProperties)(THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap)
	{ return Device9->SetCursorProperties( XHotSpot,YHotSpot,pCursorBitmap); }

    STDMETHOD_(void, SetCursorPosition)(THIS_ int X,int Y,DWORD Flags)
	{ return Device9->SetCursorPosition(X,Y,Flags);}

    STDMETHOD_(BOOL, ShowCursor)(THIS_ BOOL bShow)
	{ return Device9->ShowCursor(bShow); }

    STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain)
	{ return Device9->CreateAdditionalSwapChain(pPresentationParameters,pSwapChain); }

    STDMETHOD(GetSwapChain)(THIS_ UINT iSwapChain,IDirect3DSwapChain9** pSwapChain)
	{ return Device9->GetSwapChain(iSwapChain,pSwapChain); }

    STDMETHOD_(UINT, GetNumberOfSwapChains)(THIS)
	{ return Device9->GetNumberOfSwapChains(); }

    STDMETHOD(Reset)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters)
	{ return Device9->Reset(pPresentationParameters); }

    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion)
	{ return Device9->Present(pSourceRect,pDestRect,hDestWindowOverride,pDirtyRegion); }

    STDMETHOD(GetBackBuffer)(THIS_ UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
	{ return Device9->GetBackBuffer(iSwapChain,iBackBuffer,Type,ppBackBuffer); }

    STDMETHOD(GetRasterStatus)(THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus)
	{ return Device9->GetRasterStatus(iSwapChain,pRasterStatus); }

    STDMETHOD(SetDialogBoxMode)(THIS_ BOOL bEnableDialogs)
	{ return Device9->SetDialogBoxMode(bEnableDialogs); }

    STDMETHOD_(void, SetGammaRamp)(THIS_ UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp)
	{return Device9->SetGammaRamp(iSwapChain, Flags,pRamp); }

    STDMETHOD_(void, GetGammaRamp)(THIS_ UINT iSwapChain,D3DGAMMARAMP* pRamp)
	{ return Device9->GetGammaRamp(iSwapChain, pRamp); }

    STDMETHOD(CreateTexture)(THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle)
	{ return Device9->CreateTexture(Width,Height,Levels, Usage,Format,Pool,ppTexture,pSharedHandle); }

    STDMETHOD(CreateVolumeTexture)(THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle)
	{ return Device9->CreateVolumeTexture(Width,Height,Depth,Levels, Usage,Format,Pool,ppVolumeTexture,pSharedHandle); }

    STDMETHOD(CreateCubeTexture)(THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle)
	{ return Device9->CreateCubeTexture(EdgeLength,Levels,Usage,Format,Pool,ppCubeTexture,pSharedHandle); }

    STDMETHOD(CreateVertexBuffer)(THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle)
	{ return Device9->CreateVertexBuffer( Length,Usage,FVF,Pool,ppVertexBuffer,pSharedHandle); }

    STDMETHOD(CreateIndexBuffer)(THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle)
	{ return Device9->CreateIndexBuffer(Length,Usage, Format,Pool,ppIndexBuffer,pSharedHandle); }

    STDMETHOD(CreateRenderTarget)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
	{ return Device9->CreateRenderTarget(Width,Height,Format, MultiSample,MultisampleQuality,Lockable, ppSurface,pSharedHandle); }

    STDMETHOD(CreateDepthStencilSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
	{ return Device9->CreateDepthStencilSurface(Width,Height,Format,MultiSample,MultisampleQuality,Discard,ppSurface, pSharedHandle); }

    STDMETHOD(UpdateSurface)(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint)
	{ return Device9->UpdateSurface(pSourceSurface, pSourceRect,pDestinationSurface,pDestPoint); }

    STDMETHOD(UpdateTexture)(THIS_ IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture)
	{ return Device9->UpdateTexture(pSourceTexture, pDestinationTexture); }

    STDMETHOD(GetRenderTargetData)(THIS_ IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface)
	{ return Device9->GetRenderTargetData(pRenderTarget, pDestSurface); }

    STDMETHOD(GetFrontBufferData)(THIS_ UINT iSwapChain,IDirect3DSurface9* pDestSurface)
	{ return Device9->GetFrontBufferData(iSwapChain, pDestSurface); }

    STDMETHOD(StretchRect)(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter)
	{ return Device9->StretchRect(pSourceSurface, pSourceRect,pDestSurface,pDestRect, Filter); }

    STDMETHOD(ColorFill)(THIS_ IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color)
	{ return Device9->ColorFill(pSurface,pRect, color); }

    STDMETHOD(CreateOffscreenPlainSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
	{ return Device9->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle); }

    STDMETHOD(SetRenderTarget)(THIS_ DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget)
	{ return Device9->SetRenderTarget(RenderTargetIndex, pRenderTarget); }

    STDMETHOD(GetRenderTarget)(THIS_ DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget)
	{ return Device9->GetRenderTarget(RenderTargetIndex, ppRenderTarget); }

    STDMETHOD(SetDepthStencilSurface)(THIS_ IDirect3DSurface9* pNewZStencil)
	{ return Device9->SetDepthStencilSurface(pNewZStencil); }

    STDMETHOD(GetDepthStencilSurface)(THIS_ IDirect3DSurface9** ppZStencilSurface)
	{ return Device9->GetDepthStencilSurface(ppZStencilSurface); }

    STDMETHOD(BeginScene)(THIS)
	{ return Device9->BeginScene(); }

    STDMETHOD(EndScene)(THIS)
	{ return Device9->EndScene(); }

    STDMETHOD(Clear)(THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)
	{ return Device9->Clear(Count,  pRects, Flags, Color, Z, Stencil); }

    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
	{ return Device9->SetTransform(State, pMatrix); }

    STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix)
	{ return Device9->GetTransform(State, pMatrix); }

    STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE x,CONST D3DMATRIX* y)
	{ return Device9->MultiplyTransform(x,y); }

    STDMETHOD(SetViewport)(THIS_ CONST D3DVIEWPORT9* pViewport)
	{ return Device9->SetViewport(pViewport); }

    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT9* pViewport)
	{ return Device9->GetViewport(pViewport); }

    STDMETHOD(SetMaterial)(THIS_ CONST D3DMATERIAL9* pMaterial)
	{ return Device9->SetMaterial(pMaterial); }

    STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL9* pMaterial)
	{ return Device9->GetMaterial(pMaterial); }

    STDMETHOD(SetLight)(THIS_ DWORD Index,CONST D3DLIGHT9* x)
	{ return Device9->SetLight(Index,x); }

    STDMETHOD(GetLight)(THIS_ DWORD Index,D3DLIGHT9* x)
	{ return Device9->GetLight(Index,x); }

    STDMETHOD(LightEnable)(THIS_ DWORD Index,BOOL Enable)
	{ return Device9->LightEnable(Index,Enable); }

    STDMETHOD(GetLightEnable)(THIS_ DWORD Index,BOOL* pEnable)
	{ return Device9->GetLightEnable(Index,pEnable); }

    STDMETHOD(SetClipPlane)(THIS_ DWORD Index,CONST float* pPlane)
	{ return Device9->SetClipPlane(Index,pPlane); }

    STDMETHOD(GetClipPlane)(THIS_ DWORD Index,float* pPlane)
	{ return Device9->GetClipPlane(Index,pPlane); }

    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD Value)
	{ return Device9->SetRenderState(State,Value); }

    STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD* pValue)
	{ return Device9->GetRenderState(State,pValue); }

    STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB)
	{ return Device9->CreateStateBlock(Type, ppSB); }

    STDMETHOD(BeginStateBlock)(THIS)
	{ return Device9->BeginStateBlock(); }

    STDMETHOD(EndStateBlock)(THIS_ IDirect3DStateBlock9** ppSB)
	{ return Device9->EndStateBlock(ppSB); }

    STDMETHOD(SetClipStatus)(THIS_ CONST D3DCLIPSTATUS9* pClipStatus)
	{ return Device9->SetClipStatus(pClipStatus); }

    STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS9* pClipStatus)
	{ return Device9->GetClipStatus(pClipStatus); }

    STDMETHOD(GetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture9** ppTexture)
	{ return Device9->GetTexture(Stage,ppTexture); }

    STDMETHOD(SetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture9* pTexture)
	{ return Device9->SetTexture(Stage,pTexture); }

    STDMETHOD(GetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue)
	{ return Device9->GetTextureStageState(Stage, Type, pValue); }

    STDMETHOD(SetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value)
	{ return Device9->SetTextureStageState(Stage, Type, Value); }

    STDMETHOD(GetSamplerState)(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue)
	{ return Device9->GetSamplerState(Sampler, Type, pValue); }

    STDMETHOD(SetSamplerState)(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value)
	{ return Device9->SetSamplerState(Sampler, Type, Value); }

    STDMETHOD(ValidateDevice)(THIS_ DWORD* pNumPasses)
	{ return Device9->ValidateDevice( pNumPasses); }

    STDMETHOD(SetPaletteEntries)(THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries)
	{ return Device9->SetPaletteEntries(PaletteNumber,pEntries); }

    STDMETHOD(GetPaletteEntries)(THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries)
	{ return Device9->GetPaletteEntries(PaletteNumber,pEntries); }

    STDMETHOD(SetCurrentTexturePalette)(THIS_ UINT PaletteNumber)
	{ return Device9->SetCurrentTexturePalette(PaletteNumber); }

    STDMETHOD(GetCurrentTexturePalette)(THIS_ UINT *PaletteNumber)
	{ return Device9->GetCurrentTexturePalette(PaletteNumber); }

    STDMETHOD(SetScissorRect)(THIS_ CONST RECT* pRect)
	{ return Device9->SetScissorRect(pRect); }

    STDMETHOD(GetScissorRect)(THIS_ RECT* pRect)
	{ return Device9->GetScissorRect(pRect); }

    STDMETHOD(SetSoftwareVertexProcessing)(THIS_ BOOL bSoftware)
	{ return Device9->SetSoftwareVertexProcessing(bSoftware); }

    STDMETHOD_(BOOL, GetSoftwareVertexProcessing)(THIS)
	{ return Device9->GetSoftwareVertexProcessing(); }

    STDMETHOD(SetNPatchMode)(THIS_ float nSegments)
	{ return Device9->SetNPatchMode(nSegments); }

    STDMETHOD_(float, GetNPatchMode)(THIS)
	{ return Device9->GetNPatchMode(); }

    STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount)
	{ return Device9->DrawPrimitive(PrimitiveType,StartVertex,PrimitiveCount); }

    STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE x,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
	{ return Device9->DrawIndexedPrimitive(x,BaseVertexIndex, MinVertexIndex, NumVertices, startIndex,primCount); }

    STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
	{ return Device9->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride); }

    STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
	{ return Device9->DrawIndexedPrimitiveUP(PrimitiveType,MinVertexIndex,NumVertices, PrimitiveCount,pIndexData,IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride); }

    STDMETHOD(ProcessVertices)(THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags)
	{ return Device9->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags); }

    STDMETHOD(CreateVertexDeclaration)(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl)
	{ return Device9->CreateVertexDeclaration(pVertexElements, ppDecl); }

    STDMETHOD(SetVertexDeclaration)(THIS_ IDirect3DVertexDeclaration9* pDecl)
	{ return Device9->SetVertexDeclaration(pDecl); }

    STDMETHOD(GetVertexDeclaration)(THIS_ IDirect3DVertexDeclaration9** ppDecl)
	{ return Device9->GetVertexDeclaration(ppDecl); }

    STDMETHOD(SetFVF)(THIS_ DWORD FVF)
	{ return Device9->SetFVF(FVF); }

    STDMETHOD(GetFVF)(THIS_ DWORD* pFVF)
	{ return Device9->GetFVF(pFVF); }

    STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader)
	{ return Device9->CreateVertexShader(pFunction, ppShader); }

    STDMETHOD(SetVertexShader)(THIS_ IDirect3DVertexShader9* pShader)
	{ return Device9->SetVertexShader(pShader); }

    STDMETHOD(GetVertexShader)(THIS_ IDirect3DVertexShader9** ppShader)
	{ return Device9->GetVertexShader(ppShader); }

    STDMETHOD(SetVertexShaderConstantF)(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
	{ return Device9->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount); }

    STDMETHOD(GetVertexShaderConstantF)(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount)
	{ return Device9->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount); }

    STDMETHOD(SetVertexShaderConstantI)(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
	{ return Device9->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount); }

    STDMETHOD(GetVertexShaderConstantI)(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount)
	{ return Device9->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount); }

    STDMETHOD(SetVertexShaderConstantB)(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
	{ return Device9->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount); }

    STDMETHOD(GetVertexShaderConstantB)(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
	{ return Device9->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount); }

    STDMETHOD(SetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride)
	{ return Device9->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride); }

    STDMETHOD(GetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride)
	{ return Device9->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride); }

    STDMETHOD(SetStreamSourceFreq)(THIS_ UINT StreamNumber,UINT Setting)
	{ return Device9->SetStreamSourceFreq(StreamNumber, Setting); }

    STDMETHOD(GetStreamSourceFreq)(THIS_ UINT StreamNumber,UINT* pSetting)
	{ return Device9->GetStreamSourceFreq(StreamNumber, pSetting); }

    STDMETHOD(SetIndices)(THIS_ IDirect3DIndexBuffer9* pIndexData)
	{ return Device9->SetIndices(pIndexData); }

    STDMETHOD(GetIndices)(THIS_ IDirect3DIndexBuffer9** ppIndexData)
	{ return Device9->GetIndices(ppIndexData); }

    STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader)
	{ return Device9->CreatePixelShader(pFunction, ppShader); }

    STDMETHOD(SetPixelShader)(THIS_ IDirect3DPixelShader9* pShader)
	{ return Device9->SetPixelShader(pShader); }

    STDMETHOD(GetPixelShader)(THIS_ IDirect3DPixelShader9** ppShader)
	{ return Device9->GetPixelShader(ppShader); }

    STDMETHOD(SetPixelShaderConstantF)(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
	{ return Device9->SetPixelShaderConstantF(StartRegister, pConstantData,Vector4fCount); }

    STDMETHOD(GetPixelShaderConstantF)(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount)
	{ return Device9->GetPixelShaderConstantF(StartRegister, pConstantData,Vector4fCount); }

    STDMETHOD(SetPixelShaderConstantI)(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
	{ return Device9->SetPixelShaderConstantI(StartRegister, pConstantData,Vector4iCount); }

    STDMETHOD(GetPixelShaderConstantI)(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount)
	{ return Device9->GetPixelShaderConstantI(StartRegister, pConstantData,Vector4iCount); }

    STDMETHOD(SetPixelShaderConstantB)(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
	{ return Device9->SetPixelShaderConstantB(StartRegister, pConstantData,BoolCount); }

    STDMETHOD(GetPixelShaderConstantB)(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
	{ return Device9->GetPixelShaderConstantB (StartRegister, pConstantData,BoolCount);}

    STDMETHOD(DrawRectPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo)
	{ return Device9->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo); }

    STDMETHOD(DrawTriPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo)
	{ return Device9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);  }

    STDMETHOD(DeletePatch)(THIS_ UINT Handle)
	{ return Device9->DeletePatch(Handle); }

	STDMETHOD(CreateQuery)(THIS_ D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery)
	{ return Device9->CreateQuery(Type,ppQuery);}

};


//IDirect3D9のダミー作成
class Dummy_Direct3D9 : public IDirect3D9{

protected:

	IDirect3D9 *Direct3D;
public:

	//コンストラクタ
	Dummy_Direct3D9(IDirect3D9* direct3D){
		Direct3D = direct3D;
	}
	//デストラクタ
	~Dummy_Direct3D9(){ SAFE_DELETE(Direct3D);}


	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{ return Direct3D->QueryInterface(riid,ppvObj);}

    STDMETHOD_(ULONG,AddRef)(THIS)
	{ return Direct3D->AddRef() ;}

    STDMETHOD_(ULONG,Release)(THIS)
	{ return Direct3D->Release() ;}

    /*** Ireturn Direct3D9 methods ***/
    STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction)
	{ return Direct3D->RegisterSoftwareDevice(pInitializeFunction) ;}

    STDMETHOD_(UINT, GetAdapterCount)(THIS)
	{ return Direct3D->GetAdapterCount() ;}

    STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier)
	{ return Direct3D->GetAdapterIdentifier(Adapter,Flags,pIdentifier) ;}

    STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter,D3DFORMAT Format)
	{ return Direct3D->GetAdapterModeCount(Adapter,Format) ;}

    STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode)
	{ return Direct3D->EnumAdapterModes(Adapter,Format,Mode,pMode) ;}

    STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode)
	{ return Direct3D->GetAdapterDisplayMode(Adapter,pMode) ;}

    STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter,D3DDEVTYPE CheckType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL Windowed)
	{ return Direct3D->CheckDeviceType(Adapter,CheckType,DisplayFormat,BackBufferFormat,Windowed) ;}

    STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)
	{ return Direct3D->CheckDeviceFormat(Adapter,DeviceType,AdapterFormat,Usage,RType,CheckFormat) ;}

    STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
	{ return Direct3D->CheckDeviceMultiSampleType(Adapter,DeviceType,SurfaceFormat,Windowed,MultiSampleType,pQualityLevels) ;}

    STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)
	{ return Direct3D->CheckDepthStencilMatch(Adapter,DeviceType,AdapterFormat,RenderTargetFormat,DepthStencilFormat) ;}

	STDMETHOD(CheckDeviceFormatConversion)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat)
	{ return Direct3D->CheckDeviceFormatConversion(Adapter,DeviceType,SourceFormat,TargetFormat); }

    STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps)
	{ return Direct3D->GetDeviceCaps(Adapter,DeviceType,pCaps) ;}

    STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter)
	{ return Direct3D->GetAdapterMonitor(Adapter) ;}

    STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
	{ return Direct3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface); }

};

//IDirectInputDevice8のダミー作成

class Dummy_DirectInputDevice8 : public IDirectInputDevice8
{

protected:
	IDirectInputDevice8 *DIDevice;

public:

	//コンストラクタ
	Dummy_DirectInputDevice8(IDirectInputDevice8* directInputDevice){
		DIDevice = directInputDevice;
	}
	//デストラクタ
	~Dummy_DirectInputDevice8(){ SAFE_DELETE(DIDevice);}

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{ return DIDevice->QueryInterface(riid,ppvObj);}

    STDMETHOD_(ULONG,AddRef)(THIS)
	{ return DIDevice->AddRef() ;}

    STDMETHOD_(ULONG,Release)(THIS)
	{ return DIDevice->Release() ;}

 
    /*** IDirectInputDevice8 methods ***/
    STDMETHOD(GetCapabilities)(THIS_ LPDIDEVCAPS x)
	{ return DIDevice->GetCapabilities(x) ;}

    STDMETHOD(EnumObjects)(THIS_ LPDIENUMDEVICEOBJECTSCALLBACK x,LPVOID y,DWORD z)
	{ return DIDevice->EnumObjects(x,y,z) ;}

    STDMETHOD(GetProperty)(THIS_ REFGUID x,LPDIPROPHEADER y)
	{ return DIDevice->GetProperty(x,y) ;}

    STDMETHOD(SetProperty)(THIS_ REFGUID x,LPCDIPROPHEADER y)
	{ return DIDevice->SetProperty(x,y) ;}

    STDMETHOD(Acquire)(THIS)
	{ return DIDevice->Acquire() ;}

    STDMETHOD(Unacquire)(THIS)
	{return DIDevice->Unacquire() ;}

    STDMETHOD(GetDeviceState)(THIS_ DWORD cbData,LPVOID lpvData)
	{ return DIDevice->GetDeviceState(cbData,lpvData) ;}

    STDMETHOD(GetDeviceData)(THIS_ DWORD x,LPDIDEVICEOBJECTDATA y,LPDWORD z,DWORD a)
	{ return DIDevice->GetDeviceData(x,y,z,a) ;}

    STDMETHOD(SetDataFormat)(THIS_ LPCDIDATAFORMAT x)
	{ return DIDevice->SetDataFormat(x) ;}

    STDMETHOD(SetEventNotification)(THIS_ HANDLE x)
	{ return DIDevice->SetEventNotification( x) ;}

    STDMETHOD(SetCooperativeLevel)(THIS_ HWND x,DWORD y)
	{ return DIDevice->SetCooperativeLevel(x,y) ;}

    STDMETHOD(GetObjectInfo)(THIS_ LPDIDEVICEOBJECTINSTANCE x,DWORD y,DWORD z)
	{ return DIDevice->GetObjectInfo(x,y,z) ;}

    STDMETHOD(GetDeviceInfo)(THIS_ LPDIDEVICEINSTANCE x)
	{ return DIDevice->GetDeviceInfo(x) ;}

    STDMETHOD(RunControlPanel)(THIS_ HWND x,DWORD y)
	{ return DIDevice->RunControlPanel(x,y) ;}

    STDMETHOD(Initialize)(THIS_ HINSTANCE x,DWORD y,REFGUID z)
	{ return DIDevice->Initialize(x,y,z) ;}

    STDMETHOD(CreateEffect)(THIS_ REFGUID x,LPCDIEFFECT y,LPDIRECTINPUTEFFECT * z,LPUNKNOWN a)
	{ return DIDevice->CreateEffect(x,y,z,a) ;}

    STDMETHOD(EnumEffects)(THIS_ LPDIENUMEFFECTSCALLBACK x,LPVOID y,DWORD z)
	{ return DIDevice->EnumEffects(x,y,z) ;}

    STDMETHOD(GetEffectInfo)(THIS_ LPDIEFFECTINFO x,REFGUID y)
	{ return DIDevice->GetEffectInfo(x,y) ;}

    STDMETHOD(GetForceFeedbackState)(THIS_ LPDWORD x)
	{ return DIDevice->GetForceFeedbackState(x) ;}

    STDMETHOD(SendForceFeedbackCommand)(THIS_ DWORD x)
	{ return DIDevice->SendForceFeedbackCommand(x) ;}

    STDMETHOD(EnumCreatedEffectObjects)(THIS_ LPDIENUMCREATEDEFFECTOBJECTSCALLBACK x,LPVOID y,DWORD z)
	{ return DIDevice->EnumCreatedEffectObjects(x,y,z) ;}

    STDMETHOD(Escape)(THIS_ LPDIEFFESCAPE x)
	{ return DIDevice->Escape(x) ;}

    STDMETHOD(Poll)(THIS)
	{ return DIDevice->Poll() ;}

    STDMETHOD(SendDeviceData)(THIS_ DWORD x,LPCDIDEVICEOBJECTDATA y,LPDWORD z,DWORD a)
	{ return DIDevice->SendDeviceData(x,y,z,a) ;}

    STDMETHOD(EnumEffectsInFile)(THIS_ LPCSTR x,LPDIENUMEFFECTSINFILECALLBACK y,LPVOID z,DWORD a)
	{ return DIDevice->EnumEffectsInFile(x,y,z,a) ;}

    STDMETHOD(WriteEffectToFile)(THIS_ LPCSTR x,DWORD y,LPDIFILEEFFECT z,DWORD a)
	{ return DIDevice->WriteEffectToFile(x,y,z,a) ;}

    STDMETHOD(BuildActionMap)(THIS_ LPDIACTIONFORMATA x,LPCSTR y,DWORD z)
	{ return DIDevice->BuildActionMap(x,y,z) ;}

    STDMETHOD(SetActionMap)(THIS_ LPDIACTIONFORMATA x,LPCSTR y,DWORD z)
	{ return DIDevice->SetActionMap(x,y,z) ;}

    STDMETHOD(GetImageInfo)(THIS_ LPDIDEVICEIMAGEINFOHEADERA x)
	{ return DIDevice->GetImageInfo(x) ;}

};



//IDirectInput8のダミー作成

class Dummy_DirectInput8 : public IDirectInput8
{
protected:
	IDirectInput8 *DInput;

public:

	//コンストラクタ
	Dummy_DirectInput8(IDirectInput8* directInput){
		DInput = directInput;
	}
	//デストラクタ
	~Dummy_DirectInput8(){ SAFE_DELETE(DInput);}

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{ return DInput->QueryInterface(riid,ppvObj);}

    STDMETHOD_(ULONG,AddRef)(THIS)
	{ return DInput->AddRef() ;}

    STDMETHOD_(ULONG,Release)(THIS)
	{ return DInput->Release() ;}

    /*** IDirectInput8 methods ***/
    STDMETHOD(CreateDevice)(THIS_ REFGUID x,LPDIRECTINPUTDEVICE8 * y,LPUNKNOWN z)
	{ return DInput->CreateDevice(x,y,z);}

    STDMETHOD(EnumDevices)(THIS_ DWORD x,LPDIENUMDEVICESCALLBACK y,LPVOID z,DWORD a)
	{ return DInput->EnumDevices(x,y,z,a) ;}

    STDMETHOD(GetDeviceStatus)(THIS_ REFGUID x)
	{ return DInput->GetDeviceStatus(x) ;}

    STDMETHOD(RunControlPanel)(THIS_ HWND x,DWORD y)
	{ return DInput->RunControlPanel(x,y) ;}

    STDMETHOD(Initialize)(THIS_ HINSTANCE x,DWORD y)
	{ return DInput->Initialize(x,y) ;}

    STDMETHOD(FindDevice)(THIS_ REFGUID x,LPCSTR y,LPGUID z)
	{ return DInput->FindDevice(x,y,z) ;}

    STDMETHOD(EnumDevicesBySemantics)(THIS_ LPCSTR x,LPDIACTIONFORMAT y,LPDIENUMDEVICESBYSEMANTICSCB z,LPVOID a,DWORD b)
	{ return DInput->EnumDevicesBySemantics(x,y,z,a,b) ;}

    STDMETHOD(ConfigureDevices)(THIS_ LPDICONFIGUREDEVICESCALLBACK x,LPDICONFIGUREDEVICESPARAMS y,DWORD z,LPVOID a) 
	{ return DInput->ConfigureDevices(x,y,z,a) ;}

};


//IDirectSound8のダミー作成

class Dummy_DirectSound8 : public IDirectSound8
{
protected:
	IDirectSound8 *DISound;

public:

	//コンストラクタ
	Dummy_DirectSound8(IDirectSound8* directSound){
		DISound = directSound;
	}
	//デストラクタ
	~Dummy_DirectSound8(){ SAFE_DELETE(DISound);}

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj)
	{ return DISound->QueryInterface(riid,ppvObj);}

    STDMETHOD_(ULONG,AddRef)(THIS)
	{ return DISound->AddRef() ;}

    STDMETHOD_(ULONG,Release)(THIS)
	{ return DISound->Release() ;}

	// IDirectSound methods
    STDMETHOD(CreateSoundBuffer)    (THIS_ LPCDSBUFFERDESC pcDSBufferDesc, LPDIRECTSOUNDBUFFER *ppDSBuffer, LPUNKNOWN pUnkOuter)
	{ return DISound->CreateSoundBuffer(pcDSBufferDesc, ppDSBuffer, pUnkOuter) ;}

    STDMETHOD(GetCaps)              (THIS_ LPDSCAPS pDSCaps)
	{ return DISound->GetCaps(pDSCaps) ;}

    STDMETHOD(DuplicateSoundBuffer) (THIS_ LPDIRECTSOUNDBUFFER pDSBufferOriginal, LPDIRECTSOUNDBUFFER *ppDSBufferDuplicate)
	{ return DISound->DuplicateSoundBuffer(pDSBufferOriginal,ppDSBufferDuplicate) ;}

    STDMETHOD(SetCooperativeLevel)  (THIS_ HWND hwnd, DWORD dwLevel)
	{ return DISound->SetCooperativeLevel(hwnd, dwLevel) ;}

    STDMETHOD(Compact)              (THIS)
	{ return DISound->Compact();}

    STDMETHOD(GetSpeakerConfig)     (THIS_ LPDWORD pdwSpeakerConfig)
	{ return DISound->GetSpeakerConfig(pdwSpeakerConfig) ;}

    STDMETHOD(SetSpeakerConfig)     (THIS_ DWORD dwSpeakerConfig)
	{ return DISound->SetSpeakerConfig(dwSpeakerConfig) ;}

    STDMETHOD(Initialize)           (THIS_ LPCGUID pcGuidDevice)
	{ return DISound->Initialize(pcGuidDevice) ;}

    // IDirectSound8 methods
    STDMETHOD(VerifyCertification)  (THIS_ LPDWORD pdwCertified)
	{ return DISound->VerifyCertification(pdwCertified) ;}


};
