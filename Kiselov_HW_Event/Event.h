/******************************************
Написать класс базовый класс Event. 
От него производные AutoEvent и ManualEvent, для работы с событиями как с объектами. 
Должны быть реализованы методы: Wait(Период);Set();Reset();Close();
*****************************************/

#pragma once
#include <iostream>
#include <Windows.h>

/****************************************/
// BASE CLASS EVENT  
/*****************************************/
class Event
{
protected:
	HANDLE hndlEvent; 
public:
	Event();
	virtual ~Event();

	virtual void Create(void)=0;

	void Wait(DWORD);

	void Set(void)const; 

	void Close(void)const; 
};

/****************************************/
// INHERITOR CLASS AUTOEVENT  
/*****************************************/
class AutoEvent :public Event
{
public:
	void Create(void)override;
};

/****************************************/
// INHERITOR CLASS MANUALEVENT  
/*****************************************/
class ManualEvent : public Event
{
public: 
	void Create(void)override;
	void Reset(void)const; 
};