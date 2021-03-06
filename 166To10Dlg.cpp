#include <math.h>
#include "stdafx.h"
#include "166To10.h"
#include "166To10Dlg.h"
#include "afxdialogex.h"
#include <Windows.h>
LPTSTR HexToDec(LPTSTR lpHex);
LPTSTR HexToBin(LPTSTR lpHex);
LPTSTR DecToHex(LPTSTR lpDec);
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy166To10Dlg dialog
HWND hW;
HWND hHex;
HWND hDec;
CMy166To10Dlg::CMy166To10Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MY166TO10_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy166To10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HEX, Hex);
	DDX_Control(pDX, IDC_DEC, Dec);
	DDX_Control(pDX, IDC_BIN, Bin);
}

BEGIN_MESSAGE_MAP(CMy166To10Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_HEX, &CMy166To10Dlg::OnEnChangeHex)
//	ON_EN_CHANGE(IDC_DEC, &CMy166To10Dlg::OnEnChangeDec)
    ON_EN_CHANGE(IDC_DEC, &CMy166To10Dlg::OnEnChangeDec)
END_MESSAGE_MAP()


// CMy166To10Dlg message handlers

BOOL CMy166To10Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy166To10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	hW = ::GetActiveWindow();
	hHex = ::GetDlgItem(hW, IDC_HEX);
	hDec= ::GetDlgItem(hW, IDC_DEC);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy166To10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



VOID CMy166To10Dlg::OnEnChangeHex()
{
	HWND hW = ::GetActiveWindow();
	WCHAR HexB[9] = { 0 };
	LPTSTR lpString= HexB;
	int MaxCount=9;
	HANDLE hFocus=GetFocus();
	if (::GetDlgItemText(hW, IDC_HEX, lpString, MaxCount) == 0)
	{
		::SetDlgItemText(hW, IDC_BIN, L"");
		::SetDlgItemText(hW, IDC_DEC, L""); 
	}

	else
	{
		lpString = HexToDec(lpString);
		::SetDlgItemText(hW, IDC_DEC, lpString);//这里已经是10进制了.
		lpString = HexToBin(lpString);
		::SetDlgItemText(hW, IDC_BIN, lpString);
	}

}
LPTSTR HexToDec(LPTSTR lpHex)
{
	LPTSTR Temp = lpHex;
	int Length=lstrlenW(lpHex);
	for (; Length > 0; Length--)
	{
		if ((*lpHex < 0x30) || (*lpHex > 0x39 && *lpHex < 0x41) || (*lpHex > 0x46))
		{
			return 0;
		}
		lpHex++;
	}
	lpHex = Temp;
	BYTE Hex[8] = { 0 };
	for (int i = 0; i <= 7&&*lpHex!=0; i++)
	{
		if (*lpHex >= 0x30 && *lpHex <= 0x39)
		{
			Hex[i] = *lpHex - 0x30;
			lpHex++;
			continue;
		}
		if (*lpHex >= 0x41 && *lpHex <= 0x46)
		{
			Hex[i] = *lpHex - 0x37;
			lpHex++;
		}
	}
	lpHex = Temp;
	Length = lstrlenW(lpHex);
	DWORD64 Sum = 0;
	for (int i = 0; i <= 7 && Hex[i] != 0; i++)
	{
		Sum  = Sum+Hex[i] * pow(16, Length-1);
		Length--;
	}
	WCHAR Buffer[50] = { 0 };
	wsprintf(Buffer, L"%u", Sum);
	return (LPTSTR)Buffer;
}
LPTSTR HexToBin(LPTSTR lpHex)
{
	int Length = lstrlenW(lpHex);
	int i = 0;
	BYTE Dec[8] = { 0 };
	for (i = 1; i <= Length; i++)
	{
		Dec[i-1] = *lpHex - 0x30;
		lpHex++;
	}
	DWORD64 Sum = 0;
	for (i = 0; i <= 7; i++)
	{
		Sum = Sum + Dec[i] * pow(10,Length - 1);
		Length--;
	}
	WCHAR Bin[64] = { 0 };
	WCHAR Bin2[64] = { 0 };
	i = 0;
	DWORD64 Quo = Sum / 2;
	if (Quo == 0)
	{
		Bin2[0] = 0x31;
		return Bin2;
	}
	while (Quo != 0)
	{
		Bin[i] = Sum % 2 + 0x30;
		Quo = Sum / 2;
		Sum = Quo;
		i++;
	}
	Length = lstrlenW(Bin);
	for (i = 0; i <=Length; i++)
	{
		Bin2[i] = Bin[Length - i - 1];
	}
	return Bin2;
}
LPTSTR DecToHex(LPTSTR lpDec)
{
	LPTSTR Temp = lpDec;
	int i = 0;
	int Length = lstrlenW(lpDec);
	for (; Length > 0; Length--)
	{
		if (*lpDec < 0x30 || *lpDec>0x39)
		{
			return 0;
		}
		lpDec++;
	}
	lpDec = Temp;
	Length = lstrlenW(lpDec);
	BYTE Dec[10] = { 0 };
	for (i = 0; i <= Length; i++)
	{
		Dec[i] = *lpDec - 0x30;
	}
	DWORD64 Sum = 0;

	for (i = 0; i <= 9; i++)
	{
		Sum = Sum + Dec[i] * pow(10, Length - 1);
		Length--;
	}

	WCHAR Buffer[50] = { 0 };
	wsprintf(Buffer, L"%X", Sum);
	return (LPTSTR)Buffer;



}


void CMy166To10Dlg::OnEnChangeDec()
{

		HWND hW = ::GetActiveWindow();
		WCHAR DecB[10] = { 0 };
		LPTSTR lpString = DecB;
		int MaxCount = 10;
		HANDLE hFocus = GetFocus();
		if (::GetDlgItemText(hW, IDC_DEC, lpString, MaxCount) == 0)
		{
			::SetDlgItemText(hW, IDC_BIN, L"");
			::SetDlgItemText(hW, IDC_HEX, L"");
		}

		else
		{
			lpString = DecToHex(lpString);
			::SetDlgItemText(hW, IDC_HEX, lpString);//这里已经是10进制了.
		}


}
