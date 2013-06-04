#include "directx_hook.h"
#include "hook.h"
#include "..\debug.h"

#include <imagehlp.h>
#pragma comment(lib,"imagehlp.lib")


//IATを置き換えます。
void replaceIAT(char *szModule,char *szImportName,void *DummyFunc)
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

		return ;
      }

      ++pIAT;
      ++pINT;
    }
  }
}

IDirect3D9* __stdcall HookDirect3DCreate9(UINT SDKVersion){
	
	IDirect3D9* direct3D = Direct3DCreate9(SDKVersion);
	if(direct3D == NULL){
		return NULL;
	}
	
	HookDirect3D9 *hooked = new HookDirect3D9(direct3D);

	DebugStr("rpyEditor(client) : hooked Direct3DCreate9.");

	return hooked;
}

//DirectXのクラス作成メソッドを置き換える
void hook_dx_funcs(){
	replaceIAT("d3d9.dll","Direct3DCreate9",HookDirect3DCreate9);
}