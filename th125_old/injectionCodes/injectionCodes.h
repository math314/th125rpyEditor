#pragma once
#include <windows.h>

//================================================
//
//			injectionCodes.cpp
//
//================================================

//��������s����ƁA�C���W�F�N�V�����R�[�h�����ׂēW�J����܂��B
void InjectCodes();

void CreateJmpMnemonic(void *lpBaseAddress,//�x�[�X�̃A�h���X
					   void *lpJmpAddress);//�W�����v��̃A�h���X


//�R�[�h�C���W�F�N�V���������邽�߂̋@�\�I�Ȃ��́B
void CreateMnemonic(void *pDest,//�������ݐ�
					DWORD dwSize,	//�T�C�Y
					BYTE *OriginalMnemonic,	//����j�[���j�b�N
					void *pCallFunc,	//�Ăяo���֐�
					DWORD dwOffsetOfCallMnemonic);//�R�[���j�[���j�b�N�̃I�t�Z�b�g

//dInput����Ă΂�܂��B
//����̃L�[��������邱�Ƃɂ���āA�ᑬ���̃t���O��ύX���܂��B
void SetFPS(BYTE *diks);