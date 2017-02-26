#include "stdafx.h"
#include "Tool.h"
#include "ToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
std::string AccountFileName("option.ini");
int dbfnum = 1;
std::string dbfname[200];

int aotostate = 0;


std::string source;
std::string target;

std::string targetfilename;


 

 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string Trim(string& str)
{
	str.erase(0, str.find_first_not_of(" \t\r\n"));

	str.erase(str.find_last_not_of(" \t\r\n") + 1);

	return str;
}

CString FillZero(CString str)
{
	/*
	while (str.GetLength()<6)
	{
	
		str = "0" + str;
	}
	return str;
	*/
	return _T("0");

}
//CString thisdate;
CString releasedbfname;

#define BUFLEN   1000
bool deletestate = false;

 


//AES加密


//Aes字符串加密



//字符ASCII码值到字符字面值的转换 如 '0'转换成0， 'a'转换成10
int CReportToolDlg::char2num(TCHAR ch)
{
	if (ch >= _T('0') && ch <= _T('9'))return ch - _T('0');
	else if (ch >= _T('a') && ch <= _T('f'))return ch - _T('a') + 10;
	return -1;
}


BOOL CReportToolDlg::WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
{
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
	if (dwSize < dwMinSize)
	{
		return FALSE;
	}
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwSize, NULL, FALSE);
	return TRUE;
}



BOOL CReportToolDlg::MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	// Get the required size of the buffer that receives the Unicode 
	// string. 
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);

	if (dwSize < dwMinSize)
	{
		return FALSE;
	}


	// Convert headers from ASCII to Unicode.
	MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
	return TRUE;
}



//Aes字符串加密
BSTR CReportToolDlg::OnBAesEn(wchar_t *wText)
{
	// TODO: Add your control notification handler code here
	//unsigned 
	char inBuff[50], ouBuff[50];
	//int strlength=50;
	//char inBuff[50],ouBuff[50];
	memset(inBuff, 0, 50);
	memset(ouBuff, 0, 50);
	//wchar_t wText[16] = {L"abc"};

	//wchar_t wText[10] = {L"函数示例"};
	// char sText[20]= {0};
	//WCharToMByte(wText,sText,sizeof(sText)/sizeof(sText[0]));
	//MByteToWChar(sText,wText,sizeof(wText)/sizeof(wText[0]));
	//WCharToMByte(wText,inBuff,sizeof(inBuff)/sizeof(inBuff[0]));
	WCharToMByte(wText, inBuff, sizeof(inBuff) / sizeof(inBuff[0]));
	//Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\xe\xf\x17\x11\x12\x3\x14\x10")),8);
	Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);


	//GetDlgItemText(IDC_EAesEn,(char*)inBuff,24);
	//if(strlen((char*)inBuff)>16)MessageBox("本例只能加密16字节的字符串，大于截断");

	aes.EncryptBlock(ouBuff, inBuff); //因为输出为16个字节，每个字节用两个字母或数字表示。
									  //实际输出是32个字母或数字,否则ASCII码值超出127的会变成乱码。
	CString str = _T(""), strTmp;

	for (int i = 0; i<16; i++)
	{
		//strTmp.Format(_T("%02x"),ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出
		strTmp.Format(_T("%02x"), ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出
		if (ouBuff[i]<0xff)
		{
			strTmp = strTmp.Right(2);
		}
		str += strTmp;
		//MessageBox(strTmp,_T("加密后"));
	}
	//strout=str;
	//AfxMessageBox(str);
	BSTR bstrText = str.AllocSysString();
	return bstrText;

}
////////////////////////////////////////////////////////////////////////////////////////////////
//Aes字符串解密

BSTR CReportToolDlg::OnBAesDe(wchar_t *wText)
{
	// TODO: Add your control notification handler code here
	//unsigned char inBuff[33],ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
	//因为有个结束符，

	unsigned char ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
							   //因为有个结束符，
	memset(ouBuff, 0, 25);

	Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);
	//Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\xe\xf\x17\x11\x12\x3\x14\x10")),8);
	//Aes aes((unsigned char*)key,24);
	CString theString(wText);
	LPTSTR inBuff = new TCHAR[theString.GetLength() + 1];
	_tcscpy_s(inBuff, wcslen(theString) + 1, theString);
	unsigned char temp[25];
	for (int j = 0; j<16; j++)
	{
		temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// 将字符字面表示的16进制ASCII码值转换成真正的ASCII码值
	}
	aes.DecryptBlock(ouBuff, temp);
	//AfxMessageBox(CString(ouBuff));  
	BSTR bstrText = CString(ouBuff).AllocSysString();
	return bstrText;
}

