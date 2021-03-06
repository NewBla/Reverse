#include "stdafx.h"
#include <Windows.h>
#include <exception>

LONG WINAPI CallBack(EXCEPTION_POINTERS* Excp);
VOID Tip(void);
int main()
{

	SetUnhandledExceptionFilter(CallBack);
	printf("%d", sizeof(long long));
	//RaiseException(0xC000005, 0, 0, 0);
	__asm
	{
		mov eax, 0
		jmp eax
	}


	printf("Exception Handled In main \n");
	system("pause");
	return 0;
}

LONG WINAPI CallBack(EXCEPTION_POINTERS* Excp)
{

	MessageBox(0, L"Error", L"Error", MB_OK);
	printf("Error Address: %08X \n", Excp->ExceptionRecord->ExceptionAddress);
	printf("EAX: %08X \n", Excp->ContextRecord->Eax);
	printf("EBX: %08X \n", Excp->ContextRecord->Ebx);
	printf("ECX: %08X \n", Excp->ContextRecord->Ecx);
	printf("ESP: %08X \n", Excp->ContextRecord->Esp);
	printf("EBP: %08X \n", Excp->ContextRecord->Ebp);
	printf("EIP: %08X \n",  Excp->ContextRecord->Eip);
	printf("DR0: %08X \n", Excp->ContextRecord->Dr0);
	printf("DR1: %08X \n", Excp->ContextRecord->Dr1);
	printf("DR2: %08X \n", Excp->ContextRecord->Dr2);
	printf("DR3: %08X \n", Excp->ContextRecord->Dr3);
	printf("DR6: %08X \n", Excp->ContextRecord->Dr6);
	printf("DR7: %08X \n", Excp->ContextRecord->Dr7);
	Excp->ContextRecord->Dr0 = 0x12345678;
	Excp->ContextRecord->Dr1 = 0xABCDEF;
	Excp->ContextRecord->Dr2 = 0x1FEDF;
	Excp->ContextRecord->Dr3 = 0x123458;
	Excp->ContextRecord->Dr6 = 0x12DA78;

	Excp->ContextRecord->Eax = (DWORD)Tip;
	Excp->ContextRecord->Eip = (DWORD)Tip;
	
	printf("Exception Handled \n");
	system("pause");
	return -1;
}
VOID Tip(void)
{
   MessageBox(0, L"EAX have been Modified", L"TIP", MB_OK);
}



