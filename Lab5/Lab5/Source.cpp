#include <stdio.h>
#include <thread>         // std::thread
#include <mutex>
#include <Windows.h>

#define MUTEX_NAME test
int main()
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, "Myapp");// = OpenMutex(NULL, TRUE, MUTEX_NAME);
	DWORD result = WaitForSingleObject(hMutex, 0);
	if (result == WAIT_OBJECT_0)
	{
		printf("Is running");
	}
	else
	{
		printf("Application instance already exist");
		getchar();
		return 1;
	}
	while (true) {}
}