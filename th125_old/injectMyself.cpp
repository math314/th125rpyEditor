#include "injectMyself.h"
#include "init.h"
#include "dllInjection/dllinjection.h"

#define MYNAME TEXT("th125.dll")
#define TW_DLL_NAME TEXT("AntTweakBar.dll")

bool InjectMyself(const char *sTargetPass,	//�^�[�Q�b�g�ւ̃p�X
				  INITIALIZE *pInit)		//�������
{
	PROCESS_INFORMATION *pi = CreateSuspendedProcessA(sTargetPass);
	//NULL�Ȃ玸�s
	if(pi == NULL){ return FALSE; }

	//AntTweakBar.dll�̑}��
	if(!DllInjection(pi,TW_DLL_NAME)){
		ResumeProcess(pi);
		CloseProcess(pi);
		return false;
	}

	//���g�̑}��
	HANDLE hRemoteModule = DllInjection(pi,MYNAME);

	if(hRemoteModule){
		//������DLL�́A���̃v���Z�X���ł̃A�h���X���擾
		HANDLE hMyModule = GetModuleHandle(MYNAME);
		if(hMyModule== NULL){
			//setErrorStringEx("%s ---- ���g�̃��W���[���A�h���X�̎擾�Ɏ��s���܂����B",MYNAME);
			ResumeProcess(pi);
			CloseProcess(pi);
			return false;
		}
		//�����[�g�v���Z�X���ł́ADLL�̃��W���[���̃A�h���X����A�����[�g�v���Z�X���́AInitalize�֐��̏ꏊ�����A�Ăяo���B
		LPTHREAD_START_ROUTINE lpRemoteInitalize = (LPTHREAD_START_ROUTINE)((DWORD)Initalize - (DWORD)hMyModule + (DWORD)hRemoteModule);
		
		//�����[�g�v���Z�X���֐��Ăяo��
		if(!ExecuteRemoteProcess(pi->hProcess,lpRemoteInitalize,pInit,sizeof(INITIALIZE),NULL)){
			ResumeProcess(pi);
			CloseProcess(pi);
			return false; 
		}
	}

	ResumeProcess(pi);
	CloseProcess(pi);


	if(!hRemoteModule){return false;}
	return true;
}