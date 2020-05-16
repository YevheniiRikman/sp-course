// lab5_b_1.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <thread>         // std::thread
#include <mutex>
#include <Windows.h>

#define THREAD_COUNT 4
DWORD WINAPI writeFile(LPVOID params);
int main()
{
	HANDLE threads[THREAD_COUNT];
	HANDLE semaphore = CreateSemaphore(NULL, 2, 2, NULL);
	DWORD dwThreadId;
	for (;;)
	{
		for (auto i = 0; i < THREAD_COUNT; i++)
		{
			threads[i] = CreateThread(NULL, 0, writeFile, semaphore, 0, &dwThreadId);
			Sleep((rand() % 3) * 1000);
		}
		DWORD dwResults = WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);
		system("pause");
		system("cls");
	}
	for (size_t i = 0; i < THREAD_COUNT; i++)
	{
		CloseHandle(threads[i]);
	}
	CloseHandle(semaphore);
	return 0;
}
DWORD WINAPI writeFile(LPVOID params)
{
	clock_t start;
	BOOL bContinue = TRUE;
	HANDLE sem = (HANDLE)params;
	while (true)
	{
		start = clock();
		do {
			DWORD dwRes = WaitForSingleObject(sem, INFINITE);
			switch (dwRes)
			{
			case WAIT_OBJECT_0:
			{
				printf("Thread %d: _ENTER_ critical\n", GetCurrentThreadId());
				HANDLE file = CreateFile(L"C:\\Users\\Sterben\\source\\repos\\Lab5\\Debug\\ansi.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				if (file == INVALID_HANDLE_VALUE)
					printf("Could not open ansi.txt\n");

				else
				{
					WriteFile(file, "Aa", 2, NULL, NULL);
				}
				CloseHandle(file);
				Sleep(((rand() % 3) + 1) * 1000);
				ReleaseSemaphore(sem, 1, NULL);
				bContinue = FALSE;
				printf("Thread %d: leave critical with time %d\n", GetCurrentThreadId(), clock() - start);
			}
			break;
			default:break;
			}
		} while (bContinue);
	}
	return TRUE;
}