/***********************************************************************************************
Написать программу,
которая в одном потоке сохраняет в векторе структуры PROCESSENTRY32, устанавливает событие для
второго потока, который должен отсортировать вектор структур PROCESSENTRY32 с помощью sort и лямбда выражения по полю cntThreads
и установить событие для третьего потока, который должен вывести отсортированный вектор на консоль : Имя, ID, Количество потоков,
установить событие для четвертого потока, который должен сохранить содержимое вектора в файл.
Для решения поставленной задачи использвать классы Thread / AutoEvent и обертку для дескрипторов объектов.
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

// Предикат для лямбда-сортировки по количеству потоков 
struct Predicate_sort
{
	bool operator ()(const PROCESSENTRY32&cntThreadsOrig, const PROCESSENTRY32&cntThreadsCmp) const throw()
	{
		return cntThreadsOrig.cntThreads > cntThreadsCmp.cntThreads;
	}
};

// КЛАСС ДЛЯ РАБОТЫ С SNAPSHOT ПРОЦЕССОВ
class ProcessFinder
{
public:
	// СТАТИЧЕСКИЕ ЧЛЕНЫ - ВЕКТОР СТРУКТУР ДЛЯ ХРАНЕНИЯ ИНФОРМАЦИИ О ПРОЦЕССАХ 
	static std::vector<PROCESSENTRY32>vctrProcess32; 
	// УКАЗАТЕЛЬ НА ОБЪЕКТ ЯДРА - ПРОЦЕСС - SNAPSHOT ПРОЦЕССОВ 
	static HANDLE wHandle;

	ProcessFinder();
	virtual ~ProcessFinder();

	// ЗАПУСК ФУНКЦИИ-ЧЛЕНА НА СНЯТИЯ СКРИНШОТА ПРОЦЕССОВ 
	void StartSnapShotProcessInfo(void)const;

	// ФУНКЦИЯ-ЧЛЕН ДЛЯ СОХРАНЕНИЯ СТРУКТУР С ДАННЫМИ О ПРОЦЕССАХ 
	DWORD SaveProcessInfo(void)const;

	// ФУНКЦИЯ-ЧЛЕН ДЛЯ СОРТИРОВКИ СТРУКТУР 
	DWORD SortProcessInfo(void)const;

	// ФУНКЦИЯ-ЧЛЕН ДЛЯ ВЫВОДА ИНФО НА КОНСОЛЬ 
	DWORD ShowProcessInfo(void)const;

	// ФУНКЦИЯ-ЧЛЕН ДЛЯ ЗАПИСИ В ФАЙЛ 
	DWORD FileProcessInfo(void)const;

	// ФУНКЦИЯ-ЧЛЕН ДЛЯ ЗАКРЫТИЯ ДЕСКРИПТОРА ОБЪЕКТА ЯДРА 
	void CloseSearch(void)const throw(); 
};

