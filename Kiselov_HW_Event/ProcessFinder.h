/***********************************************************************************************
�������� ���������,
������� � ����� ������ ��������� � ������� ��������� PROCESSENTRY32, ������������� ������� ���
������� ������, ������� ������ ������������� ������ �������� PROCESSENTRY32 � ������� sort � ������ ��������� �� ���� cntThreads
� ���������� ������� ��� �������� ������, ������� ������ ������� ��������������� ������ �� ������� : ���, ID, ���������� �������,
���������� ������� ��� ���������� ������, ������� ������ ��������� ���������� ������� � ����.
��� ������� ������������ ������ ����������� ������ Thread / AutoEvent � ������� ��� ������������ ��������.
************************************************************************************************/
#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "TlHelp32.h"
#include "WrapperHandle.h"

// �������� ��� ������-���������� �� ���������� ������� 
struct Predicate_sort
{
	bool operator ()(const PROCESSENTRY32&cntThreadsOrig, const PROCESSENTRY32&cntThreadsCmp) const throw()
	{
		return cntThreadsOrig.cntThreads > cntThreadsCmp.cntThreads;
	}
};

// ����� ��� ������ � SNAPSHOT ���������
class ProcessFinder
{
public:
	// ����������� ����� - ������ �������� ��� �������� ���������� � ��������� 
	static std::vector<PROCESSENTRY32>vctrProcess32; 
	// ��������� �� ������ ���� - ������� - SNAPSHOT ��������� 
	static HANDLE wHandle;

	ProcessFinder();
	virtual ~ProcessFinder();

	// ������ �������-����� �� ������ ��������� ��������� 
	void StartSnapShotProcessInfo(void)const;

	// �������-���� ��� ���������� �������� � ������� � ��������� 
	DWORD SaveProcessInfo(void)const;

	// �������-���� ��� ���������� �������� 
	DWORD SortProcessInfo(void)const;

	// �������-���� ��� ������ ���� �� ������� 
	DWORD ShowProcessInfo(void)const;

	// �������-���� ��� ������ � ���� 
	DWORD FileProcessInfo(void)const;

	// �������-���� ��� �������� ����������� ������� ���� 
	void CloseSearch(void)const throw(); 
};

