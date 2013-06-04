#include "server\Server.h"
#include "client\hook.h"
#include <cassert>
#include <memory>

std::unique_ptr<RemoteClient> _rc;

bool __stdcall InitServer(const char* dll_path,const char *target_path){

	RemoteClientInitializer initializer(dll_path,target_path);

	if(!initializer.CreateClientProcess()){
		MessageBox(NULL,"CreateClientProcess failed.","rpyEditor(server)",0);
		return false;
	}
	if(!initializer.Injection()){
		MessageBox(NULL,"Injection failed.","rpyEditor(server)",0);
		return false;
	}

	if(!initializer.CallClientInitializer()){
		MessageBox(NULL,"CallClientInitializer failed.","rpyEditor(server)",0);
		return false;
	}

	//�N���C�A���g�̃��C���X���b�h�𓮂���
	initializer.StartMainThread();

	//_rc.reset();

	return true;
}

int __stdcall InitClient(void *dummy){

	//MessageBox(NULL,"succeed!","rpyEditor(client)",0);

	//directX�֌W�̃��\�b�h��u��������
	hook_dx_funcs();

	//main window��hook
	hook_window();

	return 0;
}