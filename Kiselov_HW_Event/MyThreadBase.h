#pragma once
//#include "Exception.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ProcessFinder.h"
/******************************************/
// Parent class of THREAD FOR MULTIFUNCTION
/******************************************/
class MyThreadBase
{
protected:
	HANDLE hndlThread;		// pointer to void - handler 
	friend DWORD WINAPI ThreadProc(LPVOID lpParametr);
public:
	
	MyThreadBase();

	virtual ~MyThreadBase();

	virtual DWORD WINAPI ThreadFunction() = 0;

	void Run(void);

	void Wait(void)const;

	void Close(void)const; 
}; 
// EXTERN GLOBAL FUNCTION FOR THREAD 
extern inline DWORD WINAPI ThreadProc(LPVOID lpParametr)
{
	MyThreadBase *currTread = reinterpret_cast<MyThreadBase*>(lpParametr); 
	return currTread->ThreadFunction(); 
}

/******************************************/
/******************************************/
/******************************************/

/******************************************/
// INHERITOR CLASS FOR CURRENT WORK WITH SNAPSHOT 
/******************************************/
class MyThreadForSnapShot : public MyThreadBase
{
protected:
	ProcessFinder procFinder;
	friend DWORD WINAPI ThreadProcSave(LPVOID lpParametr);
	friend DWORD WINAPI ThreadProcSort(LPVOID lpParametr);
	friend DWORD WINAPI ThreadProcShow(LPVOID lpParametr);
	friend DWORD WINAPI ThreadProcFile(LPVOID lpParametr);

public:
	MyThreadForSnapShot(){};
	virtual ~MyThreadForSnapShot(){};

	void Run(DWORD);
	DWORD WINAPI ThreadFunction()override;
};

enum SnapFunc { Save = 1, Sort, Show, File };

// EXTERN GLOBAL FUNCTIONS FOR SNAPSHOTS 
extern inline DWORD WINAPI ThreadProcSave(LPVOID lpParametr)
{
	ProcessFinder currProc; 
	return currProc.SaveProcessInfo(); 
}

extern inline DWORD WINAPI ThreadProcSort(LPVOID lpParametr)
{
	ProcessFinder currProc;
	return currProc.SortProcessInfo();
}

extern inline DWORD WINAPI ThreadProcShow(LPVOID lpParametr)
{
	ProcessFinder*currProc = reinterpret_cast<ProcessFinder*>(lpParametr);
	return currProc->ShowProcessInfo();
}

extern inline DWORD WINAPI ThreadProcFile(LPVOID lpParametr)
{
	ProcessFinder*currProc = reinterpret_cast<ProcessFinder*>(lpParametr);
	return currProc->FileProcessInfo();
}