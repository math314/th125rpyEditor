#include "injectionCodes.h"
#include "../DebugFile.h"
#include <stdarg.h>
#include "../init.h"
#include "../DirectX9/MyDirectX.h"
#include "../AntTweakBar/AntTweakBar.h"
#include "../AntTweakBar/global.h"

void CreateJmpMnemonic(void *lpBaseAddress,//ベースのアドレス
					   void *lpJmpAddress)//ジャンプ先のアドレス
{
	DWORD dwProtect;
	VirtualProtect(lpBaseAddress,0x100,PAGE_EXECUTE_READWRITE,&dwProtect);

	DWORD dwDifference = (DWORD)lpJmpAddress - (DWORD)lpBaseAddress - 5;	//ニーモックの長さ分を引く必要がある。

	BYTE *bMnemonic = (BYTE *)lpBaseAddress;
	bMnemonic[0] = 0xE9;
	(*((DWORD *)&bMnemonic[1])) = dwDifference;

	 VirtualProtect(lpBaseAddress,0x100,dwProtect,&dwProtect);
}


void CreateMnemonic(void *pDest,//書き込み先
					DWORD dwSize,	//サイズ
					BYTE *OriginalMnemonic,	//自作ニーモニック
					void *pCallFunc,	//呼び出す関数
					DWORD dwOffsetOfCallMnemonic)//コールニーモニックのオフセット
{
	DWORD dwProtect;
	VirtualProtect(pDest,dwSize,PAGE_EXECUTE_READWRITE,&dwProtect);

	//コールがある場合は
	if(pCallFunc){
		(*(( BYTE *)&OriginalMnemonic[dwOffsetOfCallMnemonic])) = 0xE8;
		(*((DWORD *)&OriginalMnemonic[dwOffsetOfCallMnemonic + 1])) = (DWORD)pCallFunc - ((DWORD)pDest +dwOffsetOfCallMnemonic) - 5;
	}

	memcpy(pDest,OriginalMnemonic,dwSize);

	VirtualProtect(pDest,dwSize,dwProtect,&dwProtect);
}


//================================================
//
//			デバック文字列出力用(InjectionCode)
//
//================================================

int __cdecl getDebugString(char *szFormat, ...)
{
	char szDebugString[1024];
	va_list argList;
	va_start(argList, szFormat);

	int iLength = wvsprintf(szDebugString, szFormat, argList);
	va_end(argList);

	//\n\0 ---> \r\n\0
	szDebugString[iLength-1] = '\r';
	szDebugString[iLength]   = '\n';
	szDebugString[iLength+1] = '\0';

	WriteDebugFile(szDebugString);

	setDebugString(szDebugString);


	return 1;
}