///////////////////

//超过16字符的字符串加密

BSTR CReportToolDlg::MoreStrOnBAesEn(CString leftstr)
{
	int StrLen = leftstr.GetLength();
	CString cutstr, Erystr;
	//szs.Format(_T("%d"),StrLen);
	//AfxMessageBox(szs);
	int blocknum = StrLen / 16;     //必须是英文字符，如果是中文字符，截取的是16个中文字符，但每次只加密8个字符，丢掉后8个
	int leftnum = StrLen % 16;
	for (int i = 1; i <= blocknum; i++)
	{
		cutstr = leftstr.Left(16);
		leftstr = leftstr.Right(leftstr.GetLength() - 16);
		//AfxMessageBox(cutstr+_T("/")+leftstr);
		Erystr = Erystr + OnBAesEn((LPWSTR)(LPCWSTR)cutstr);
		// wchar_t * STRV=(LPWSTR)(LPCWSTR)wholestr;

	}
	// AfxMessageBox(leftstr);
	//OnBAesEn(leftstr)
	Erystr = Erystr + OnBAesEn((LPWSTR)(LPCWSTR)leftstr);
	//AfxMessageBox(Erystr);
	BSTR bstrText = Erystr.MakeUpper().AllocSysString();
	return bstrText;
	// return Erystr;
}
//超过16字符的字符串加密


//超过16字符的字符串解密

BSTR CReportToolDlg::MoreStrOnBAesDe(CString leftstr)
{
	////解密
	leftstr = leftstr.MakeLower();
	// leftstr=MoreStrOnBAesDe(leftstr);
	int StrLen = leftstr.GetLength();
	CString cutstr, Erystr;

	//CString szs;
	//szs.Format(_T("%d"),StrLen);
	//AfxMessageBox(szs);
	int blocknum = StrLen / 32;     //必须是英文字符，如果是中文字符，截取的是16个中文字符，但每次只加密8个字符，丢掉后8个
	int leftnum = StrLen % 32;
	for (int i = 1; i <= blocknum; i++)
	{
		cutstr = leftstr.Left(32);
		leftstr = leftstr.Right(leftstr.GetLength() - 32);
		// AfxMessageBox(cutstr+_T("/")+leftstr);
		Erystr = Erystr + OnBAesDe((LPWSTR)(LPCWSTR)cutstr);
		// wchar_t * STRV=(LPWSTR)(LPCWSTR)wholestr;
	}
	//AfxMessageBox(leftstr);
	//OnBAesEn(leftstr)
	// Erystr=Erystr+OnBAesDe((LPWSTR)(LPCWSTR)leftstr);
	//AfxMessageBox(Erystr);
	BSTR bstrText = Erystr.AllocSysString();
	return bstrText;
	///解密
}


//超过16字符的字符串解密

//AES加密
BOOL CReportToolDlg::ReadConfigFile()
{

	CString str;
	GetDlgItem(IDC_ALLDBF)->GetWindowText(str);
 
 
	str = MoreStrOnBAesEn(str);




	SetDlgItemText(IDC_ZD, str);
	return TRUE;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

 
END_MESSAGE_MAP()


// CReportToolDlg 对话框



CReportToolDlg::CReportToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REPORTTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReportToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReportToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

 

 
	ON_WM_TIMER()
END_MESSAGE_MAP()




BOOL CReportToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



	 

	 SetTimer(1, 3000, NULL);
 
 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CReportToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReportToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CReportToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool finishstate = false;

void CReportToolDlg::OnTimer(UINT_PTR nIDEvent)
{
 
	switch (nIDEvent)
	{
	case 1:
		ReadConfigFile();

		
		break;
 

	}

	CDialogEx::OnTimer(nIDEvent);
}




/////////////////////////////////////////////////////////////////////////////


 

//检查文件是否存在并释放到硬盘






 