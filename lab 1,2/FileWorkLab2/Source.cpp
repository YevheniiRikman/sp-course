#include <stdio.h>
#include <locale.h>
#include <tchar.h>
#include <Windows.h>

#include <iostream>
#define FILE_MAX_LENGTH 1000
#define _CRT_SECURE_NO_WARNINGS
#define _ITERATOR_DEBUG_LEVEL 2



using namespace std;

struct Note
{
	int Id;
	FILETIME CreateTime;
	char DataString[5];
	int ChangeCounter;
};

void FileInit();
bool WriteNoteToFile(Note*, int);
Note* InputData(int Id, int ChangeCounter);
DWORD FindNote(int id, DWORD*);
void OutputData(Note* note);
void ReadNotes();
bool CreateNote();
bool UpdateNote(int Id);
bool DeleteNote(int Id);
void OpenFile();
bool FileExists(LPCTSTR);

char* PATH;
int NoteQuontity = 1;
int FileSize = 2;
HANDLE HRFILE;

bool FileExists(LPCTSTR fname)
{
	return::GetFileAttributes(fname) != DWORD(-1);
}

void FileInit() {	
	WriteFile(HRFILE, &NoteQuontity, 4, NULL, NULL);
	WriteFile(HRFILE, &FileSize, 4, NULL, NULL);
	FlushFileBuffers(HRFILE);
	CloseHandle(HRFILE);
	//ReadFile(HRFILE, buf, sizeof(Note), &readByte, NULL);	
}