void CreateMnemonic_GetDebugString_sp()
{

/*

0045EFA6     CC                INT3
0045EFA7     CC                INT3
0045EFA8     CC                INT3
0045EFA9     CC                INT3
0045EFAA     CC                INT3
0045EFAB     CC                INT3
0045EFAC     CC                INT3
0045EFAD     CC                INT3
0045EFAE     CC                INT3
0045EFAF     CC                INT3
0045EFB0     A1 B40C4D00       MOV EAX,DWORD PTR DS:[4D0CB4]
0045EFB5     83BC88 C0D04B00 0>CMP DWORD PTR DS:[EAX+ECX*4+4BD0C0],0
0045EFBD     74 16             JE SHORT th125.0045EFD5
0045EFBF     53                PUSH EBX
0045EFC0     68 AC1E4A00       PUSH th125.004A1EAC                      ;  ASCII "::preloadAnim already : %s
"
0045EFC5     E8 C6260000       CALL th125.00461690
0045EFCA     8B8488 C0D04B00   MOV EAX,DWORD PTR DS:[EAX+ECX*4+4BD0C0]
0045EFD1     83C4 08           ADD ESP,8
0045EFD4     C3                RETN


			↓
			↓
			↓

0045EFA6     8D8488 C0D04B00   LEA EAX,DWORD PTR DS:[EAX+ECX*4+4BD0C0]
0045EFAD     EB 08             JMP SHORT th125.0045EFB7
0045EFAF     90                NOP
0045EFB0     A1 B40C4D00       MOV EAX,DWORD PTR DS:[4D0CB4]
0045EFB5    ^EB EF             JMP SHORT th125.0045EFA6
0045EFB7     8338 00           CMP DWORD PTR DS:[EAX],0
0045EFBA     74 14             JE SHORT th125.0045EFD0
0045EFBC     50                PUSH EAX
0045EFBD     53                PUSH EBX
0045EFBE     68 AC1E4A00       PUSH th125.004A1EAC                      ;  ASCII "::preloadAnim already : %s"
0045EFC3     E8 3810BA0F       CALL d3dx9_42.10000000
0045EFC8     83C4 08           ADD ESP,8
0045EFCB     58                POP EAX
0045EFCC     8B00              MOV EAX,DWORD PTR DS:[EAX]
0045EFCE     C3                RETN
0045EFCF     90                NOP
0045EFD0     A1 B40C4D00       MOV EAX,DWORD PTR DS:[4D0CB4]

*/

	BYTE After_Mnemonic[] = {0x8D,0x84,0x88,0xC0,0xD0,0x4B,0x00,
							 0xEB,0x08,
							 0x90,     0xA1,0xB4,0x0C,0x4D,0x00,
							 0xEB,0xEF,     0x83,0x38,0x00,
							 0x74,0x14,     0x50,     0x53,
							 0x68,0xAC,0x1E,0x4A,0x00,
							 0x00,0x00,0x00,0x00,0x00,	//コールニーモニック
							 0x83,0xC4,0x08,     0x58,
							 0x8B,0x00,     0xC3,
							 0x90,     0xA1,0xB4,0x0C,0x4D,0x00};

	CreateMnemonic((void *)0x0045EFA6,sizeof(After_Mnemonic),After_Mnemonic,getDebugString,29);

}

//================================================
//
//			ウィンドウハック用(InjectionCode)
//
//================================================

/*
static WNDPROC oldWndProc = (WNDPROC)0x0044E960;
HRESULT CALLBACK HookWindowProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam){
	// Send event message to AntTweakBar
    if( TwEventWin(hWnd, msg, wParam, lParam) ){
        return 0;   // Event has been handled by AntTweakBar
	}

	return oldWndProc(hWnd,msg,wParam,lParam);
}

void CreateMnemonic_CallCreateHookWindowProc()
{

0044F806  |. C74424 18 60E94400   MOV DWORD PTR SS:[ESP+18],th125.0044E960 ; |

			↓
			↓
			↓

0044F806  |. C74424 18 00000000   MOV DWORD PTR SS:[ESP+18],HookWindowProc ; |


	BYTE mnemonic[4];
	(*((int *)mnemonic)) = (int)HookWindowProc;
	CreateMnemonic((void *)(0x0044F806 + 4),4,mnemonic,NULL,0);
}
*/

//================================================
//
//			ウィンドウフック用(InjectionCode)
//
//================================================

static WNDPROC oldWndProc = NULL;
static HWND *pMainWnd = (HWND *)0x004D17D8;
HRESULT CALLBACK HookWindowProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam){
	// Send event message to AntTweakBar
    if( TwEventWin(hWnd, msg, wParam, lParam) ){
        return 0;   // Event has been handled by AntTweakBar
	}

	return oldWndProc(hWnd,msg,wParam,lParam);
}

int CallCreateHookWindowProc()
{
	oldWndProc = (WNDPROC)GetWindowLongPtr(*pMainWnd,GWLP_WNDPROC);
	SetWindowLongPtr(*pMainWnd,GWLP_WNDPROC,(LONG)HookWindowProc);

	return 0;
}

void CreateMnemonic_CallCreateHookWindowProc()
{
/*
	0044F9F0  \. C3             RETN

			↓
			↓
			↓

	0044F9F0    -E9 0B06BB0F    JMP jwdsrch.10000000

*/
	void * pAddress = (int *)0x0044F9F0;
	CreateJmpMnemonic(pAddress,CallCreateHookWindowProc);
}

//================================================
//
//			フィルム巻き数取得用(InjectionCode)
//
//================================================

