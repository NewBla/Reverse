#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "FunctionDef.h"
using namespace std;
int main()
{
	BYTE L0x606060[4] = {0x60,0x60,0x60,0};
	DWORD EDX[4] = { 0 };
	char* p = (char*)L0x606060;
	Func00463080(L0x606060, (PBYTE)EDX, strlen(p));


    return 0;
}
PBYTE Func00463080(PBYTE Source,PBYTE Dest,int Length)
{
	DWORD Local23[22] = { 0 };
	Local23[0] = 0x67452301;
	Local23[1] = 0xEFCDAB89;
	Local23[2] = 0x98BADCFE;
	Local23[3] = 0x10325476;
	Func00462F84(Local23,Source,Length);//本函数对Local32做处理,使用传进来的Source也就是0x00606060
	Func00463008(Local23,(PDWORD)Dest);

	return Dest;
}
VOID Func00462F84(PDWORD Source, PBYTE Dest, UINT LoopNum)  //Local23=Source
{
	UINT Num = LoopNum;
	Num = Num * 8;
	DWORD EAX = (Source[4] >> 3) & 0x3F;
	Source[4] = Source[4] + Num;
	if (Num>Source[4])
	{
		Source[5] += 1;
	}
	Source[5] += (LoopNum >> 0x1D);
	UINT  Num1 = 0x40;
	Num1 = Num1 - EAX;
	PBYTE Source7= (PBYTE)&Source[6];
	if (Num1>LoopNum)
	{
		Num1 = 0;
		Strcopy(Source7+EAX, &Dest[Num1], LoopNum - Num1);
	}
	else
	{
		Strcopy(Source7 + EAX,Dest, Num1);
		Func0046281C(&Source[6], Source);
		if (LoopNum < Num1 + 0x3F)
		{
			EAX = 0;
			Strcopy(Source7 + EAX, &Dest[Num1], LoopNum - Num1);
		}
	}
}

VOID Func00463008(PDWORD Input,PDWORD Output)
{  
	BYTE Global0046E7DC[64];
	Global0046E7DC[0] = 0x80;
	for (int i = 1; i <= 63; i++)
	{
		Global0046E7DC[i]=0;
	}
	DWORD ESP[2] = { 0 };
	PBYTE Input4 =(PBYTE)(Input + 4);
	Func004627DC(Input4,(PBYTE)ESP,2);
	if (((Input[4] >> 3) & 0x3F) < 0x38)
	     {
		Func00462F84(Input,Global0046E7DC, 0x38 - ((Input[4] >> 3) & 0x3F));//
		Func00462F84(Input, (PBYTE)ESP,8);
		for (int i = 0; i <= 3; i++)
		{
			Output[i] = Input[i];
		}
		//Func004627DC((PBYTE)Input, (PBYTE)Output,3);
	    }
}