void OpenFile() {
	HRFILE = CreateFile(
		PATH,
		GENERIC_ALL,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}

bool CreateNote() {
	LPVOID buf = malloc(sizeof(Note));
	memset(buf, 0, sizeof(Note));
	DWORD readByte = -1;
	int Id;
	DWORD previousId = 0;
	Note* noteBuf;
	OpenFile();
	DWORD offset = FindNote(0, &previousId);
	if (offset == -1){
		SetFilePointer(HRFILE, 0, NULL, FILE_END);
	}
	else{
		SetFilePointer(HRFILE, offset, NULL, FILE_BEGIN);
	}
	noteBuf = InputData(previousId + 1, 0);
	WriteNoteToFile(noteBuf, offset);
	return true;	
}

void ReadNotes() {
	LPVOID buf = malloc(sizeof(Note));
	memset(buf, 0, sizeof(Note));
	DWORD readByte = -1;
	OpenFile();
	SetFilePointer(HRFILE, 8, NULL, FILE_BEGIN);
	while (readByte != 0)
	{
		if (0 == ReadFile(HRFILE, buf, sizeof(Note), &readByte, NULL)) {
			cout << "Create note error (Read err)\n";
			return;
		};
		if (readByte == 0)break;
		Note* noteBuf = (Note*)buf;
		if (noteBuf->Id != 0)
		{
			OutputData(noteBuf);
		}
	}
	CloseHandle(HRFILE);
}

bool UpdateNote(int Id) {
	if (Id <= 0) return false;
	LPVOID buf = malloc(sizeof(Note));
	memset(buf, 0, sizeof(Note));
	DWORD prevId = 0;
	DWORD readByte = -1;
	OpenFile();
	DWORD offset= FindNote(Id, &prevId);
	if ( offset== -1) return false;
	SetFilePointer(HRFILE, offset,NULL, FILE_BEGIN);
	if (0 == ReadFile(HRFILE, buf, sizeof(Note), &readByte, NULL)) {
		cout << "Read err\n";
		return false;
	};
	Note* noteBuf = (Note*)buf;
	noteBuf = InputData(noteBuf->Id, noteBuf->ChangeCounter);
	return WriteNoteToFile(noteBuf, offset);
}

bool DeleteNote(int Id) {
	OpenFile();
	DWORD previousId = -1;
	DWORD offset = FindNote(Id, &previousId);
	if (offset == -1)
	{
		CloseHandle(HRFILE);
		return false;
	}
	else
	{
		SetFilePointer(HRFILE, offset, NULL, FILE_END);
		Note* emptyNote = new Note();
		emptyNote->Id = 0;
		WriteNoteToFile(emptyNote,offset);
	}
	return true;
}
 
Note* InputData(int Id, int ChangeCounter) {
	Note* NoteField = new Note();
	SYSTEMTIME stUTC;
	FILETIME noteTime;
	GetSystemTime(&stUTC);
	SystemTimeToFileTime(&stUTC, &noteTime);
	cout << "Enter data string:\n";
	NoteField->Id = Id;
	NoteField->ChangeCounter = ChangeCounter+1;
	NoteField->CreateTime = noteTime;
	cin >> NoteField->DataString;	
	return NoteField;
}

void OutputData(Note* note) {
	SYSTEMTIME stUTC, stLocal;
	FILETIME noteTime = note->CreateTime;
	PSTR stringTime = new char[100];
	GetSystemTime(&stUTC);
	FileTimeToSystemTime(&noteTime, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	// преобразовать полученное время в строку
	wsprintf(stringTime, "%02d/%02d/%d  %02d:%02d",
		stLocal.wDay, stLocal.wMonth, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute);


	SystemTimeToFileTime(&stUTC, &noteTime);
	cout << "ID:         "<< note->Id << "\n";
	cout << "DATA:       "<< note->DataString << "\n";	
	cout << "TIME:       "<< stringTime << "\n";
	cout << "CHANGE_NUM: "<< note->ChangeCounter << "\n";
	cout << "--------------------\n";
}

DWORD FindNote(int id, DWORD *previousID) {
	LPVOID buf = malloc(sizeof(Note));
	memset(buf, 0, sizeof(Note));
	DWORD readByte = -1;
	DWORD offsetSum = 8;
	DWORD currentId = 0;
	SetFilePointer(HRFILE, 8, NULL, FILE_BEGIN);
	while (readByte != 0)
	{
		if (0 == ReadFile(HRFILE, buf, sizeof(Note), &readByte, NULL)) {
			cout << "Read file err\n";
			return 0;
		}
		if (readByte == 0)break;
		offsetSum += readByte;
		Note* noteBuf = (Note*)buf;
		currentId = noteBuf->Id;
		if (currentId == id) {
			return offsetSum - sizeof(Note);
		}
		*previousID = currentId;
	}
	return -1;
}

bool WriteNoteToFile(Note* note, int offset) {
	if (offset == -1){
		SetFilePointer(HRFILE, 0, NULL, FILE_END);
	}
	else {
		SetFilePointer(HRFILE, offset, NULL, FILE_BEGIN);
	}
	if (0 == WriteFile(HRFILE, note, sizeof(Note), NULL, NULL))
	{
		return false;
	}
	FlushFileBuffers(HRFILE);
	CloseHandle(HRFILE);
	return true;
}

int main(int argc, char *argv[]) {	
	argv[1] = (char *)"file.txt";
	PATH = argv[1];		
	char* path = argv[1];	
	if (FileExists(PATH) == 0) {
		HRFILE = CreateFile(
			PATH,
			GENERIC_ALL,
			FILE_SHARE_READ,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		FileInit();
	}
	if (HRFILE == INVALID_HANDLE_VALUE) {
		cout << "File open or create error\n";
		return 0;
	}
	while (true)
	{
		int action;
		int id;
		cout << "1) Read notes\n";
		cout << "2) Create note\n";
		cout << "3) Edit notes\n";
		cout << "4) Delete notes\n";
		cout << "5) Exit\n";
		scanf_s("%d", &action);
		switch (action)
		{
			case 1:ReadNotes();break;
			case 2:CreateNote();break;
			case 3:cout << "Enter ID to edit: "; cin >> id;
				if (!UpdateNote(id)) {
					cout << "Mo such note to update!";
				}				
				break;
			case 4:cout << "Enter ID to delete: ";cin >> id;
				if (!DeleteNote(id)) {
					cout << "Mo such note to delete!";
				} break;
			case 5: return 0;
			default:
				break;
		}
	}
	return 0;
}