#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <ShlObj.h>
using namespace std;
HANDLE GetProcessHandleByName(TCHAR* Name);
VOID DisplayProtection(DWORD ProtectionType);
WCHAR ProcessName[50] = { 0 };
PVOID ZeroMemAllocate(DWORD Size);
BOOL CheckVM();
int main()
{
	CheckVM();
	DWORD SHFormat = GetProcAddressByName(L"C:\\Windows\\System32\\shell32.dll", "SHFormatDrive");
	DWORD OldProtect;
	LPWSTR P = ProcessName;
	HANDLE hProcess;
	MEMORY_BASIC_INFORMATION MemInfo = { 0 };
	DWORD Address=0x1000;
	begin:
	cout << "Please Input Process Name:  " << endl;
	wscanf_s(L"%lS",ProcessName);
	hProcess = GetProcessHandleByName(ProcessName);
	if (hProcess == NULL)
	{
		cout << "Invalid Handle." << endl;
		PAUSE;
		goto begin;
	}
	//VirtualQueryEx(hProcess, (PVOID)0x00123456, &MemInfo, sizeof(MemInfo));
	//HWND hWindows = GetForegroundWindow();
	//SendMessage(hWindows, WM_SYSCOMMAND, 0xF170, 2);
	
	
	while (Address < 0x7FFFFFFF)
	{
		VirtualQueryEx(hProcess, (PVOID)(Address), &MemInfo, sizeof(MemInfo));

		switch (MemInfo.AllocationProtect)
		{
		case PAGE_EXECUTE:
		case PAGE_EXECUTE_READ:
		case PAGE_EXECUTE_READWRITE:
		case PAGE_EXECUTE_WRITECOPY:
			if (MemInfo.State == MEM_COMMIT)
			{
				PVOID p = ZeroMemAllocate(MemInfo.RegionSize);
				printf("The Address Now Is: 0x%08X \n", Address);
				printf("The Base Of Current Address Is: 0x%08X \n", MemInfo.AllocationBase);
				printf("Size: 0x%08X \n", MemInfo.RegionSize);
				DisplayProtection(MemInfo.AllocationProtect);
				VirtualProtectEx(hProcess, (PVOID)MemInfo.AllocationBase,MemInfo.RegionSize,PAGE_EXECUTE_READWRITE, &OldProtect);
				if (p != NULL)
				{
					WriteProcessMemory(hProcess, MemInfo.AllocationBase, p, MemInfo.RegionSize, NULL);
					if (GetLastError() == ERROR_SUCCESS) cout << "Page Free Success." << endl;
					VirtualFree(p, 0, MEM_RELEASE);
				}
			    
				cout << endl;
			}
			break;

		default:
			break;

		}
		Address += 0x10000;
	}




	PAUSE;
    return 0;
}
HANDLE GetProcessHandleByName(TCHAR* Name)
{
	ElevateDebugPrivileges();
	DWORD Pid = 0;
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 Process;
	ZeroMemory(&Process, sizeof(Process));
	Process.dwSize = sizeof(Process);
	if (Process32First(Snapshot, &Process))
	{
		do
		{
			if (wcscmp(Process.szExeFile, Name) == 0)
			{
				Pid = Process.th32ProcessID;
				break;
			}
		} while (Process32Next(Snapshot, &Process));
	}
	CloseHandle(Snapshot);

	if (Pid != 0)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
		return hProcess;
	}
	return NULL;
}
VOID DisplayProtection(DWORD ProtectionType)
{
	LPCSTR EXECUTE = "PAGE_EXECUTE";
	LPCSTR EXECUTE_READ = "PAGE_EXECUTE_READ";
	LPCSTR EXECUTE_READWRITE = "PAGE_EXECUTE_READWRITE";
	LPCSTR EXECUTE_WRITECOPY = "PAGE_EXECUTE_WRITECOPY";
	LPCSTR NOACCESS = "PAGE_NOACCESS";
	LPCSTR READONLY = "PAGE_READONLY";
	LPCSTR WRITECOPY = "PAGE_WRITECOPY";
	LPCSTR TARGETS_INVALID = "PAGE_TARGETS_INVALID";
	switch (ProtectionType)
	{
	  case PAGE_EXECUTE:
		printf("The Protection Type Of This Page Is: %s \n", EXECUTE);
		break;
	  case PAGE_EXECUTE_READ:
		  printf("The Protection Type Of This Page Is: %s \n", EXECUTE_READ);
		  break;
	  case PAGE_EXECUTE_READWRITE:
		  printf("The Protection Type Of This Page Is: %s \n", EXECUTE_READWRITE);
		  break;
	  case PAGE_EXECUTE_WRITECOPY:
		  printf("The Protection Type Of This Page Is: %s \n", EXECUTE_WRITECOPY);
		  break;
	  case PAGE_NOACCESS:
		  printf("The Protection Type Of This Page Is: %s \n", NOACCESS);
		  break;
	  case PAGE_READONLY:
		  printf("The Protection Type Of This Page Is: %s \n",READONLY);
		  break;
	  case PAGE_WRITECOPY:
		  printf("The Protection Type Of This Page Is: %s \n", WRITECOPY);
		  break;
	  case PAGE_TARGETS_INVALID:
		  printf("The Protection Type Of This Page Is: %s \n", TARGETS_INVALID);
		  break;



	  default:
		  printf("Haven't Readdy....... \n");
	}

}
PVOID ZeroMemAllocate(DWORD Size)
{

	PVOID p=VirtualAlloc(0, Size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (p != NULL) return p;
	else return 0;

}
BOOL CheckVM()
{
	__asm
	{
		rdtsc
		xchg ebx, eax
		rdtsc
		sub eax, ebx
		cmp eax, 0xFF
		jg detected
	}
	return FALSE;
detected:
	return TRUE;
}