/*
0043A100     83C4 14              ADD ESP,14
0043A103     C3                   RETN
0043A104     81C6 64130000        ADD ESI,1364
0043A10A     DDD8                 FSTP ST
0043A10C     E8 AF9D0200          CALL th125.00463EC0
0043A111     5F                   POP EDI
0043A112     5E                   POP ESI
0043A113     5D                   POP EBP
0043A114     5B                   POP EBX
0043A115     83C4 14              ADD ESP,14
0043A118     C3                   RETN
0043A119     5F                   POP EDI
0043A11A     DDD8                 FSTP ST
0043A11C     5E                   POP ESI
0043A11D     5D                   POP EBP
0043A11E     5B                   POP EBX
0043A11F     83C4 14              ADD ESP,14
0043A122     C3                   RETN
0043A123     CC                   INT3
0043A124     CC                   INT3
0043A125     CC                   INT3
0043A126     CC                   INT3
0043A127     CC                   INT3
0043A128     CC                   INT3
0043A129     CC                   INT3
0043A12A     CC                   INT3
0043A12B     CC                   INT3
0043A12C     CC                   INT3
0043A12D     CC                   INT3
0043A12E     CC                   INT3
0043A12F     CC                   INT3


			↓
			↓
			↓


0043A100     EB 1D                JMP SHORT th125.0043A11F
0043A102     90                   NOP
0043A103  |. C3                   RETN
0043A104  |> 81C6 64130000        ADD ESI,1364
0043A10A  |. DDD8                 FSTP ST
0043A10C  |. E8 AF9D0200          CALL th125.00463EC0
0043A111  |. 5F                   POP EDI
0043A112  |. 5E                   POP ESI
0043A113  |. 5D                   POP EBP
0043A114  |. 5B                   POP EBX
0043A115     EB 08                JMP SHORT th125.0043A11F
0043A117     90                   NOP
0043A118  |. C3                   RETN
0043A119  |> 5F                   POP EDI
0043A11A  |. DDD8                 FSTP ST
0043A11C  |. 5E                   POP ESI
0043A11D  |. 5D                   POP EBP
0043A11E  |. 5B                   POP EBX
0043A11F  |. 83C4 14              ADD ESP,14
0043A122     57                   PUSH EDI
0043A123     810424 4C130000      ADD DWORD PTR SS:[ESP],134C
0043A12A     E8 D15EBC0F          CALL igdumdx3.10000000
0043A12F     C3                   RETN

*/

void GetFilmRewindRate_main(int dummy1,int dummy2,float *pRewindRate)
{
	static float fRewindRate = 0.0f;
	//ファイル巻取り率取得
	fRewindRate = *pRewindRate * 100;

	static bool bFirstCall = true;
	if(bFirstCall){
		TwAddVarRO(TW_Global::bar,TW_Global::sRewindRate, TW_TYPE_FLOAT, &fRewindRate, 
			   " label='Strip length' help='test' ");
		bFirstCall = false;
	}

	TwSetParam(TW_Global::bar, TW_Global::sRewindRate,"label",TW_PARAM_CSTRING,1,TW_Global::sRewindRate);

}

__declspec(naked) void GetFilmRewindRate(float *pRewindRate)
{
	__asm{
		push eax
		call GetFilmRewindRate_main
	}
	
	__asm{
		pop eax
		add esp,8
		retn
	}
}

void CreateMnemonic_GetFilmRewindRate()
{
	BYTE After_Mnemonic1[3] ={
		0xEB,0x1D,0x90
	};

	CreateMnemonic((void *)0x0043A100,sizeof(After_Mnemonic1),After_Mnemonic1,NULL,0);
	After_Mnemonic1[1] = 0x08;
	CreateMnemonic((void *)0x0043A115,sizeof(After_Mnemonic1),After_Mnemonic1,NULL,0);

	BYTE After_Mnemonic2[] = {
		0x57,
		0x81,0x04,0x24,0x4C,0x13,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,		//コールニーモニック
		0xC3
	};

	CreateMnemonic((void *)0x0043A122,sizeof(After_Mnemonic2),After_Mnemonic2,GetFilmRewindRate,8);

}

//================================================
//
//			FPS設定用(InjectionCode)
//
//================================================

static LARGE_INTEGER *pFrequency = (LARGE_INTEGER *)0x004D17F0;
static LARGE_INTEGER FrequencyBase = {0};

static int getUseFPSIndex(BYTE *diks);
static float changeFPS(BYTE *diks,
			   float *fFPS);

void Start_SetFPS(){
	QueryPerformanceFrequency(&FrequencyBase);
}

