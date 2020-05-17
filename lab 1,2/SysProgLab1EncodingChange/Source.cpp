#include <stdio.h>
#include <locale.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
#define FILE_MAX_LENGTH 1024

using namespace std;


int main(int argc, char *argv[]) {	
	char* path = argv[1];
	HANDLE rFile = CreateFile(path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (rFile == INVALID_HANDLE_VALUE) {
		printf_s("Open file Error");
		return 0;
	}

	LPVOID buf = malloc(FILE_MAX_LENGTH);
	memset(buf, 0, FILE_MAX_LENGTH);

	char pathOut[100] = "fileOut.txt";

	HANDLE wFile = CreateFile(
		pathOut,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	
	DWORD readByte = -1;
	while (readByte != 0) {

		if (0 == (ReadFile(rFile, buf, FILE_MAX_LENGTH, &readByte, NULL))) {
			printf_s("Read file Error");
			return 0;
		}
		if (readByte == 0) {
		}


		int strLength = readByte;
		int byteQuontity = 0;

		LPVOID result;


		if (strcmp(argv[2], "-u") == 0)
		{
			result = malloc(FILE_MAX_LENGTH * 2);
			memset(result, 0, FILE_MAX_LENGTH * 2);
			byteQuontity = readByte * 2;
			strLength = MultiByteToWideChar(
				CP_THREAD_ACP,
				MB_ERR_INVALID_CHARS,
				(LPCCH)buf,
				readByte,
				(LPWSTR)result,
				readByte);
			if (strLength == 0) {
				printf_s("Convertion string Error");
				return 0;
			}
		}
		else if (strcmp(argv[2], "-a") == 0)
		{
			result = malloc(FILE_MAX_LENGTH * 2);
			memset(result, 0, FILE_MAX_LENGTH * 2);
			byteQuontity = readByte / 2;
			strLength = WideCharToMultiByte(
				CP_ACP,
				WC_NO_BEST_FIT_CHARS,
				(LPCWCH)buf,
				readByte,
				(LPSTR)result,
				readByte / 2,
				NULL,
				NULL);
		}
		else {
			printf_s("Wrong action key");
			return 0;
		}
	

		if (0 == WriteFile(wFile, result, byteQuontity, NULL, NULL)) {
			printf_s("Write file Error");
			return 0;
		}
		FlushFileBuffers(wFile);
		printf("Bytes read: %d\n", readByte);
		printf("Bytes write: %d\n", byteQuontity);
	}
	CloseHandle(wFile);
	CloseHandle(rFile);
	return 0;
}