VOID Func0046281C(PDWORD Source, PDWORD Dest)
{
	DWORD D0019EF08[22] = { 0 };
	D0019EF08[0] = (DWORD)Source;
	D0019EF08[1] = (DWORD)Dest;
	PDWORD EBX = &D0019EF08[2];
	PDWORD ESI  =  &D0019EF08[3];
	PDWORD EDI = &D0019EF08[4];
	PDWORD EBP= &D0019EF08[5];
	PDWORD EDX=&D0019EF08[6];
	Func004627A8((PBYTE)Source, EDX, 0x40);
	*EBX = Dest[0];
	*ESI = Dest[1];
	*EDI = Dest[2];
	*EBP = Dest[3];
	Func004626D8(*EBP, &D0019EF08[6], 0x7, 0xD76AA478,EBX,*EDI, *ESI);
	Func004626D8(*EDI, &D0019EF08[7], 0xC, 0xE8C7B756, EBP, *ESI, *EBX);
	Func004626D8(*ESI, &D0019EF08[8], 0x11, 0x242070DB, EDI, *EBX, *EBP);
	Func004626D8(*EBX, &D0019EF08[9], 0x16, 0xC1BDCEEE, ESI, *EBP, *EDI);

	Func004626D8(*EBP, &D0019EF08[10], 0x7, 0xF57C0FAF, EBX, *EDI, *ESI);
	Func004626D8(*EDI, &D0019EF08[11], 0xC, 0x4787C62A, EBP, *ESI, *EBX);
	Func004626D8(*ESI, &D0019EF08[12], 0x11, 0xA8304613, EDI, *EBX, *EBP);
	Func004626D8(*EBX, &D0019EF08[13], 0x16, 0xFD469501, ESI, *EBP, *EDI);

	Func004626D8(*EBP, &D0019EF08[14], 0x7, 0x698098D8, EBX, *EDI, *ESI);
	Func004626D8(*EDI, &D0019EF08[15], 0xC, 0x8B44F7AF, EBP, *ESI, *EBX);
	Func004626D8(*ESI, &D0019EF08[16], 0x11, 0xFFFF5BB1, EDI, *EBX, *EBP);
	Func004626D8(*EBX, &D0019EF08[17], 0x16, 0x895CD7BE, ESI, *EBP, *EDI);

	Func004626D8(*EBP, &D0019EF08[18], 0x7, 0x6B901122, EBX, *EDI, *ESI);
	Func004626D8(*EDI, &D0019EF08[19], 0xC, 0xFD987193, EBP, *ESI, *EBX);
	Func004626D8(*ESI, &D0019EF08[20], 0x11, 0xA679438E, EDI, *EBX, *EBP);
	Func004626D8(*EBX, &D0019EF08[21], 0x16, 0x49B40821, ESI, *EBP, *EDI);


	Func0046270C(*EBP, &D0019EF08[7], 0x5, 0xF61E2562, EBX, *EDI, *ESI);
	Func0046270C(*EDI, &D0019EF08[12], 0x9, 0xC040B340, EBP, *ESI, *EBX);
	Func0046270C(*ESI, &D0019EF08[17], 0xE, 0x265E5A51, EDI, *EBX, *EBP);
	Func0046270C(*EBX, &D0019EF08[6], 0x14, 0xE9B6C7AA, ESI, *EBP, *EDI);

	Func0046270C(*EBP, &D0019EF08[11], 0x5, 0xD62F105D, EBX, *EDI, *ESI);
	Func0046270C(*EDI, &D0019EF08[16], 0x9, 0x2441453, EBP, *ESI, *EBX);
	Func0046270C(*ESI, &D0019EF08[21], 0xE, 0xD8A1E681, EDI, *EBX, *EBP);
	Func0046270C(*EBX, &D0019EF08[10], 0x14, 0xE7D3FBC8, ESI, *EBP, *EDI);

	Func0046270C(*EBP, &D0019EF08[15], 0x5, 0x21E1CDE6, EBX, *EDI, *ESI);
	Func0046270C(*EDI, &D0019EF08[20], 0x9, 0xC33707D6, EBP, *ESI, *EBX);
	Func0046270C(*ESI, &D0019EF08[9], 0xE, 0xF4D50D87, EDI, *EBX, *EBP);
	Func0046270C(*EBX, &D0019EF08[14], 0x14, 0x455A14ED, ESI, *EBP, *EDI);

	Func0046270C(*EBP, &D0019EF08[19], 0x5, 0xA9E3E905, EBX, *EDI, *ESI);
	Func0046270C(*EDI, &D0019EF08[8], 0x9, 0xFCEFA3F8, EBP, *ESI, *EBX);
	Func0046270C(*ESI, &D0019EF08[13], 0xE, 0x676F02D9, EDI, *EBX, *EBP);
	Func0046270C(*EBX, &D0019EF08[18], 0x14, 0x8D2A4C8A, ESI, *EBP, *EDI);

	Func00462740(*EBP, &D0019EF08[11], 0x4, 0xFFFA3942, EBX, *EDI, *ESI);
	Func00462740(*EDI, &D0019EF08[14], 0xB, 0x8771F681, EBP, *ESI, *EBX);
	Func00462740(*ESI, &D0019EF08[17], 0x10, 0x6D9D6122, EDI, *EBX, *EBP);
	Func00462740(*EBX, &D0019EF08[20], 0x17, 0xFDE5380C, ESI, *EBP, *EDI);

	Func00462740(*EBP, &D0019EF08[7], 0x4, 0xA4BEEA44, EBX, *EDI, *ESI);
	Func00462740(*EDI, &D0019EF08[10], 0xB, 0x4BDECFA9, EBP, *ESI, *EBX);
	Func00462740(*ESI, &D0019EF08[13], 0x10, 0xF6BB4B60, EDI, *EBX, *EBP);
	Func00462740(*EBX, &D0019EF08[16], 0x17, 0xBEBFBC70, ESI, *EBP, *EDI);

	Func00462740(*EBP, &D0019EF08[19], 0x4, 0x289B7EC6, EBX, *EDI, *ESI);
	Func00462740(*EDI, &D0019EF08[6], 0xB, 0xEAA127FA, EBP, *ESI, *EBX);
	Func00462740(*ESI, &D0019EF08[9], 0x10, 0xD4EF3085, EDI, *EBX, *EBP);
	Func00462740(*EBX, &D0019EF08[12], 0x17, 0x4881D05, ESI, *EBP, *EDI);

	Func00462740(*EBP, &D0019EF08[15], 0x4, 0xD9D4D039, EBX, *EDI, *ESI);
	Func00462740(*EDI, &D0019EF08[18], 0xB, 0xE6DB99E5, EBP, *ESI, *EBX);
	Func00462740(*ESI, &D0019EF08[21], 0x10, 0x1FA27CF8, EDI, *EBX, *EBP);
	Func00462740(*EBX, &D0019EF08[8], 0x17, 0xC4AC5665, ESI, *EBP, *EDI);

	Func00462774(*EBP, &D0019EF08[6], 0x6, 0xF4292244, EBX, *EDI, *ESI);
	Func00462774(*EDI, &D0019EF08[13], 0xA, 0x432AFF97, EBP, *ESI, *EBX);
	Func00462774(*ESI, &D0019EF08[20], 0xF, 0xAB9423A7, EDI, *EBX, *EBP);
	Func00462774(*EBX, &D0019EF08[11], 0x15, 0xFC93A039, ESI, *EBP, *EDI);

	Func00462774(*EBP, &D0019EF08[18], 0x6, 0x655B59C3, EBX, *EDI, *ESI);
	Func00462774(*EDI, &D0019EF08[9], 0xA, 0x8F0CCC92, EBP, *ESI, *EBX);
	Func00462774(*ESI, &D0019EF08[16], 0xF, 0xFFEFF47D, EDI, *EBX, *EBP);
	Func00462774(*EBX, &D0019EF08[7], 0x15, 0x85845DD1, ESI, *EBP, *EDI);

	Func00462774(*EBP, &D0019EF08[14], 0x6, 0x6FA87E4F, EBX, *EDI, *ESI);
	Func00462774(*EDI, &D0019EF08[21], 0xA, 0xFE2CE6E0, EBP, *ESI, *EBX);
	Func00462774(*ESI, &D0019EF08[12], 0xF, 0xA3014314, EDI, *EBX, *EBP);
	Func00462774(*EBX, &D0019EF08[19], 0x15, 0x4E0811A1, ESI, *EBP, *EDI);

	Func00462774(*EBP, &D0019EF08[10], 0x6, 0xF7537E82, EBX, *EDI, *ESI);
	Func00462774(*EDI, &D0019EF08[17], 0xA, 0xBD3AF235, EBP, *ESI, *EBX);
	Func00462774(*ESI, &D0019EF08[8], 0xF, 0x2AD7D2BB, EDI, *EBX, *EBP);
	Func00462774(*EBX, &D0019EF08[15], 0x15, 0xEB86D391, ESI, *EBP, *EDI);

	*Dest=*Dest+ D0019EF08[2];
	Dest[1] = Dest[1] + D0019EF08[3];
	Dest[2] = Dest[2] + D0019EF08[4];
	Dest[3] = Dest[3] + D0019EF08[5];
}