//dInputから呼ばれます。
//特定のキーを押されることによって、低速等のフラグを変更します。
void SetFPS(BYTE *diks)
{


//------------------------------FPS計測
	static LARGE_INTEGER lastCount = {0};
	static LARGE_INTEGER currCount = {0};
	static DWORD FPSCount = 0;
	static float realFPS = 0.0f;

	QueryPerformanceCounter(&currCount);

	FPSCount++;

	if(currCount.QuadPart - lastCount.QuadPart >= FrequencyBase.QuadPart){	//1秒間より多かったら
		if(currCount.QuadPart != 0){
			realFPS = (float)(FPSCount * (double)FrequencyBase.QuadPart / (currCount.QuadPart - lastCount.QuadPart)) ;	//FPS計算
		}
		lastCount = currCount;
		FPSCount = 0;
		Start_SetFPS();
	}

//------------------------------FPS変更
	//最後に押された数字ボタンを取得
	int iFPSindex = getUseFPSIndex(diks);

	INITIALIZE init;
	GetInitData(&init);
	float fUseFPS = 60.0f;

	//FPSをセット
	fUseFPS = changeFPS(diks,&(init.fFPS[iFPSindex]));
	SetInitData(&init);

	pFrequency->QuadPart = (LONGLONG)(FrequencyBase.QuadPart * 60 / (double)fUseFPS );

	setFPSString(fUseFPS,realFPS);

	return;
}

//使うFPSのフラグを返します。
int getUseFPSIndex(BYTE *diks)
{

	//初期値は7(FPS = 60)
	static int iLastPushed = 7;
	int iPushed = -1;

	//0~9で押されたものを0から順に探していく。1つだけ見つける。
		 if(diks[DIK_0] & 0x80){ iPushed = 0;}
	else if(diks[DIK_1] & 0x80){ iPushed = 1;}
	else if(diks[DIK_2] & 0x80){ iPushed = 2;}
	else if(diks[DIK_3] & 0x80){ iPushed = 3;}
	else if(diks[DIK_4] & 0x80){ iPushed = 4;}
	else if(diks[DIK_5] & 0x80){ iPushed = 5;}
	else if(diks[DIK_6] & 0x80){ iPushed = 6;}
	else if(diks[DIK_7] & 0x80){ iPushed = 7;}
	else if(diks[DIK_8] & 0x80){ iPushed = 8;}
	else if(diks[DIK_9] & 0x80){ iPushed = 9;}

	if(iPushed != -1){
		iLastPushed = iPushed;	//押されてたら、フラグ入れ替え。
	}

	//フラグを返す。
	return iLastPushed;

}

#define CHANGE_FPS_H	0x0001
#define CHANGE_FPS_L	0x0002

float changeFPS(BYTE *diks,
			   float *pfFPS)
{
	static int iLastChangeFPSKey = 0;
	int iChangeFPSKey = 0;

	//Hが押されたか
	if(diks[DIK_H] & 0x80){
		iChangeFPSKey |= CHANGE_FPS_H;
	}
	//Lが押されたか
	if(diks[DIK_L] & 0x80){
		iChangeFPSKey |= CHANGE_FPS_L;
	}

	//キー入力に変わりがない時
	if(iLastChangeFPSKey == iChangeFPSKey){
		return *pfFPS;
	}

	iLastChangeFPSKey = iChangeFPSKey;	//キー入力代入

	if(iLastChangeFPSKey & CHANGE_FPS_H){
		*pfFPS += 1.0f;
		if( *pfFPS > 600.0f ){ *pfFPS = 600.0f; }

	} else if(iLastChangeFPSKey & CHANGE_FPS_L){
		*pfFPS -= 1.0f;
		if( *pfFPS < 3.0f){ *pfFPS= 3.0f;}
	}

	return *pfFPS;
}


//================================================
//
//			FPS設定用(InjectionCode)
//
//================================================

/*

0043BA74      E8 77F8FFFF   CALL th125.0043B2F0


			↓
			↓
			↓


0043BA74      E8 8745BC0F   CALL igdumdx3.10000000


*/

