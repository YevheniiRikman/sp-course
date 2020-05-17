#include <stdio.h>
#include <locale.h>
#include <tchar.h>
#include <Windows.h>
#define WIDTH 7
#define DIV 1024
#define MB (1024*1024*1024)

void PrintError()
{
	LocalAlloc(LMEM_ZEROINIT, 1 << 32 - 1);
	DWORD err = GetLastError();
	char *text;
	FormatMessage(
		// use system message tables to retrieve error text
		FORMAT_MESSAGE_FROM_SYSTEM
		// allocate buffer on local heap for error text
		| FORMAT_MESSAGE_ALLOCATE_BUFFER
		// Important! will fail otherwise, since we're not 
		// (and CANNOT) pass insertion parameters
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
		err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&text,  // output 
		0, // minimum size for output buffer
		NULL);   // arguments - see note
	printf("%s",text);
}

void PrintInfo()
{
	printf("System info:\n");	
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	_tprintf(TEXT("dwNumberOfProcessors %*ld\n"),
		WIDTH, sysInfo.dwNumberOfProcessors);	
	_tprintf(TEXT("dwActiveProcessorMask %*ld\n"),
		WIDTH, sysInfo.dwActiveProcessorMask);	
	_tprintf(TEXT("dwAllocationGranularity %*ld\n"),
		WIDTH, sysInfo.dwAllocationGranularity);	
	_tprintf(TEXT("dwPageSize %*ld B\n"),
		WIDTH, sysInfo.dwPageSize);
	printf("lpMaximumApplicationAddress %x\n", sysInfo.lpMaximumApplicationAddress);
	printf("lpMinimumApplicationAddress %x\n", sysInfo.lpMinimumApplicationAddress);
	_tprintf(TEXT("wProcessorArchitecture %*ld   "),
		WIDTH, sysInfo.wProcessorArchitecture);
	switch (sysInfo.wProcessorArchitecture)
	{
		case PROCESSOR_ARCHITECTURE_INTEL:printf("PROCESSOR_ARCHITECTURE_INTEL x86");break;
		case PROCESSOR_ARCHITECTURE_AMD64:printf("PROCESSOR_ARCHITECTURE_INTEL x64");break;
		case PROCESSOR_ARCHITECTURE_UNKNOWN:printf("PROCESSOR_ARCHITECTURE_UNKNOWN");break;
	default:printf("PROCESSOR_ARCHITECTURE_UNKNOWN");
		break;
	}
	_tprintf(TEXT("\ndwProcessorTypes %*ld  "),
		WIDTH, sysInfo.dwProcessorType);
	switch (sysInfo.dwProcessorType)
	{
	case PROCESSOR_INTEL_386:printf("PROCESSOR_INTEL_386");break;
	case PROCESSOR_INTEL_486:printf("PROCESSOR_INTEL_486");break;
	case PROCESSOR_INTEL_PENTIUM:printf("PROCESSOR_INTEL_PENTIUM");break;
	case PROCESSOR_INTEL_IA64:printf("PROCESSOR_INTEL_IA64");break;
	case PROCESSOR_AMD_X8664:printf("PROCESSOR_AMD_X8664");break;
	default:printf("PROCESSOR_PROCESSOR_UNKNOWN");
		break;
	}
	_tprintf(TEXT("\nwProcessorLevel %*ld\n"),
		WIDTH, sysInfo.wProcessorLevel);
	_tprintf(TEXT("wProcessorRevision %*ld\n"),
		WIDTH, sysInfo.wProcessorRevision);
	_tprintf(TEXT("wReserved %*ld\n"),
		WIDTH, sysInfo.wReserved);

	printf("\nMemory info:\n");
	MEMORYSTATUS memInfo;
	GlobalMemoryStatus(&memInfo);

	printf("There is  %ld percent of memory in use.\n", memInfo.dwMemoryLoad);
	printf("There are %ld total KB of physical memory.\n", memInfo.dwTotalPhys);
	printf("There are %ld free  KB of physical memory.\n", memInfo.dwAvailPhys);
	printf("There are %ld total KB of paging file.\n", memInfo.dwTotalPageFile);
	printf("There are %ld free  KB of paging file.\n", memInfo.dwAvailPageFile);
	printf("There are %ld total KB of virtual memory.\n", memInfo.dwTotalVirtual);
	printf("There are %ld free  KB of virtual memory.\n", memInfo.dwAvailVirtual);	
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");
	if (argc == 2) {
		if (strcmp(argv[1], "-i") == 0)
		{
			PrintInfo();
		}
		else if (strcmp(argv[1], "-e") == 0)
		{
			PrintError();
		}
	}
}