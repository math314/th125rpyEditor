#define __DLLMAIN__

#include "DebugFile.h"
#include "init.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
                     )
{
    switch(ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

    break;
	case DLL_PROCESS_DETACH:

		//------------------------------�f�o�b�O�t�@�C�������B
		CloseDebugFile();
    }
    return TRUE;
}