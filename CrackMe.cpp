#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;
CHAR User[50] = { 0 };
CHAR Serial[50] = { 0 };
LPSTR User1 = User;
LPSTR Serial1 = Serial;
DWORD UserHandler(LPSTR User);
DWORD SerialHandler(LPSTR Serial);
int main()
{
	begin:
	cout << "Input The User Name : " << endl;
	cin >> User1;
	cout << "Input The Serial :" << endl;
	cin >> Serial1;

	printf("User: %08X \n", UserHandler(User1));
	printf("Serial: %08X \n", SerialHandler(Serial1));

	goto begin;
	system("pause");

    return 0;
}
DWORD UserHandler(LPSTR User)
{
	DWORD Sum = 0;
	while (*User != 0)
	{
		if (*User < 0x41)
		{
			return 0;
		}
		if (*User > 0x5A)
		{
			*User = *User - 0x20;
		}
		Sum = Sum + *User;
		User++;
	}
	return Sum ^ 0x5678;
}
DWORD SerialHandler(LPSTR Serial)
{
	DWORD Sum = 0;
	while (*Serial != 0)
	{
		Sum = Sum * 10 + *Serial - 0x30;
		Serial++;
	}
	return Sum ^ 0x1234;
}
PBYTE Splish(LPSTR User)
{
	int Length = strlen(User);
	if (!Length) return 0;
	BYTE UserHandled[50] = { 0 };
	for (int i = 0; i <= Length; i++)
	{
		*User = *User % 0xA;
		*User = *User^i + 2;
		if (*User >=10)
		{
			*User -= 10;
		}
		UserHandled[i] = *User;
		User++;
	}

	return UserHandled;

}