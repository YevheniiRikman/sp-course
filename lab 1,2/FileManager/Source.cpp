#include <stdio.h>
#include <locale.h>
#include <tchar.h>
#include <Windows.h>
#include <Fileapi.h>
#include <iostream>

using namespace std;

void cd(char*);
void cp(char*, char*);
void mkdir(char*);
void dir();
void rm(char*);
void finfo(char*);
void PrintError();
void PrintTime(FILETIME);

char* PATH;
char* COMAND;
char* ROOT_DIR;

void PrintError() {
		DWORD err = GetLastError();
		char *text;
		FormatMessage(			
			FORMAT_MESSAGE_FROM_SYSTEM			
			| FORMAT_MESSAGE_ALLOCATE_BUFFER			
			| FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,   
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&text, 
			0,
			NULL);
		printf("%s\n", text);
}

void cd(char* newPath) {	
	if (FILE_ATTRIBUTE_DIRECTORY == GetFileAttributesA(newPath))
	{
		strcat(newPath, "\\");
		PATH = newPath;	
	}	
	else {
		cout << "No such directory\n";
	}
}

void cp(char* source, char* destination) {
	char fullPathDest[100];
	char fullPathSource[100];
	
	CopyFileA(source, destination, true);
}

void dir() {
	WIN32_FIND_DATA FindFileData;
	char* fullPath = new char;
	strcpy(fullPath, PATH);
	strcat(fullPath, "*");	
	HANDLE hFind = FindFirstFileA(fullPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		cout << "Error\n";
		return;
	}
	do {
		std::cout <<"	"<< FindFileData.cFileName << "\n";
	} while (FindNextFile(hFind, &FindFileData)!=0);	
	FindClose(hFind);
}

void rm(char* fileName) {
	char fullPath[100];
	strcpy(fullPath, PATH);
	strcat(fullPath, fileName);
	if (FILE_ATTRIBUTE_DIRECTORY == GetFileAttributesA(fullPath))
	{	
		//if (FindFirstFile())
		if (true)
		{
			RemoveDirectoryA(fullPath);
		}
		else {
			cout << "Deleted!\n";
		}
	}
	else {
		DeleteFileA(fullPath);
		cout << "Deleted!\n";
	}
}

void mkdir(char* dirName) {	
	char fullPath[100];
	strcpy(fullPath, PATH);	
	strcat(fullPath, dirName);
	CreateDirectoryA(fullPath, NULL);
}

void finfo(char* fileName) {	
	char fullPath[100];
	strcpy(fullPath, PATH);
	strcat(fullPath, fileName);	
	BY_HANDLE_FILE_INFORMATION fileInfo;
	HANDLE hr = CreateFile(
		fullPath,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (0 == GetFileInformationByHandle(hr, &fileInfo)) {
		cout << "No such file\n";
		return;
	}
	cout << "\nFile size: ";
	printf("%d", fileInfo.nFileSizeLow);
	cout << "\nNumber of links: ";
	printf("%d", fileInfo.nNumberOfLinks);
	cout << "\nFile attributes: ";
	printf("%d", fileInfo.dwFileAttributes);	
	cout << "\nCreation time: ";
	PrintTime(fileInfo.ftCreationTime);
	cout << "\nLast access time: ";
	PrintTime(fileInfo.ftLastAccessTime);
	cout << "\nLast write time: ";
	PrintTime(fileInfo.ftLastWriteTime);
	cout << "\n";
	CloseHandle(hr);
}

void PrintTime(FILETIME ft) {
	SYSTEMTIME stUTC, stLocal;
	PSTR stringTime = new char[100];
	FILETIME noteTime;
	noteTime = ft;
	GetSystemTime(&stUTC);
	FileTimeToSystemTime(&noteTime, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
	wsprintf(stringTime, "%02d/%02d/%d  %02d:%02d",
		stLocal.wDay, stLocal.wMonth, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute);
	cout << stringTime;
}

int main(int argc, char *argv[]) {	
	setlocale(LC_ALL, "Russian");
	PATH = new char;
	PATH = (char*)"C:\\";		
	while (true)
	{
		cout << PATH << "> ";
		char* command = new char;
		char* commandkey = new char;
		cin >> command;

		if (strcmp(command, "cd") == 0)
		{
			char* newDir = new char;
			cin >> newDir;
			cd(newDir);
		}
		else if (strcmp(command, "cp") == 0)
		{
			char* source = new char;
			char* destination = new char;
			cin >> source;
			cin >> destination;
			cp(source, destination);
		}
		else if (strcmp(command, "mkdir") == 0)
		{
			cin >> commandkey;
			mkdir(commandkey);
		}
		else if (strcmp(command, "dir") == 0)
		{
			dir();
		}
		else if (strcmp(command, "rm") == 0)
		{
			cin >> commandkey;
			rm(commandkey);
		}
		else if (strcmp(command, "finfo") == 0)
		{
			cin >> commandkey;
			finfo(commandkey);
		}
		else if (strcmp(command, "exit") == 0) {
			return 0;
		}
		else {
			cout << "Wrong comand";
		}
		PrintError();
	}
	return 0;
}