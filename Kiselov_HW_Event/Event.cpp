#include "Event.h"
/****************************************/
// BASE CLASS EVENT  
/*****************************************/
Event::Event() :hndlEvent(nullptr){}

Event::~Event()
{
	if (this->hndlEvent)
		Close(); 
}

void Event::Wait(DWORD dwMilliseconds)
{
	WaitForSingleObject(this->hndlEvent, dwMilliseconds); 
	return; 
}

void Event::Set() const
{
	SetEvent(this->hndlEvent); 
	return; 
}

void Event::Close() const
{
	CloseHandle(this->hndlEvent); 
	return; 
}

/****************************************/
// INHERITOR CLASS AUTOEVENT  
/*****************************************/

void AutoEvent::Create()
{
	if (this->hndlEvent)
		return;
	else
		CreateEvent(NULL, FALSE, FALSE, NULL);
	return;
}

/****************************************/
// INHERITOR CLASS MANUALEVENT  
/*****************************************/
void ManualEvent::Create()
{
	if (this->hndlEvent)
		return;
	else
		CreateEvent(NULL, TRUE, FALSE, NULL);
	return;
}

void ManualEvent::Reset() const
{
	ResetEvent(this->hndlEvent); 
	return; 
}



