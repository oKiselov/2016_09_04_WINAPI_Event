#include "MyThreadBase.h"

MyThreadBase::MyThreadBase() :hndlThread(nullptr){}

MyThreadBase::~MyThreadBase()
{
	Close(); 
}

void MyThreadBase::Run(void)
{
	if (this->hndlThread)
		return;
	else
	{
		this->hndlThread = CreateThread	(0,0,ThreadProc,this,0,0);
	}
	return;
}

void MyThreadBase::Wait()const
{
	if (WaitForSingleObject((this->hndlThread), INFINITE) != WAIT_OBJECT_0)
	{
		std::wcout << L"Error = " << GetLastError() << std::endl;
	}
	return; 
}

void MyThreadBase::Close()const 
{
	if (!this->hndlThread)
		return; 
	else
		CloseHandle(this->hndlThread); 
	return;
}

// Override of member-functions FOR CURRENT CLASS SNAPSHOT
void MyThreadForSnapShot::Run(DWORD en)
{
	if (this->hndlThread)
		return;
	else
	{
		if (en == Save)
			this->hndlThread = CreateThread(0, 0, ThreadProcSave, this, 0, 0);
		else if (en == Sort)
			this->hndlThread = CreateThread(0, 0, ThreadProcSort, this, 0, 0);
		else if (en == Show)
			this->hndlThread = CreateThread(0, 0, ThreadProcShow, this, 0, 0);
		else if (en == File)
			this->hndlThread = CreateThread(0, 0, ThreadProcFile, this, 0, 0);
	}
	return;
}

DWORD MyThreadForSnapShot::ThreadFunction()
{
	Run(Save); 
	return 0;
}