VOID Func004626D8(DWORD Param1,PDWORD Param2,int Param3,DWORD Param4,PDWORD Param5,DWORD Param6,DWORD Param7)
{
	DWORD EDI = Param6;
	DWORD ESI = Param7;
	PDWORD EBX = Param5;
	DWORD ECX = Param1;
	DWORD EAX=Func0046268C(ECX, EDI, ESI)+*Param2+Param4;
	*Param5 = *Param5 + EAX;
	Func004626B8(EBX, Param3);
	*EBX = *EBX + ESI;
}

VOID Func00462740(DWORD Param1, PDWORD Param2, int Param3, DWORD Param4, PDWORD Param5, DWORD Param6, DWORD Param7)
{
	DWORD EDI = Param6;
	DWORD ESI = Param7;
	PDWORD EBX = Param5;
	DWORD ECX = Param1;
	DWORD EAX = Func004626A4(ECX, EDI, ESI) + *Param2 + Param4;
	*Param5 = *Param5 + EAX;
	Func004626B8(EBX, Param3);
	*EBX = *EBX + ESI;
}

VOID Func0046270C(DWORD Param1, PDWORD Param2, int Param3, DWORD Param4, PDWORD Param5, DWORD Param6, DWORD Param7)
{
	DWORD EDI = Param6;
	DWORD ESI = Param7;
	PDWORD EBX = Param5;
	DWORD ECX = Param1;
	DWORD EAX = Func00462698(ECX, EDI, ESI) + *Param2 + Param4;
	*Param5 = *Param5 + EAX;
	Func004626B8(EBX, Param3);
	*EBX = *EBX + ESI;
}

