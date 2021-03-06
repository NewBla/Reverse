#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;
int main()
{

	int *p = new int[10];

	int *b = (int*)malloc(15);





	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	printf("Page Size: 0x%08X \n", SysInfo.dwPageSize);
	printf("AllocationGranularity: 0x%08X \n", SysInfo.dwAllocationGranularity);
	printf("MinimumApplicationAddress: 0x%08X \n", SysInfo.lpMinimumApplicationAddress);
	printf("MaximumApplicationAddress: 0x%08X \n", SysInfo.lpMaximumApplicationAddress);

	MEMORYSTATUS MemStatus;
	GlobalMemoryStatus(&MemStatus);

	printf("MemLoad: 0x%08X \n", MemStatus.dwMemoryLoad);
	printf("TotalPhys: 0x%08X \n", MemStatus.dwTotalPhys);
	printf("AvailPhys: 0x%08X \n", MemStatus.dwAvailPhys);
	printf("TotalPageFile: 0x%08X \n", MemStatus.dwTotalPageFile);
	printf("AvailPageFile: 0x%08X \n", MemStatus.dwAvailPageFile);
	printf("TotalVirtual: 0x%08X \n", MemStatus.dwTotalVirtual);
	printf("AvailVirtual: 0x%08X \n", MemStatus.dwAvailVirtual);
	cout << "Press Any Key To Allocate Memory ...." << endl;
	system("pause");
	PDWORD pVirtualAlloc =(PDWORD)VirtualAlloc(0, 1024 * 1024*2, MEM_COMMIT, PAGE_READWRITE);
	printf("New Memory Address: 0x%08X \n", pVirtualAlloc);

	cout << "Press Any Key To Free The New Memory....." << endl;

	system("pause");

	VirtualFree(pVirtualAlloc, 0, MEM_RELEASE);

	cout << "Press Any Key To Execute HeapAlloc ...." << endl;
	system("pause");


	HANDLE hHeap = GetProcessHeap();
	PDWORD pHeapAlloc=(PDWORD)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, 1024 * 1024 * 2);
	printf("New Memory Address: 0x%08X \n", pHeapAlloc);
	cout << "Press Any Key To Free The New Memory....." << endl;

	system("pause");

	HeapFree(hHeap, HEAP_NO_SERIALIZE, pHeapAlloc);


	cout << "Press Any Key To Allocate Memory From Stack ...." << endl;
	system("pause");

	CHAR A[1024*1000] = { 0 };
	printf("New Memory Address: 0x%08X \n", A);

	system("pause");


    return 0;
}

