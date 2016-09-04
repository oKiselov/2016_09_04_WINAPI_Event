#include "ProcessFinder.h"


ProcessFinder::ProcessFinder() {}

ProcessFinder::~ProcessFinder()
{
	if (this->wHandle)
		CloseSearch(); 
}

// ������ �������-����� �� ������ ��������� ��������� 
void ProcessFinder::StartSnapShotProcessInfo(void)const
{
	this->wHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	if (this->wHandle == INVALID_HANDLE_VALUE)
	{
		std::wcout << L"Error CreateToolhelp32Snapshot = " << GetLastError() << std::endl;
		return ;
	}
}

// �������-���� ��� ���������� �������� � ������� � ��������� 
DWORD ProcessFinder::SaveProcessInfo(void)const
{
	PROCESSENTRY32 tempPE; 
	tempPE.dwSize = sizeof(PROCESSENTRY32); 

	BOOL bProcFirst=Process32First(this->wHandle, &tempPE); 
	if (!bProcFirst)
	{
		std::wcout << L"Error Process32First = " << GetLastError() << std::endl;
		return 0;
	}

	do
	{
		this->vctrProcess32.push_back(tempPE); 
	} while (Process32Next(this->wHandle, &tempPE)); 
	return 0; 
}

// �������-���� ��� ���������� �������� 
DWORD ProcessFinder::SortProcessInfo(void)const
{
	std::sort(this->vctrProcess32.begin(), this->vctrProcess32.end(), Predicate_sort()); 
	return 0; 
}

// �������-���� ��� ������ ���� �� ������� 
DWORD ProcessFinder::ShowProcessInfo(void)const
{
	for (auto cit = this->vctrProcess32.cbegin(); cit != this->vctrProcess32.cend(); ++cit)
		std::wcout << L"Name: " << cit->szExeFile << L", ID: " << cit->th32ProcessID << L", Amount of counts: " << cit->cntThreads << std::endl; 
	return 0; 
}

// �������-���� ��� ������ � ���� 
DWORD ProcessFinder::FileProcessInfo(void)const
{
	std::wofstream ofs("SnapShot32Process.txt");
	if (!ofs.is_open())
	{
		std::wcout << L"Error Opening File = " << GetLastError() << std::endl;
		return 0;
	}
	for (auto cit = this->vctrProcess32.cbegin(); cit != this->vctrProcess32.cend(); ++cit)
	{
		ofs << L"Name: " << cit->szExeFile << L", ID: " << cit->th32ProcessID << L", Amount of counts: " << cit->cntThreads<<"\n";
	}
	ofs.close(); 
	return 0; 
}

// �������-���� ��� �������� ����������� ������� ���� 
void ProcessFinder::CloseSearch()const 
{
	CloseHandle(this->wHandle); 
}