VOID Func00462774(DWORD Param1, PDWORD Param2, int Param3, DWORD Param4, PDWORD Param5, DWORD Param6, DWORD Param7)
{
	DWORD EDI = Param6;
	DWORD ESI = Param7;
	PDWORD EBX = Param5;
	DWORD ECX = Param1;
	DWORD EAX = Func004626AC(ECX, EDI, ESI) + *Param2 + Param4;
	*Param5 = *Param5 + EAX;
	Func004626B8(EBX, Param3);
	*EBX = *EBX + ESI;
}


DWORD Func004626AC(DWORD ECX, DWORD EDX, DWORD EAX)
{
	EAX = EAX | (~ECX);
	return EDX^EAX;
}

DWORD Func004626A4(DWORD ECX, DWORD EDX, DWORD EAX)
{
	return ECX^EAX^EDX;
}

DWORD Func0046268C(DWORD ECX,DWORD EDX,DWORD EAX)
{
	EDX = EDX&EAX;
	EAX = ~EAX;
	ECX = EAX&ECX;
	EDX = EDX | ECX;
	EAX = EDX;
	return EAX;
}

DWORD Func00462698(DWORD ECX, DWORD EDX, DWORD EAX)
{
	EAX = ECX&EAX;
	ECX = ~ECX;
	EDX &= ECX;
	EAX |= EDX;
	return EAX;
}


VOID Func004626B8(PDWORD EAX,DWORD EDX)
{
	DWORD ECX = 0x20;
	DWORD EBX = EDX;
	ECX = ECX - EBX;
	EBX = *EAX;
	EBX = EBX >> ECX;
	ECX = EDX;
	EDX = *EAX;
	EDX =EDX<< ECX;
	EBX |= EDX;
	*EAX = EBX;
}

VOID Func004627DC(PBYTE Source, PBYTE Dest, int LoopNum)
{

	for (; LoopNum >= 0; LoopNum--)
	{
		*Dest = (*Source) & 0xFF;
		Dest++;

		*Dest = ((*Source) >> 8) & 0xFF;
	    Dest++;

		*Dest = ((*Source) >> 0x10) & 0xFF;
		Dest++;

		*Dest = ((*Source) >> 0x18) & 0xFF;
		Dest++;
      
		Source += 4;
	}

}

int Func004627A8(PBYTE EAX,PDWORD EDX,int Loop)
{
	Loop = Loop >> 2;
	for (; Loop > 0; Loop--)
	{
		*EDX = *EAX;
		EAX++;

		*EDX |= ((*EAX) << 0x8);
		EAX++;

		*EDX |= ((*EAX) << 0x10);
		EAX++;

		*EDX |= ((*EAX) << 0x18);
		EAX++;

		EDX = EDX + 1;
	}
	return 0;

}

int Strcopy(PBYTE StartAddress,PBYTE Str,int CopyNum) 
{
	if (CopyNum == 0||StartAddress==0||Str==0) return 0;

	for (int i = 0; i <= CopyNum; i++)
	{
		StartAddress[i] = Str[i];
	}
	return CopyNum;
}