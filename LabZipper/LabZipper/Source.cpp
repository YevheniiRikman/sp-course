#include <stdio.h>
#include <locale.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
#include <string>

#define FILE_MAX_LENGTH 1024

using namespace std;


int main(int argc, char *argv[]) {
	
	setlocale(0, "");
	HANDLE in;//дескриптор записи в стандартный поток дочернего процесса
	HANDLE out;//дескриптор чтения из стандартного потока дочернего процесса
	HANDLE read;//дескриптор чтения из пороцесса и записи в pipe
	HANDLE write;//дескриптор записи в процесс из pipe
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = true;
	saAttr.lpSecurityDescriptor = nullptr;

	//CreatePipe(&in, &write, &saAttr, 0);   //создаём пайп записи в стандартный поток дочернего прооцесса
	CreatePipe(&read, &out, &saAttr, 0);   //создаём пайп чтения из стандартного потока дочернего прооцесса

	//создаем дочерний процесс
	STARTUPINFO si;//структура для CreateProcess
	ZeroMemory(&si, sizeof(STARTUPINFO));//обнуляем si
	si.hStdOutput = out;//подменяем pipe-дескрипторы для дочернего прооцесса
	   
	si.dwFlags |= STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi;//структура для CreateProcess
	WCHAR args[] = L"7za.exe e archive.zip";
	int operation;
	char* res;

	char path[1024];
	
	while (1)
	{
		char comm[1024] = "7za.exe";
		cout << "Вебирите операцию: " << endl << "1)Распаковка" << endl << "2)Упаковка" << endl << "3)Выход" << endl;
		cin >> operation;
		if (operation == 1)
		{
			cout << "Введите путь к файлу:";
			cin >> path;
			char comm1[] = " e ";
			strcat(comm, comm1);
			strcat(comm, path);
			system("cls");
		}
		else if (operation == 2)
		{
			cout << "Введите путь к файлу:";
			cin >> path;
			cout << "Введите имя архива:";
			char arname[128];
			cin >> arname;
			char ftype[] = ".zip ";
			char comm1[] = " a ";
			strcat(comm, comm1);
			strcat(comm, arname);
			strcat(comm, ftype);
			strcat(comm, path);
			system("cls");
		}
		else if (operation == 3)
		{
			return 0;
		}
		else
		{
			system("cls");
		}
		CreateProcess(NULL, comm, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);//запускаем процесс code.exe

	//ввод данных из pipe в стандартный поток дочернего процесса
		unsigned long bread = 0;   //кол-во прочитанных байт
		char dat[] = "10 20";//данные
		int n = string(dat).size() + 1;//размер даннх в байтах
		WaitForSingleObject(pi.hProcess, INFINITE);
		
		//вывод данных из стандартного потока дочернего процесса в pipe
		char buf[2048]; //буфер вывода
		ReadFile(read, buf, 2047, &bread, NULL);
		DWORD lp;
		GetExitCodeProcess(pi.hProcess, (&lp));
		char *istr;
		char str2[] = "Everything is Ok";
		//Поиск строки
		istr = strstr(buf, str2);
		cout << "Result: ";
		if (istr == NULL)
		{
			cout << "Error!!!!!";
		}
		else
			cout << "Everything is OK" << endl;
		
		//читаем из стандартного потока в буфер
		buf[bread] = '\0';
	}
	return 0;
}