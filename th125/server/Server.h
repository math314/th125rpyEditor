#include <string>
#include <Windows.h>

class RemoteClientInitializer{
	const std::string m_DllPath;
	const std::string m_TargetPath;

	PROCESS_INFORMATION *m_pi;
	HANDLE m_RemoteDllPointer;
public:

	RemoteClientInitializer(const std::string& dll_path,const std::string& target_path);
	~RemoteClientInitializer();

	//サーバープロセスの作成
	bool CreateClientProcess();

	//dll injectionを行う
	bool Injection();

	void StartMainThread();

	bool CallClientInitializer();


};

class RemoteClient{
	DWORD m_ProcessID;
	void* m_RemoteDllPointer;

public:
	RemoteClient(DWORD processID,void* remoteDllPointer);

	std::pair<bool,int> CallFunction(const std::string& func_name,void *arg,int arg_size);
};