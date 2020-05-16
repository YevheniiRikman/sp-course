#include <thread>         // std::thread
#include <windows.h>


#define CRITICAL_MODE 0
#define NONCRITICAL_MODE 1
#define ARR_SIZE 50000000
#define THREAD_COUNT 3
int arr[ARR_SIZE];
CRITICAL_SECTION criticalSection;


void sum()
{
	int sum = 0;
	for (int i = 0; i < ARR_SIZE; i++)
	{
		sum += arr[i];
	}
	printf("sum: %d\n", sum);
}
void average()
{
	double avg = 0;
	for (int i = 0; i < ARR_SIZE; i++)
	{
		avg += arr[i];
	}
	printf("Avarage value: %f\n", avg / ARR_SIZE);
}
void maximum()
{
	int max = 0;
	for (int i = 0; i < ARR_SIZE; i++)
	{
		if (max < arr[i])
			max = arr[i];
	}
	printf("maximum value: %d\n", max);
}
void generateArr()
{
	for (int i = 0; i < ARR_SIZE; i++)
	{
		arr[i] = rand() % 100;
	}
}
DWORD WINAPI arraySum(LPVOID critical)
{
	if (static_cast<bool>(critical))
	{
		EnterCriticalSection(&criticalSection);
		sum();
		LeaveCriticalSection(&criticalSection);
	}
	else
		sum();
	return 0;
}
DWORD WINAPI arraySrednee(LPVOID critical)
{
	if (static_cast<bool>(critical))
	{
		EnterCriticalSection(&criticalSection);
		average();
		LeaveCriticalSection(&criticalSection);
	}
	else
		average();
	return 0;
}
DWORD WINAPI arrayMax(LPVOID critical)
{
	if (static_cast<bool>(critical))
	{
		EnterCriticalSection(&criticalSection);
		maximum();
		LeaveCriticalSection(&criticalSection);
	}
	else
		maximum();
	return 0;
}
int main()
{
	clock_t start;
	HANDLE threads[3];
	DWORD threadId;
	generateArr();
	InitializeCriticalSectionAndSpinCount(&criticalSection, 0);
	start = clock();
	threads[0] = CreateThread(NULL, 0, arraySum, LPVOID(TRUE), 0, &threadId);
	threads[1] = CreateThread(NULL, 0, arraySrednee, LPVOID(TRUE), 0, &threadId);
	threads[2] = CreateThread(NULL, 0, arrayMax, LPVOID(TRUE), 0, &threadId);
	WaitForMultipleObjects(3, threads, TRUE, INFINITE);
	start = clock() - start;
	DeleteCriticalSection(&criticalSection);
	for (HANDLE thread : threads)
	{
		CloseHandle(thread);
	}
	printf("Exclusion array time = %d\n", start);
	start = clock();
	threads[0] = CreateThread(NULL, 0, arraySum, LPVOID(FALSE), 0, &threadId);
	threads[1] = CreateThread(NULL, 0, arraySrednee, LPVOID(FALSE), 0, &threadId);
	threads[2] = CreateThread(NULL, 0, arrayMax, LPVOID(FALSE), 0, &threadId);
	WaitForMultipleObjects(3, threads, TRUE, INFINITE);
	start = clock() - start;
	for (HANDLE thread : threads)
	{
		CloseHandle(thread);
	}
	
	printf("no-exclusion array time = %d\n", start);
	return 0;
}