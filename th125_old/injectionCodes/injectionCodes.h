#pragma once
#include <windows.h>

//================================================
//
//			injectionCodes.cpp
//
//================================================

//これを実行すると、インジェクションコードがすべて展開されます。
void InjectCodes();

void CreateJmpMnemonic(void *lpBaseAddress,//ベースのアドレス
					   void *lpJmpAddress);//ジャンプ先のアドレス


//コードインジェクションをするための機能的なもの。
void CreateMnemonic(void *pDest,//書き込み先
					DWORD dwSize,	//サイズ
					BYTE *OriginalMnemonic,	//自作ニーモニック
					void *pCallFunc,	//呼び出す関数
					DWORD dwOffsetOfCallMnemonic);//コールニーモニックのオフセット

//dInputから呼ばれます。
//特定のキーを押されることによって、低速等のフラグを変更します。
void SetFPS(BYTE *diks);