typedef struct tag_th125RpyHeader
{
	DWORD magic;
	WORD  w1;	// 1
	WORD  w2;	// 0?
	DWORD d2;
	DWORD commentOffset;
	DWORD version;				//0x0100
	DWORD d3;
	DWORD d4;
	DWORD rawRpyMainSize;
	DWORD EncodedRpyMainSize;
}th125RpyHeader;

static int rpyFlag = 0;

static void *pReadRpy = (void *)0x0043B2F0;

int CreateRpyMainDataFile_main()
{
	if(rpyFlag != 1){
		return 0;
	}

	th125RpyHeader *pRpyHeader = (th125RpyHeader *)(*((DWORD *)((*((DWORD *)0x004B68CC)) + 0x18)));
	void *pRpyMain = (void *)(*((DWORD *)((*((DWORD *)0x004B68CC)) + 0x1C)));

	if(pRpyMain == NULL){
		return 0;
	}
	const char *sRpyName = (const char *)0x004B6798;
	char sNewRpyName[1024];
	for(int i = 0; sRpyName[i] != '.'; i++){
		sNewRpyName[i] = sRpyName[i];
	}

	lstrcatA(sNewRpyName,"_main.rpy");

	HANDLE hFile = CreateFileA(sNewRpyName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	DWORD dwAcc;
	DWORD dwWriteSize = pRpyHeader->EncodedRpyMainSize;
	if(dwWriteSize >= 1024 * 1024 * 10){	//念のため。10MB以上は不可能に。
		CloseHandle(hFile);
		return 0;
	}
	WriteFile(hFile,pRpyMain,dwWriteSize,&dwAcc,NULL);
	CloseHandle(hFile);

	return 0;
}

void CreateRpyMainDataFile_end();

__declspec(naked) void CreateRpyMainDataFile_start()
{
	__asm{
		push eax
		mov rpyFlag,eax
		mov eax,CreateRpyMainDataFile_end
		mov [esp + 4],eax	//リターン先を書き換える
		pop eax
		jmp pReadRpy
	}
}

__declspec(naked) void CreateRpyMainDataFile_end()
{
	__asm{
		test eax,eax
		jnz failed
		call CreateRpyMainDataFile_main
failed :
		push eax
		mov DWORD PTR [esp],0x0043BA79
		ret
	}
}

void CreateMnemonic_CreateRpyMainDataFile()
{
	BYTE After_Mnemonic[5] = {0};

	CreateMnemonic((void *)0x0043BA74,sizeof(After_Mnemonic),After_Mnemonic,CreateRpyMainDataFile_start,0);
}

#define DEBUG_ADDRESS 0x004653C0
#define DEBUG_ADDRESS2 0x00454840
#define DEBUG_ADDRESS3 0x00461690
#define DEBUG_ADDRESS4 0x00453840

void InjectCodes()
{

	CreateJmpMnemonic((void *)DEBUG_ADDRESS,(void *)getDebugString);
	CreateJmpMnemonic((void *)DEBUG_ADDRESS2,(void *)getDebugString);
	CreateJmpMnemonic((void *)DEBUG_ADDRESS3,(void *)getDebugString);
	CreateJmpMnemonic((void *)DEBUG_ADDRESS4,(void *)getDebugString);
	CreateMnemonic_GetDebugString_sp();
	
	//------------------------------Direct3D9,DirectInput8,DirectSound8の置き換え
	{
		void *pFunc;
		void *pDirectSound = (void *)0x00497008;
		void *pDirect3DCreate9 = (void *)0x004972A8;
		void *pDirectInput8Create = (void *)0x00497000;

		pFunc = myDirectSoundCreate8;
		CreateMnemonic(pDirectSound,4,(BYTE *)&pFunc,NULL,0);

		pFunc = myDirect3DCreate9;
		CreateMnemonic(pDirect3DCreate9,4,(BYTE *)&pFunc,NULL,0);

		pFunc = myDirectInput8Create;
		CreateMnemonic(pDirectInput8Create,4,(BYTE *)&pFunc,NULL,0);
	}

	//------------------------------FPSの調整開始
	Start_SetFPS();

	//------------------------------ウィンドウフック開始
	CreateMnemonic_CallCreateHookWindowProc();

	//------------------------------フィルム巻取り率取得可能にする。
	CreateMnemonic_GetFilmRewindRate();

	//------------------------------リプレイファイルを書き込む
	CreateMnemonic_CreateRpyMainDataFile();
	
}