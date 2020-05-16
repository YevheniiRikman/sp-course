#include <windows.h> 
#include <stdio.h> 
#include <iostream>
#include <cstdlib> // содержит srand() и rand()

using namespace std;
DWORD dwTlsIndex;
DWORD dwLocalArray;
DWORD dwGreatestArray[10];
DWORD dwLocalSum;
DWORD num;
VOID ErrorExit(LPSTR);
int GreatestDivider(DWORD t)
{
	int num = ((int*)TlsGetValue(dwLocalArray))[t];
	for (int j = num - 1; j > 0; j--)
	{
		if (num%j == 0)
		{
			return j;
		}
	}
}

int SumOfGreatest()
{
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum += (int)TlsGetValue(dwGreatestArray[i]);
	}
	return sum;
}

DWORD WINAPI ThreadFunc(LPVOID randomDigits)
{
	LPVOID lpvData;
	LPVOID lpvMax;
	lpvMax = (LPVOID)LocalAlloc(LPTR, 256);
	LPVOID lpvLocalArray;
	LPVOID lpvGreatestArray;
	LPVOID lpvLocalSum;
	lpvLocalSum = (LPVOID)LocalAlloc(LPTR, sizeof(int));
	lpvGreatestArray = (LPVOID)LocalAlloc(LPTR, sizeof(int) * 10);
	lpvLocalArray = (LPVOID)LocalAlloc(LPTR, sizeof(int) * 10);

	TlsSetValue(dwLocalArray, randomDigits);
	int sum = 0;
	for (int t = 0; t < 10; t++)
	{
		int gr = GreatestDivider(t);
		//sum += gr;
		sum = SumOfGreatest();
		TlsSetValue(dwGreatestArray[t], (LPVOID)gr);

		printf("thread %d: ArrayData=%d GreatestDivider: %d\n ", GetCurrentThreadId(), ((int*)TlsGetValue(dwLocalArray))[t], TlsGetValue(dwGreatestArray[t]));

	}
	TlsSetValue(dwLocalSum, (LPVOID)sum);
	printf("thread %d: Sum: %d\n ", GetCurrentThreadId(), TlsGetValue(dwLocalSum));
	int max = ((int*)TlsGetValue(dwLocalArray))[0];
	for (int i = 1; i < 10; i++) {
			if (((int*)TlsGetValue(dwLocalArray))[i] > max) {
				max = ((int*)TlsGetValue(dwLocalArray))[i];
			}
	}
	printf("thread %d: max=%d\n", GetCurrentThreadId(), max);
	

	// Release the dynamic memory before the thread returns. 

	lpvData = TlsGetValue(dwTlsIndex);
	if (lpvData != 0)
		LocalFree((HLOCAL)lpvData);

	return 0;
}

int main(VOID)
{
	int thread_count;
	while (1)
	{
		system("cls");
		cout << "Enter the number of threads: ";
		scanf("%d", &thread_count);
		if (thread_count > 1)
			break;
	}
	DWORD IDThread;
	HANDLE* hThread = new HANDLE[thread_count];
	int i;
	// Allocate a TLS indexes. 

	if ((dwTlsIndex = TlsAlloc()) == TLS_OUT_OF_INDEXES)
		ErrorExit((LPSTR)"TlsAlloc failed");
	if ((dwLocalArray = TlsAlloc()) == TLS_OUT_OF_INDEXES)
		ErrorExit((LPSTR)"TlsAlloc failed");
	if ((dwLocalSum = TlsAlloc()) == TLS_OUT_OF_INDEXES)
		ErrorExit((LPSTR)"TlsAlloc failed");
	if ((num = TlsAlloc()) == TLS_OUT_OF_INDEXES)
		ErrorExit((LPSTR)"TlsAlloc failed");
	for (int y = 0; y < 10; y++)
	{
		if ((dwGreatestArray[y] = TlsAlloc()) == TLS_OUT_OF_INDEXES)
			ErrorExit((LPSTR)"TlsAlloc failed");
	}
	if ((dwLocalSum = TlsAlloc()) == TLS_OUT_OF_INDEXES)
		ErrorExit((LPSTR)"TlsAlloc failed");
	// Create multiple threads. 


	for (i = 0; i < thread_count; i++)
	{
		int* randomDigits = (int*)LocalAlloc(LPTR, sizeof(int)*10);

		for (int j = 0; j < 10; j++)
		{
			randomDigits[j] = 10 + rand() % 91; // запись случайного числа, которое вернет rand()
			printf("thread %d: number=%d\n", i, randomDigits[j]);
		}
		int num = 5;
		hThread[i] = CreateThread(NULL, // default security attributes 
			0,                           // use default stack size 
			(LPTHREAD_START_ROUTINE)ThreadFunc, // thread function 
			(LPVOID)randomDigits,                    // no thread function argument 
			0,                       // use default creation flags 
			&IDThread);              // returns thread identifier 

	  // Check the return value for success. 
		if (hThread[i] == NULL)
			ErrorExit((LPSTR)"CreateThread error\n");
	}

	for (i = 0; i < thread_count; i++)
		WaitForSingleObject(hThread[i], INFINITE);

	TlsFree(dwTlsIndex);
	TlsFree(dwLocalArray);
	TlsFree(dwLocalSum);
	for (int i = 0; i < 10; i++)
	{
		TlsFree(dwGreatestArray[i]);
	}
	return 0;
}

void ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);
	ExitProcess(0);
}