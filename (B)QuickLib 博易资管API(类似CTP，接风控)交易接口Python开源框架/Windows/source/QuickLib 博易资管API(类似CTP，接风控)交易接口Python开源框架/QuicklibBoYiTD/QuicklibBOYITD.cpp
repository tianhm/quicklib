/*
1.本文件为Quicklib 期货博易API资管交易库底层代码
2.本文件及调用的库文件Quicklib 博易API(类似CTP，只是多一道风控网关)期货交易库和交易库遵循 开源协议GPL v3
简单的说：对基于GPL v3协议的源代码，若个人或机构仅仅是自己使用，则可以闭源。
若基于该开源代码，开发出程序或衍生产品用于商业行为则也必须开源。

Quciklib Python框架和工具遵循GPL v3协议包括：
（1）Quicklib CTP   期货行情库
（2）Quicklib CTP   期货交易库
（3）Quicklib CTP2  A股行情库
（4）Quicklib MOM模式  博易资管交易库
（用于接入资管投顾系统，MOM模式可实现私募进行投顾的选拔考核，并通过自己的风控系统接入实盘）

Quciklib Python框架和工具暂不遵循开源协议包括：
（5）Quicklib 监控器库（预警、监控、交易信号数据复制、跟单）（可免费试用）

对Quciklib开源库做出贡献的，并得到原始作者肯定的，将公布在http://www.quciklib.cn网站上，
并添加在《开源说明和感谢.txt》，并将该文件不断更新放入每一个新版本的Quicklib库里。

原始作者：QQ 147423661 林(王登高)
官方网站：http://www.quicklib.cn
官方QQ群：5172183(1群)、25884087(2群)
*/

#include "stdafx.h"
#include "QLCTPInterface.h"
#include "CTPTraderSpi.h"
using namespace std;

extern CRITICAL_SECTION g_csdata;
list <cmdcontent> cmdlist;
//list <cmdcontent>::iterator cmd_Iter;

list <CThostFtdcOrderField> orderlist;
//list <CThostFtdcOrderField>::iterator order_Iter;

list <CThostFtdcTradeField> tradelist;
//list <CThostFtdcTradeField>::iterator trade_Iter;

list <CThostFtdcAccountregisterField> qryaccountregisterlist;
//list <CThostFtdcAccountregisterField>::iterator qryaccountregister_Iter;


list <CThostFtdcRspTransferField> banktofuturebyfuturelist;
//list <CThostFtdcRspTransferField>::iterator banktofuturebyfuture_Iter;

list <CThostFtdcRspTransferField> futuretobankbyfuturelist;
//list <CThostFtdcRspTransferField>::iterator futuretobankbyfuture_Iter;


list <CThostFtdcQueryMaxOrderVolumeField>  querymaxordervolumelist;
//list <CThostFtdcQueryMaxOrderVolumeField>::iterator querymaxordervolume_Iter;


list <CThostFtdcInstrumentStatusField> InstrumentStatuslist;
//list <CThostFtdcInstrumentStatusField>::iterator InstrumentStatus_Iter;


list <CThostFtdcRspInfoField> errorlist;
//list <CThostFtdcRspInfoField>::iterator error_Iter;

list <CThostFtdcSettlementInfoConfirmField> settlementlist;
//list <CThostFtdcSettlementInfoConfirmField>::iterator settlement_Iter;

//估计字段要自己定义，或多个登录状态的定义
list <CThostFtdcRspUserLoginField> loginlist;
//list <CThostFtdcRspUserLoginField>::iterator login_Iter;

list <CThostFtdcUserLogoutField> loginoutlist;
//list <CThostFtdcUserLogoutField>::iterator loginout_Iter;

list <int> connectlist;
//list <int>::iterator connect_Iter;

///请求查询合约保证金率响应
list <CThostFtdcInstrumentMarginRateField> MarginRatelist;
//list <CThostFtdcInstrumentMarginRateField>::iterator MarginRate_Iter;

///请求查询合约手续费率响应
list <CThostFtdcInstrumentCommissionRateField> CommissionRatelist;
//list <CThostFtdcInstrumentCommissionRateField>::iterator CommissionRate_Iter;

 

 

#include <process.h>
HANDLE hEvent[MAX_EVENTNUM] = { NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL };

std::string gTDFrontAddr[3];
std::string gBrokerID;
std::string gUserID;
std::string gPassword;

std::string gSN;

HANDLE ghTradedVolMutex = NULL;
std::map<int, int> gOrderRef2TradedVol;

std::string gConfigFile("QuickLibTD.ini");

QLCTPTraderSpi gTraderSpi;

bool showpositionstate=false;


//AES加密
#include "Aes.h"  
#include <string>  
#include <algorithm>  
using namespace std;

//Aes字符串加密
string OnBAesEn(char *wText, char *key, int w)
{
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
	//WCharToMByte(wText, inBuff, sizeof(inBuff) / sizeof(inBuff[0]));
	//Aes aes((unsigned char*)"\x2\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x20\x21\x22\x23\x24\x2",32);

	//Aes aes((unsigned char*)_T("ddd0000000000000"),16);

	Aes aes((unsigned char*)key, 24);



	//GetDlgItemText(IDC_EAesEn,(char*)inBuff,24);
	//if(strlen((char*)inBuff)>16)MessageBox("本例只能加密16字节的字符串，大于截断");

	aes.EncryptBlock(ouBuff, wText); //因为输出为16个字节，每个字节用两个字母或数字表示。
									 //实际输出是32个字母或数字,否则ASCII码值超出127的会变成乱码。
	string str = "", strTmp;

	for (int i = 0; i<16; i++)
	{
		//strTmp.Format(_T("%02x"),ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出
		//strTmp.Format("%02x", ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出

		char temp[100] = { 0 };
		_snprintf_s(temp, sizeof(temp), sizeof(temp), "%02x", ouBuff[i]);
		strTmp = string(temp);


		if (ouBuff[i]<0xff)
		{
			//strTmp = strTmp.Right(2);

			strTmp = strTmp.substr(strTmp.size(), 2 - strTmp.size());
		}
		str += strTmp;
		//MessageBox(strTmp,_T("加密后"));
	}
	//strout=str;
	//AfxMessageBox(str);
	//BSTR bstrText = str.AllocSysString();
	//return bstrText;
	return str;
}
////////////////////////////////////////////////////////////////////////////////////////////////


//字符ASCII码值到字符字面值的转换 如 '0'转换成0， 'a'转换成10
int char2num(TCHAR ch)
{
	if (ch >= '0' && ch <= '9')return ch - '0';
	else if (ch >= 'a' && ch <= 'f')return ch - 'a' + 10;
	return -1;
}
//Aes字符串解密
string OnBAesDe(char *wText, char *key, int w)
{
	// TODO: Add your control notification handler code here
	//unsigned char inBuff[33],ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
	//因为有个结束符，

	unsigned char ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
							   //因为有个结束符，
	memset(ouBuff, 0, 25);
	//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17",24);
	//Aes aes((unsigned char*)_T("ddd0000000000000"),16);
	Aes aes((unsigned char*)key, 24);
	//CString theString(wText);
	string theString = (wText);
	char * inBuff = new char[theString.size() + 1];
	//_tcscpy_s(inBuff, theString.size() + 1, theString);

	strncpy_s(inBuff, sizeof(inBuff), theString.c_str(), theString.size() + 1);
	unsigned char temp[25];
	for (int j = 0; j<16; j++)
	{
		temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// 将字符字面表示的16进制ASCII码值转换成真正的ASCII码值
	}
	aes.DecryptBlock(ouBuff, temp);
	//AfxMessageBox(CString(ouBuff));  
	//BSTR bstrText = CString(ouBuff).AllocSysString();
	//return bstrText;

	return  (char*)(&ouBuff);
}






BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
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



BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
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


/*
//Aes字符串加密
string  OnBAesEn(char *wText)
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
//WCharToMByte(wText, inBuff, sizeof(inBuff) / sizeof(inBuff[0]));
//Aes aes((unsigned char*)"\x2\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x20\x21\x22\x23\x24\x2",32);

Aes aes((unsigned char*)"\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10", 16);

//Aes aes((unsigned char*)key,24);



//GetDlgItemText(IDC_EAesEn,(char*)inBuff,24);
//if(strlen((char*)inBuff)>16)MessageBox("本例只能加密16字节的字符串，大于截断");

//aes.EncryptBlock(ouBuff, inBuff); //因为输出为16个字节，每个字节用两个字母或数字表示。
aes.EncryptBlock(ouBuff, wText); //因为输出为16个字节，每个字节用两个字母或数字表示。
//实际输出是32个字母或数字,否则ASCII码值超出127的会变成乱码。
string str = "", strTmp;

for (int i = 0;i<16;i++)
{
//strTmp.Format(_T("%02x"),ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出
char temp[100] = {0};
sprintf_s(temp, sizeof(temp), "%02x", ouBuff[i]);
//strTmp.Format("%02x", ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出

strTmp = temp;
if (ouBuff[i]<0xff)
{
//strTmp = strTmp.Right(2);

strTmp = strTmp.substr(strTmp.size(), 2 - strTmp.size());
}
str += strTmp;
//MessageBox(strTmp,_T("加密后"));
}
//strout=str;
//AfxMessageBox(str);
//BSTR bstrText = str.AllocSysString();
//return bstrText;
return str;

}
////////////////////////////////////////////////////////////////////////////////////////////////
//Aes字符串解密
string OnBAesDe(char *wText)
{
// TODO: Add your control notification handler code here
//unsigned char inBuff[33],ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
//因为有个结束符，

unsigned char ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
//因为有个结束符，
memset(ouBuff, 0, 25);
//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17",24);
// Aes aes((unsigned char*)_T("ddd0000000000000"),16);
Aes aes((unsigned char*)"\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10", 16);

//Aes aes((unsigned char*)key,24);
string theString=(wText);
LPTSTR inBuff = new TCHAR[theString.size() + 1];
strncpy_s(inBuff, sizeof(inBuff), theString.c_str(), theString.size() + 1);
unsigned char temp[25];
for (int j = 0;j<16;j++)
{
temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// 将字符字面表示的16进制ASCII码值转换成真正的ASCII码值
}
aes.DecryptBlock(ouBuff, temp);
//AfxMessageBox(CString(ouBuff));
//BSTR bstrText = .AllocSysString();
//return bstrText;

return  (char*)(&ouBuff);
}



//Aes字符串加密
string OnBAesEn2(char *wText)
{
// TODO: Add your control notification handler code here
//unsigned
char inBuff[50], ouBuff[50];
//int strlength=50;
//char inBuff[50],ouBuff[50];
memset(inBuff, 0, 50);
memset(ouBuff, 0, 50);
//wchar_t wText[16] = {L"abc"};


//WCharToMByte(wText, inBuff, sizeof(inBuff) / sizeof(inBuff[0]));
//Aes aes((unsigned char*)"\x2\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x20\x21\x22\x23\x24\x2",32);

//Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10")),16);
Aes aes((unsigned char*)"\x9\xf\xa\x3\xa\x5\x15\xc\x1\xe\x13\x11\x17\x3\x11\x2", 16);

//Aes aes((unsigned char*)key,24);



//GetDlgItemText(IDC_EAesEn,(char*)inBuff,24);
//if(strlen((char*)inBuff)>16)MessageBox("本例只能加密16字节的字符串，大于截断");
//aes.EncryptBlock(ouBuff, inBuff); //因为输出为16个字节，每个字节用两个字母或数字表示。
aes.EncryptBlock(ouBuff, wText); //因为输出为16个字节，每个字节用两个字母或数字表示。
//实际输出是32个字母或数字,否则ASCII码值超出127的会变成乱码。
string str = "", strTmp;

for (int i = 0;i<16;i++)
{
//strTmp.Format(_T("%02x"),ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出
char temp[100] = { 0 };
sprintf_s(temp, sizeof(temp), "%02x", ouBuff[i]);


//strTmp.Format("%02x", ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出

strTmp = temp;

if (ouBuff[i]<0xff)
{
//strTmp = strTmp.Right(2);
strTmp = strTmp.substr(strTmp.size(), 2 - strTmp.size());
}
str += strTmp;
//MessageBox(strTmp,_T("加密后"));
}
//strout=str;
//AfxMessageBox(str);
//BSTR bstrText = str.AllocSysString();
//return bstrText;
return str;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//Aes字符串解密
string OnBAesDe2(char *wText)
{
// TODO: Add your control notification handler code here
//unsigned char inBuff[33],ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
//因为有个结束符，

unsigned char ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
//因为有个结束符，
memset(ouBuff, 0, 25);
//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17",24);
// Aes aes((unsigned char*)_T("ddd0000000000000"),16);
//	  Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10")),16);
Aes aes((unsigned char*) "\x9\xf\xa\x3\xa\x5\x15\xc\x1\xe\x13\x11\x17\x3\x11\x2", 16);
//Aes aes((unsigned char*)key,24);
string theString=(wText);
LPTSTR inBuff = new TCHAR[theString.size() + 1];
strncpy_s(inBuff, sizeof(inBuff), theString.c_str(),  theString.size() + 1);
unsigned char temp[25];
for (int j = 0;j<16;j++)
{
temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// 将字符字面表示的16进制ASCII码值转换成真正的ASCII码值
}
aes.DecryptBlock(ouBuff, temp);
//AfxMessageBox(CString(ouBuff));
//BSTR bstrText = .AllocSysString();
//return bstrText;

return (char*)(&ouBuff);
}
*/
//Aes字符串加密
/*
string OnBAesEn3(const char *wText)
{
// TODO: Add your control notification handler code here
//unsigned
char inBuff[25], ouBuff[25];
//int strlength=50;
//char inBuff[50],ouBuff[50];
memset(inBuff, 0, 25);
memset(ouBuff, 0, 25);
//wchar_t wText[16] = {L"abc"};

//wchar_t wText[10] = {L"函数示例"};
// char sText[20]= {0};
//WCharToMByte(wText,sText,sizeof(sText)/sizeof(sText[0]));
//MByteToWChar(sText,wText,sizeof(wText)/sizeof(wText[0]));
//WCharToMByte(wText,inBuff,sizeof(inBuff)/sizeof(inBuff[0]));
//WCharToMByte(wText, inBuff, sizeof(inBuff) / sizeof(inBuff[0]));
//Aes aes((unsigned char*)"\x2\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x20\x21\x22\x23\x24\x2",32);

//Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10")),16);
Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);

//Aes aes((unsigned char*)key,24);

strncpy_s(inBuff,sizeof(inBuff), wText,strlen(wText));


printf("inBuff %X\n", inBuff);
//GetDlgItemText(IDC_EAesEn,(char*)inBuff,24);
//if(strlen((char*)inBuff)>16)MessageBox("本例只能加密16字节的字符串，大于截断");
//aes.EncryptBlock(ouBuff, inBuff); //因为输出为16个字节，每个字节用两个字母或数字表示。
aes.EncryptBlock(ouBuff, inBuff); //因为输出为16个字节，每个字节用两个字母或数字表示。
//实际输出是32个字母或数字,否则ASCII码值超出127的会变成乱码。
string str = "", strTmp;
printf("ouBuff %X\n", ouBuff);
for (int i = 0;i<16;i++)
{
//strTmp.Format(_T("%02x"),ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出
//strTmp.Format("%02x", ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出

char temp[200] = {0};
sprintf_s(temp,sizeof(temp), "%02X", ouBuff[i]);



strTmp = string(temp);
if (ouBuff[i]<0xff)
{
//strTmp = strTmp.Right(2);
//strTmp = strTmp.substr(strTmp.size(), 2 - strTmp.size());

strTmp = strTmp.substr(0,16);
}
str += strTmp;
//MessageBox(strTmp,_T("加密后"));
}

printf("结果%s\n", str);
//strout=str;
//AfxMessageBox(str);
//BSTR bstrText = str.AllocSysString();
//return bstrText;
return str;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//Aes字符串解密
string OnBAesDe3(char *wText)
{

printf("执行");
// TODO: Add your control notification handler code here
//unsigned char inBuff[33],ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
//因为有个结束符，

unsigned char ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
//因为有个结束符，
memset(ouBuff, 0, 25);
//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17",24);
// Aes aes((unsigned char*)_T("ddd0000000000000"),16);
//	  Aes aes((unsigned char*)VMProtectDecryptStringW(_T("\x6\xf\x8\x9\xa\xb\x5\xd\xe\xf\x17\x11\x12\x3\x14\x10")),16);
Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);
//Aes aes((unsigned char*)key,24);
string  theString=(wText);
LPTSTR inBuff = new TCHAR[theString.size() + 1];
strncpy_s(inBuff, sizeof(inBuff), theString.c_str(),  theString.size() + 1);
unsigned char temp[25];
for (int j = 0;j<16;j++)
{
temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// 将字符字面表示的16进制ASCII码值转换成真正的ASCII码值
}
aes.DecryptBlock(ouBuff, temp);
//AfxMessageBox(CString(ouBuff));
//BSTR bstrText = .AllocSysString();
//return bstrText;

printf("%x\n", (char*)(&ouBuff));

return  (char*)(&ouBuff);
}
*/
//NEW
//Aes字符串加密
string  OnBAesEn(const char * strinput)
{
	// TODO: Add your control notification handler code here
	unsigned char inBuff[25], ouBuff[25];
	memset(inBuff, 0, 25);
	memset(ouBuff, 0, 25);
	//printf("c1\n");
	//Sleep(5000);
	//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17", 24);
	Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);
	//GetDlgItemText(IDC_EAesEn, (char*)inBuff, 24);

	strncpy_s((char*)inBuff, sizeof(inBuff), strinput, strlen(strinput));

	//printf("c2\n");
	//Sleep(5000);
	//if (strlen((char*)inBuff)>16)MessageBox("本例只能加密16字节的字符串，大于截断");

	aes.EncryptBlock(ouBuff, inBuff); //因为输出为16个字节，每个字节用两个字母或数字表示。
	string str = "", strTmp;		//实际输出是32个字母或数字,否则ASCII码值超出127的会变成乱码。
	for (int i = 0; i<16; i++)
	{
		char temp[100] = { 0 };
		_snprintf_s(temp, sizeof(temp), sizeof(temp), "%02x", ouBuff[i]);
		//strTmp.Format("%02x", ouBuff[i]);   //其实相当于把ouBuff的ASCII值这个数字以16进制的形式输出
		strTmp = temp;


		str += strTmp;
	}

	//printf("c3\n");
	//Sleep(5000);
	//MessageBox(str,"加密后");
	//SetDlgItemText(IDC_EAesEn, str);
	//printf("加密1次：%s\n", str.c_str());
	return str;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//Aes字符串解密
string OnBAesDe(const char * strinput)
{
	//printf("输入： %s\n", strinput);
	// TODO: Add your control notification handler code here
	unsigned char inBuff[33], ouBuff[25];  //还是要注意32个字符的字符串需要用33个字节来存储，
										   //因为有个结束符，
	memset(inBuff, 0, 25);
	memset(ouBuff, 0, 25);
	//Aes aes((unsigned char*)"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17", 24);
	Aes aes((unsigned char*)"\x3\xf\x8\x9\xa\x8\x15\xd\xe\xe\x17\x11\x12\x3\x11\x9", 16);
	//GetDlgItemText(IDC_EAesEn, (char*)inBuff, 33);
	strncpy_s((char*)inBuff, sizeof(inBuff), strinput, strlen(strinput));


	unsigned char temp[25] = { 0 };
	for (int j = 0; j<16; j++)
	{
		temp[j] = char2num(inBuff[2 * j]) * 16 + char2num(inBuff[2 * j + 1]);// 将字符字面表示的16进制ASCII码值转换成真正的ASCII码值
	}

	aes.DecryptBlock(ouBuff, temp);//"dda97ca4......ec0d7191"

								   //printf("解密：%s\n", ouBuff);

								   //SetDlgItemText(IDC_EAesDe, CString(ouBuff));
								   //Sleep(5000);
								   //return (char*)&ouBuff;
								   //string str = (char*)&ouBuff;
	return (char*)&ouBuff;
}

string MoreStrOnBAesEn(string leftstr)
{
	int StrLen = leftstr.size();
	string cutstr, Erystr;
	//printf("长度%d\n", StrLen);
	int blocknum = StrLen / 16;     //必须是英文字符，如果是中文字符，截取的是16个中文字符，但每次只加密8个字符，丢掉后8个
	int leftnum = StrLen % 16;
	printf("len[%d] blocknum[%d]\n", StrLen, blocknum);

	for (int i = 1; i <= blocknum; i++)
	{
		//printf("[%d] \n", i );
		//printf("[%d] [%d]\n", 16 * (i - 1), 16 * i);
		//printf("%s  [%d][%d]\n", leftstr.c_str(),16 * (i - 1), 16 * i);
		cutstr = leftstr.substr(16 * (i - 1), 16);
		//printf("[%d]en_p: %s\n",i, cutstr.c_str());

		Erystr = Erystr + OnBAesEn(((char*)cutstr.c_str()));

	}
	//printf("剩余[%d][%d]\n", 16 * (blocknum ), StrLen - 16 * (blocknum));
	cutstr = leftstr.substr(16 * (blocknum), StrLen - 16 * (blocknum));
	//printf("en_p: %s\n", cutstr.c_str());
	Erystr = Erystr + OnBAesEn((char*)(cutstr.c_str()));
	//string转大写
	//transform(Erystr.begin(), Erystr.end(), Erystr.begin(), ::toupper);
	return Erystr;
}
bool CheckSN3()
{
	//gUserID.c_str(), gSN.c_str())
	//CString account;
	//CString content;
	//account.Format(_T("%s"), accountchar);
	//content.Format(_T("%s"), contentchar);

	//	string RSEID =;

	//RSA加密
	// CString RK=RSEID;    //授权序列号
	// vl(RK.GetLength(),RK);
	// int RSTATE=0;//,RSTATE2=0;




	// AfxMessageBox(m_OUT);
	//2048位最多存 512个16进制字符  2048/4=512
	// theApp.SN=m_OUT;
	//RSA
	//RSA加密



	// CString leftstr=_T("ABCDEF3333333345453543643tytyytg68787egUIASDGLSDKSDLKKDKKooweodoubleKASDFthakyoucitySHANHGAI7acdf323421CCAE");
	//   CString username=GetProfileString(VMProtectDecryptStringW(_T("Settings")),VMProtectDecryptStringW(_T("username")));
	//	  int usernameStrLen=username.GetLength();
	//  if(usernameStrLen>3){username=username.Left(3);}

	//AfxMessageBox(GetCPUInfo()+L"/c");
	//AfxMessageBox(GetDisplay()+L"/m");
	//AfxMessageBox(HardDiskId()+L"/m");
	//CString leftstr=GetCPUInfo()+GetMacAddress();//+username;
	//CString account = _T("68122653") ;// GetCPUInfo() + GetDisplay() + HardDiskId();//+username;






	//AfxMessageBox(MoreStrOnBAesEn(leftstr));

	//AfxMessageBox(MoreStrOnBAesDe(MoreStrOnBAesEn(leftstr)));

	//wchar_t * dataA=VMProtectDecryptStringW(_T("20120711"));   //有效期起始日期(应该为发布软件的日期)
	//AfxMessageBox(L"AAA");
	// AfxMessageBox(RK2);
	// AfxMessageBox(MoreStrOnBAesEn(leftstr));

	//	 AfxMessageBox(L"BBB");

	//CString temp;
	//temp.Format(_T("%s"), RSEID.c_str());


	// MessageBox(NULL, RSEID.GetBuffer(RSEID.GetLength()), TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);
	//AfxMessageBox(RSEID);
	string str = MoreStrOnBAesEn(gUserID);
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	//MessageBox(NULL, str.c_str(), TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);

	while (str == gSN)
		//while(RSEID==MoreStrOnBAesEn(leftstr))
	{
		//RSTATE=1;
		//AfxMessageBox(_T("获得授权b1"));
		//MessageBox(NULL, "获得授权b1", TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);
		return 1;
	}
	//while(RK2!=GetCPUInfo() && RSTATE2!=1)
	//{
	//   RSTATE2=1;
	//	AfxMessageBox(_T("试用b1"));
	//	return 0;
	//}
	////////////////////////////////////////检查SN
	//   }     
	//MessageBox(NULL, "无授权b1", TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);
	//  srand((unsigned)time(NULL));
	return 0;
	//授权状态判断  不包含BIOS
	//RSA加密
}
//超过16字符的字符串加密


//超过16字符的字符串解密

string MoreStrOnBAesDe(string leftstr)
{
	////解密
	//transform(strA.begin(), strA.end(), strA.begin(), ::toupper);
	leftstr = leftstr.c_str();//.MakeLower();

							  //printf("%s\n", leftstr.c_str());
	int StrLen = leftstr.size();
	string cutstr, Erystr;

	//printf("A1\n" );
	//Sleep(7000);

	int blocknum = StrLen / 32;     //必须是英文字符，如果是中文字符，截取的是16个中文字符，但每次只加密8个字符，丢掉后8个
	int leftnum = StrLen % 32;
	//printf("A2\n");
	//Sleep(7000);
	for (int i = 1; i <= blocknum; i++)
	{
		//printf("A3\n");
		//Sleep(7000);
		cutstr = leftstr.substr(32 * (i - 1), 32);
		//printf("de_p: %s\n", cutstr.c_str());
		Erystr = Erystr + OnBAesDe((char*)(cutstr.c_str()));

		//printf("A4\n");
		//Sleep(7000);
	}
	//printf("A5\n");
	//Sleep(7000);
	//printf("DE剩余[%d][%d]\n", 16 * (blocknum), StrLen - 16 * (blocknum));
	//cutstr = leftstr.substr(32 * (blocknum), StrLen - 32 * (blocknum));
	//printf("de_p: %s\n",   cutstr.c_str());
	//printf("A6\n");
	//Sleep(7000);

	//	printf("尾巴 ： %s\n", OnBAesDe((char*)(cutstr.c_str())).c_str());

	//Erystr=Erystr+OnBAesDe((char*)(cutstr.c_str()));
	// printf("结束 : %s\n", Erystr.c_str());

	return Erystr;
	///解密
}


//随机检查SN
bool CheckSN()
{
	//gUserID.c_str(), gSN.c_str())
	//CString account;
	//CString content;
	//account.Format(_T("%s"), accountchar);
	//content.Format(_T("%s"), contentchar);
 
//	string RSEID =;

	//RSA加密
	// CString RK=RSEID;    //授权序列号
	// vl(RK.GetLength(),RK);
	// int RSTATE=0;//,RSTATE2=0;




	// AfxMessageBox(m_OUT);
	//2048位最多存 512个16进制字符  2048/4=512
	// theApp.SN=m_OUT;
	//RSA
	//RSA加密

 

	// CString leftstr=_T("ABCDEF3333333345453543643tytyytg68787egUIASDGLSDKSDLKKDKKooweodoubleKASDFthakyoucitySHANHGAI7acdf323421CCAE");
	//   CString username=GetProfileString(VMProtectDecryptStringW(_T("Settings")),VMProtectDecryptStringW(_T("username")));
	//	  int usernameStrLen=username.GetLength();
	//  if(usernameStrLen>3){username=username.Left(3);}

	//AfxMessageBox(GetCPUInfo()+L"/c");
	//AfxMessageBox(GetDisplay()+L"/m");
	//AfxMessageBox(HardDiskId()+L"/m");
	//CString leftstr=GetCPUInfo()+GetMacAddress();//+username;
	//CString account = _T("68122653") ;// GetCPUInfo() + GetDisplay() + HardDiskId();//+username;






																 //AfxMessageBox(MoreStrOnBAesEn(leftstr));

																 //AfxMessageBox(MoreStrOnBAesDe(MoreStrOnBAesEn(leftstr)));

																 //wchar_t * dataA=VMProtectDecryptStringW(_T("20120711"));   //有效期起始日期(应该为发布软件的日期)
																 //AfxMessageBox(L"AAA");
																 // AfxMessageBox(RK2);
																 // AfxMessageBox(MoreStrOnBAesEn(leftstr));

																 //	 AfxMessageBox(L"BBB");

	//CString temp;
	//temp.Format(_T("%s"), RSEID.c_str());
	 

	// MessageBox(NULL, RSEID.GetBuffer(RSEID.GetLength()), TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);
	//AfxMessageBox(RSEID);
	string str = MoreStrOnBAesEn(gUserID);
	transform(str.begin(),str.end(),str.begin(),::toupper);
	//MessageBox(NULL, str.c_str(), TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);

	while (str == gSN)
		//while(RSEID==MoreStrOnBAesEn(leftstr))
	{
		//RSTATE=1;
		 //AfxMessageBox(_T("获得授权b1"));
		// MessageBox(NULL, "获得授权b1", TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);
		return 1;
	}
	//while(RK2!=GetCPUInfo() && RSTATE2!=1)
	//{
	//   RSTATE2=1;
	//	AfxMessageBox(_T("试用b1"));
	//	return 0;
	//}
	////////////////////////////////////////检查SN
	//   }     
	// MessageBox(NULL, "无授权b1", TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);
	//  srand((unsigned)time(NULL));
	return 0;
	//授权状态判断  不包含BIOS
	//RSA加密
}
//随机检查SN

//随机检查SN
bool CheckSN2()
{
	//gUserID.c_str(), gSN.c_str())
	//CString account;
	//CString content;
	//account.Format(_T("%s"), accountchar);
	//content.Format(_T("%s"), contentchar);

	//	string RSEID =;

	//RSA加密
	// CString RK=RSEID;    //授权序列号
	// vl(RK.GetLength(),RK);
	// int RSTATE=0;//,RSTATE2=0;




	// AfxMessageBox(m_OUT);
	//2048位最多存 512个16进制字符  2048/4=512
	// theApp.SN=m_OUT;
	//RSA
	//RSA加密



	// CString leftstr=_T("ABCDEF3333333345453543643tytyytg68787egUIASDGLSDKSDLKKDKKooweodoubleKASDFthakyoucitySHANHGAI7acdf323421CCAE");
	//   CString username=GetProfileString(VMProtectDecryptStringW(_T("Settings")),VMProtectDecryptStringW(_T("username")));
	//	  int usernameStrLen=username.GetLength();
	//  if(usernameStrLen>3){username=username.Left(3);}

	//AfxMessageBox(GetCPUInfo()+L"/c");
	//AfxMessageBox(GetDisplay()+L"/m");
	//AfxMessageBox(HardDiskId()+L"/m");
	//CString leftstr=GetCPUInfo()+GetMacAddress();//+username;
	//CString account = _T("68122653") ;// GetCPUInfo() + GetDisplay() + HardDiskId();//+username;






	//AfxMessageBox(MoreStrOnBAesEn(leftstr));

	//AfxMessageBox(MoreStrOnBAesDe(MoreStrOnBAesEn(leftstr)));

	//wchar_t * dataA=VMProtectDecryptStringW(_T("20120711"));   //有效期起始日期(应该为发布软件的日期)
	//AfxMessageBox(L"AAA");
	// AfxMessageBox(RK2);
	// AfxMessageBox(MoreStrOnBAesEn(leftstr));

	//	 AfxMessageBox(L"BBB");

	//CString temp;
	//temp.Format(_T("%s"), RSEID.c_str());


	// MessageBox(NULL, RSEID.GetBuffer(RSEID.GetLength()), TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);
	//AfxMessageBox(RSEID);
	string str = MoreStrOnBAesEn(gUserID);
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	//MessageBox(NULL, str.c_str(), TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);

	while (str == gSN)
		//while(RSEID==MoreStrOnBAesEn(leftstr))
	{
		//RSTATE=1;
		//AfxMessageBox(_T("获得授权b1"));
		//MessageBox(NULL, "获得授权b1", TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);
		return 1;
	}
	//while(RK2!=GetCPUInfo() && RSTATE2!=1)
	//{
	//   RSTATE2=1;
	//	AfxMessageBox(_T("试用b1"));
	//	return 0;
	//}
	////////////////////////////////////////检查SN
	//   }     
	//MessageBox(NULL, "无授权b1", TEXT("你好"), MB_ICONINFORMATION | MB_YESNO);
	//  srand((unsigned)time(NULL));
	return 0;
	//授权状态判断  不包含BIOS
	//RSA加密
}
//随机检查SN

void QuickLib_TD_Start()
{	//临界区
	for (int i = 0; i < MAX_EVENTNUM; i++)
	{
		if (!hEvent[i])
		{
			char temp[10] = { 0 };
			_snprintf_s(temp, sizeof(temp), sizeof(temp), "hEvent%d", i);
			hEvent[i] = CreateEvent(NULL, FALSE, FALSE, temp);//TRUE手动置位
															  //hEvent = CreateEvent(NULL, FALSE, FALSE, "abc");//TRUE自动置位，无需ResetEvent
		}

	}

	InitializeCriticalSection(&g_csdata);


	//while(!CheckSN())
	//{
	
		//return;
	//}
	    /*
		//RSA
		//m_OUT =VMProtectDecryptStringW(GetProfileString(_T("Settings"),_T("SN")));
		string SN = "16EF034A7F9785C03EDF4295020B81C3C5FC8E8776E52018F5007634BFEEBAAEA51562DFA2C44F65FBB2F69AB1550D9D98478034C8BDC689840F6ACCEEF4AB060B330FC90A5B9032CE37AEEB1EB5C58CF0575096A4CA23A4A94DE96251791854C0B8AB11DD12D4CCBD93F50678EAB073DC4D49A23D4BF7CFE291732CD2FFF6AF5D53481D8853373647BFC5FD81F58BB6E067D467E343604A4D744651D688B86B50F4F1C223CD7C1E8CD0703BF2E456E28FB16D791AD22D6DFE98A066CA45B68893750193CF1B7C7C094DEE0D67DDFA06F22299C5809DFAB5DDA65FB70265780458CB29F004E3BE9D0BDD66ECDEC256377A99E3DDBAE5C985B6309F4F3CF8E7CE1";//  (GetProfileString(_T("Settings"), _T("SN")));
		string m_OUT = SN;
		//2048位最多存 512个16进制字符  2048/4=512
		//RSA

		// WriteProfileString(_T("Settings"),_T("SNp2"),m_OUT);   //SN保存到注册表
		//RSA加密
		RSAE rsa("123");
		rsa.OnButtonPut();
		//AfxMessageBox(OnClickDecrypt());
		//RSEID =
		//	rsa.OnClickDecrypt(); //授权序列号
		printf("RSA De: %s\n", rsa.OnClickDecrypt().c_str());

		printf("RSA En: %s\n", rsa.OnClickDecrypt().c_str());
		//RSA加密
		//CString RK=RSEID;    //授权序列号
		//vl(RSEID.GetLength(), RSEID);   //授权序列号，检查首位缺位补0
		*/



	std::cout << __FUNCTION__ << std::endl;
	ghTradedVolMutex = ::CreateMutex(NULL, FALSE, NULL);
	std::cout << "Init Finished." << std::endl;
}




void QuickLib_TD_End()
{
	std::cout << __FUNCTION__ << std::endl;
	//临界区
	DeleteCriticalSection(&g_csdata);

	if (ghTradedVolMutex)
	{
		::CloseHandle(ghTradedVolMutex);
		ghTradedVolMutex = NULL;
	}
}

int Login()
{
	std::cout << __FUNCTION__ << std::endl;
	std::ifstream ifs(gConfigFile.c_str());
	if (ifs.is_open())
	{
		std::string fl;
		getline(ifs, fl);
		getline(ifs, gTDFrontAddr[0]);
		getline(ifs, gTDFrontAddr[1]);
		getline(ifs, gTDFrontAddr[2]);

		getline(ifs, fl);
		getline(ifs, gBrokerID);

		getline(ifs, fl);
		getline(ifs, gUserID);

		getline(ifs, fl);
		getline(ifs, gPassword);

		getline(ifs, fl);
		getline(ifs, gSN);

		ifs.close();
	}else
	{
		std::cout << "fail to open config file." << std::endl;
		return 1;
	}
	
	//while (!CheckSN2(gUserID.c_str(),gSN.c_str()))
	//{

	//	return -1;
	//}
	while(!CheckSN())
	{

	return 0;
	}
	while (!CheckSN2())
	{

		return -1;
	}
	std::cout << "Login: " << gUserID << std::endl;

	while (CheckSN3())
	{

		bool ret = gTraderSpi.Init();

		if (ret)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
	return  0;
}

//限制版
//int maxordernum2 = 6 + 8;
//int num2 = 0;
//限制版

//乘数
extern std::map<std::string, double> gUnderlyingMultiple;
//保证金率
extern std::map<std::string, double> gMarginRate_long;
extern std::map<std::string, double> gMarginRate_short;
//手续费率
extern std::map<std::string, double> gCommissionRate;

//查询最大报单数量
extern std::map<std::string, int> gMaxOrderVolume;




extern int	Trade_dataA_Amount_B_Today[TYPE_NUM];		//多单持仓
extern int	Trade_dataA_Amount_B_History[TYPE_NUM];		//多单持仓
extern int	Trade_dataA_Amount_S_Today[TYPE_NUM];		//空单持仓
extern int	Trade_dataA_Amount_S_History[TYPE_NUM];		//空单持仓

extern double YestayAllAmount;
extern double TodayAllAmount;
extern double UserAmount;




extern std::map<std::string, int> gPosition_S;
extern std::map<std::string, int> gPosition_B;

extern std::map<std::string, int> gPosition_S_Today;
extern std::map<std::string, int> gPosition_B_Today;
extern std::map<std::string, int> gPosition_S_History;
extern std::map<std::string, int> gPosition_B_History;

extern std::map<std::string, int> gTypeCheckState_S_Today;
extern std::map<std::string, int> gTypeCheckState_B_Today;
extern std::map<std::string, int> gTypeCheckState_S_History;
extern std::map<std::string, int> gTypeCheckState_B_History;

#define POSITION_SELL_TODAY     9001
#define POSITION_BUY_TODAY      9002
#define POSITION_SELL_HISTORY   9003
#define POSITION_BUY_HISTORY    9004
#define POSITION_SELL_ALL   9005
#define POSITION_BUY_ALL    9006


#define RATETYPE_LONG     0
#define RATETYPE_SHORT    1

extern QLCTPTraderSpi *mpUserSpi;


int InsertOrderByRate(char *Instrument, char direction, char offsetFlag, char priceType, double price, double rate, bool BalanceType,int multiplier)
{
	//std::cout << __FUNCTION__ << Instrument << "\t" << direction << "\t"
	//<< offsetFlag << "\t" << priceType << "\t" << price << "\t"
	//<< num << std::endl;

	//限制版

	//num2++;
	//while (num2 > maxordernum2)
	//{
	//	return 0;
	//	break;
	//}

	//限制版


	int num = 0;// rate*

	if (BalanceType==0)
	{
		if (TodayAllAmount < 1e-10)
		{
			return -2;//未获得资金容量数据
		}
		num =(int)( rate* TodayAllAmount*multiplier); //动态权益
	}
	else
	{
		if (YestayAllAmount < 1e-10)
		{
			return -2;//未获得资金容量数据
		}
		num = (int)(rate* YestayAllAmount*multiplier); //静态权益

	}


	printf("按开仓比例[%0.02f%%]下单手数[%d]\n", rate,num);

	if (gTraderSpi.IsInitOK())
	{
		return gTraderSpi.InsertOrder(Instrument, direction, offsetFlag, priceType, price, num);
	}
	else
	{
		return -1;
	}
}


int InsertOrder(char *Instrument, char direction, char offsetFlag, char priceType, double price, int num)
{
	std::cout << __FUNCTION__ << Instrument << "\t" << direction << "\t"
		<< offsetFlag << "\t" << priceType << "\t" << price << "\t"
		<< num << std::endl;

	//限制版

	//num2++;
	//while (num2 > maxordernum2)
	//{
	//	return 0;
	//	break;
	//}

	//限制版

	printf("下单手数[%d]\n", num);

	if (gTraderSpi.IsInitOK())
	{
		return gTraderSpi.InsertOrder(Instrument, direction, offsetFlag, priceType, price, num);
	}
	else
	{
		return -1;
	}
}
 
int DeleteOrder(char *Instrument, int OrderRef)
{
	std::cout << __FUNCTION__ << "\t" << OrderRef << std::endl;

	if (gTraderSpi.IsInitOK())
	{
		return gTraderSpi.DeleteOrder(Instrument, OrderRef);
	}
	else
	{
		return -1;
	}
}

int QryTradedVol(int OrderRef)
{
	int ret = -1;
	::WaitForSingleObject(ghTradedVolMutex, INFINITE);
	if (gOrderRef2TradedVol.find(OrderRef) != gOrderRef2TradedVol.end())
	{
		ret = gOrderRef2TradedVol[OrderRef];
	}
	::ReleaseMutex(ghTradedVolMutex);
	return ret;
}

//查询乘数
double QryUnderlyingMultiple(char *Instrument)
{
	if (!mpUserSpi)
	{
		return -1; //未初始化完成
	}
	//OnRspQryInstrument
	mpUserSpi->ReqQryInstrument(Instrument);//仓位管理		

	int num = 0;
	while (num<30)
	{
 

			if (gUnderlyingMultiple.find(Instrument) != gUnderlyingMultiple.end())
			{
				//printf("乘数:%0.02f\n\n", gUnderlyingMultiple[Instrument]);
				return gUnderlyingMultiple[Instrument];
				//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

				//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
			}
			else
			{
				//printf("没找到该合约%s\n", contract);
				return -2;
			}

 

		num++;
		Sleep(200);
	}


	return -3;//查询超时

}


//查询保证金率
double QryExchangeMarginRate(char *Instrument,int type)
{
	if (!mpUserSpi)
	{
		return -1; //未初始化完成
	}
	mpUserSpi->ReqQryInstrumentMarginRate(Instrument);//仓位管理		

	//mpUserSpi->ReqQryInvestorProductGroupMargin(Instrument);//仓位管理	
	
	int num = 0;
	while (num<30)
	{
		if (type == RATETYPE_LONG)
		{

			if (gMarginRate_long.find(Instrument) != gMarginRate_long.end())
			{

                return gMarginRate_long[Instrument];
				//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

				//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
			}
			else
			{
				//printf("没找到该合约%s\n", contract);
				return -2;
			}

			
		}

		else
		{
			if (gMarginRate_short.find(Instrument) != gMarginRate_short.end())
			{


			    return gMarginRate_short[Instrument];

				//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

				//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
			}
			else
			{
				//printf("没找到该合约%s\n", contract);
				return -2;
			}



		}


		num++;
		Sleep(200);
	}


	return -3;//查询超时
	/*


	//gPosition_S_Today::iterator it = gPosition_S_Today.find(contract);
	switch (positiontype)
	{
	 case POSITION_SELL_TODAY:
	 {
		// printf("POSITION_SELL_TODAY[%s][%d]\n", contract, gPosition_S_Today[contract]);
		if (gPosition_S_Today.find(contract) != gPosition_S_Today.end())
		{
			//printf("%s 查询POSITION_SELL_TODAY仓位%d\n", contract, gPosition_S_Today[contract]);


			return gPosition_S_Today[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("没找到该合约%s\n", contract);
			return 0;
		}

	
	
	 }
	 break;
	 case POSITION_BUY_TODAY:
	 {
		// printf("POSITION_BUY_TODAY[%s][%d]\n", contract, gPosition_B_Today[contract]);

		 if (gPosition_B_Today.find(contract) != gPosition_B_Today.end())
		 {
			// printf("%s 查询POSITION_BUY_TODAY仓位%d\n", contract, gPosition_B_Today[contract]);
			 return gPosition_B_Today[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 else
		 {
			 //printf("没找到该合约%s\n", contract);
			 return 0;
		 }

	 }
	 break;
	 case POSITION_SELL_HISTORY:
	 {
		 //printf("POSITION_SELL_HISTORY\n");
		 if (gPosition_S_History.find(contract) != gPosition_S_History.end())
		 {
			// printf("%s 查询POSITION_SELL_HISTORY仓位%d\n", contract, gPosition_S_History[contract]);
			 return gPosition_S_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 else
		 {
			//printf("没找到该合约%s\n", contract);
			 return 0;
		 }

	 }
	 break;
	 case POSITION_BUY_HISTORY:
	 {
		// printf("POSITION_BUY_HISTORY\n");
		 if (gPosition_B_History.find(contract) != gPosition_B_History.end())
		 {
			// printf("%s 查询POSITION_BUY_HISTORY仓位%d\n", contract, gPosition_B_History[contract]);
			 return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 else
		 {
			//printf("没找到该合约%s\n", contract);
			 return 0;
		 }

	 }
	 break;

	 case POSITION_SELL_ALL:
	 {  //  printf("POSITION_SELL_ALL\n");
		 int allnum = 0;

		 if (gPosition_S_History.find(contract) != gPosition_S_History.end())
		 {
			// printf("%s A查询POSITION_SELL_ALL仓位%d\n", contract, gPosition_S_History[contract]);
			 
			 allnum = gPosition_S_History[contract];
			 //return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		// else
		// {
			// printf("没找到该合约的策略%s\n", contract);
			 //allnum= 0;
		// }


		 if (gPosition_S_Today.find(contract) != gPosition_S_Today.end())
		 {
			// printf("%s B查询POSITION_SELL_ALL仓位%d\n", contract, gPosition_S_Today[contract]);

			 allnum = allnum + gPosition_S_Today[contract];
			 //return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		// else
		// {
			// printf("没找到该合约的策略%s\n", contract);
			// allnum = 0;
		// }

		 return allnum;
	 }
	 break;
	 case POSITION_BUY_ALL:
	 {   //printf("POSITION_BUY_ALL\n");
		 int allnum = 0;

		 if (gPosition_B_History.find(contract) != gPosition_B_History.end())
		 {
			// printf("%s A查询POSITION_BUY_ALL仓位%d\n", contract, gPosition_B_History[contract]);

			 allnum = gPosition_B_History[contract];
			 //return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 //else
		// {
			// printf("没找到该合约的策略%s\n", contract);
			 //allnum= 0;
		// }


		 if (gPosition_B_Today.find(contract) != gPosition_B_Today.end())
		 {
			// printf("%s B查询POSITION_BUY_ALL仓位%d\n", contract, gPosition_B_Today[contract]);

			 allnum = allnum + gPosition_B_Today[contract];
			 //return gPosition_B_History[contract];
			 //memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			 //	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		 }
		 //else
		// {
			// printf("没找到该合约的策略%s\n", contract);
			// // allnum = 0;
		// }
		 return allnum;

	 }
	 break;

	 default:
		printf("err get\n");
		return 0;
	 break;
	}
	*/


	/*
	//map
	//string instrumentstr = pDepthMarketData->InstrumentID;
	QS_List::iterator it = mapTest.find(contract);
	if (it == mapTest.end())
	{
		//返回错误包
		//m_pConnect->SetErrorMg("未配置此券商!");
		//AddErrorPackage(head);
		//if (allprintfstate) {
		printf("没找到该合约的策略%s\n", contract);
		//}
		//return -1;
	}
	else
	{
		//WriteLog(0, 100, "qisd_jy:%d, qsid_zx:%d ", qsid, it->second);
		for (int k = 0; k < it->second.strategyfilenum; k++)
		{
			//if (it->second.strategyfile[k] != "")
			//{
			//if (true)
			//{
			printf("[%s] 仓位[%d]\n", contract, (it->second.strategyfile[k]).c_str(), it->second.position[k]);
			//strategy((it->second.strategyfile[k]).c_str(), pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);

		}
	}
	*/


	//return 1;
}


int  QUICKLIB_TD_API ReqQueryMaxOrderVolume(char * BrokerID,char * InvestorID,char * InstrumentID, char Direction, char  OffsetFlag,char  HedgeFlag, int MaxVolume)
{
	CThostFtdcQueryMaxOrderVolumeField req;
	memset(&req,0,sizeof(CThostFtdcQueryMaxOrderVolumeField));
	strncpy_s(req.BrokerID, sizeof(req.BrokerID), BrokerID, sizeof(req.BrokerID));
	strncpy_s(req.InvestorID, sizeof(req.InvestorID), InvestorID, sizeof(req.InvestorID));
	strncpy_s(req.InstrumentID, sizeof(req.InstrumentID), InstrumentID, sizeof(req.InstrumentID));
	req.Direction  = Direction ;
	req.OffsetFlag = OffsetFlag;
	req.HedgeFlag = HedgeFlag;
	req.MaxVolume = MaxVolume;
	return mpUserSpi->ReqQueryMaxOrderVolume(&req,1);//仓位管理		
}


int  QUICKLIB_TD_API ReqQryContractBank()
{
	CThostFtdcQryContractBankField req;
	memset(&req,0,sizeof(CThostFtdcQryContractBankField));
	strcpy(req.BrokerID, gBrokerID.c_str());
	//strncpy_s(tn.BrokerID, sizeof(tn.BrokerID), BrokerID, sizeof(tn.BrokerID));
	return mpUserSpi->ReqQryContractBank(&req, 1);//仓位管理		
}


int  QUICKLIB_TD_API  ReqFromBankToFutureByFuture(
	char * BankID,
	 //char * BankBranchID,
	//char * BrokerID,
	char *  BrokerBranchID,
	char *BankAccount,
	char * BankPassWord,
	char * AccountID,
	//char *Password,
	//char * CurrencyID,
	 double  TradeAmount,
	int nRequestID)
{
	 
	/*
	///业务功能码
	TThostFtdcTradeCodeType	TradeCode;
	///银行代码
	TThostFtdcBankIDType	BankID;
	///银行分支机构代码
	TThostFtdcBankBrchIDType	BankBranchID;
	///期商代码
	TThostFtdcBrokerIDType	BrokerID;
	///期商分支机构代码
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///交易日期
	TThostFtdcTradeDateType	TradeDate;
	///交易时间
	TThostFtdcTradeTimeType	TradeTime;
	///银行流水号
	TThostFtdcBankSerialType	BankSerial;
	///交易系统日期 
	TThostFtdcTradeDateType	TradingDay;
	///银期平台消息流水号
	TThostFtdcSerialType	PlateSerial;
	///最后分片标志
	TThostFtdcLastFragmentType	LastFragment;
	///会话号
	TThostFtdcSessionIDType	SessionID;
	///客户姓名
	TThostFtdcIndividualNameType	CustomerName;
	///证件类型
	TThostFtdcIdCardTypeType	IdCardType;
	///证件号码
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	TThostFtdcCustTypeType	CustType;
	///银行帐号
	TThostFtdcBankAccountType	BankAccount;
	///银行密码
	TThostFtdcPasswordType	BankPassWord;
	///投资者帐号
	TThostFtdcAccountIDType	AccountID;
	///期货密码
	TThostFtdcPasswordType	Password;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///期货公司流水号
	TThostFtdcFutureSerialType	FutureSerial;
	///用户标识
	TThostFtdcUserIDType	UserID;
	///验证客户证件号码标志
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///转帐金额
	TThostFtdcTradeAmountType	TradeAmount;
	///期货可取金额
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///费用支付标志
	TThostFtdcFeePayFlagType	FeePayFlag;
	///应收客户费用
	TThostFtdcCustFeeType	CustFee;
	///应收期货公司费用
	TThostFtdcFutureFeeType	BrokerFee;
	///发送方给接收方的消息
	TThostFtdcAddInfoType	Message;
	///摘要
	TThostFtdcDigestType	Digest;
	///银行帐号类型
	TThostFtdcBankAccTypeType	BankAccType;
	///渠道标志
	TThostFtdcDeviceIDType	DeviceID;
	///期货单位帐号类型
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	TThostFtdcBankAccountType	BankSecuAcc;
	///银行密码标志
	TThostFtdcPwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///交易柜员
	TThostFtdcOperNoType	OperNo;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///交易ID
	TThostFtdcTIDType	TID;
	///转账交易状态
	TThostFtdcTransferStatusType	TransferStatus;
	///长客户姓名
	TThostFtdcLongIndividualNameType	LongCustomerName;
	*/
 
	CThostFtdcReqTransferField req;
	memset(&req,0,sizeof(CThostFtdcReqTransferField));

	//req.TradeCode;  
	//req.BankID; //必填  
	strcpy(req.BrokerID, gBrokerID.c_str());

	//req.BankBranchID; //必填  
	if (req.BankBranchID[0] == 0)
	{
		strcpy(req.BankBranchID, "0000");
	}
	//req.BrokerID; //必填  
	//req.BrokerBranchID; //必填  
	//if (req.BrokerBranchID[0] == 0)
	//{
	//	strcpy(req.BrokerBranchID, "0000");
	//}
	//req.TradeDate;  
	//req.TradeTime;  
	//req.BankSerial;  
	//req.TradingDay;  
	//req.PlateSerial;  
	//req.LastFragment;  
	//req.SessionID;  
	//req.CustomerName;  
	//req.IdCardType;  
	//req.IdentifiedCardNo;  
	//req.CustType;  
	//req.BankAccount; //必填  
	//req.BankPassWord; //必填  
	strcpy(req.BankAccount, BankAccount);
	strcpy(req.BankPassWord, BankPassWord);
					  //req.AccountID;  
	//req.AccountID; //必填  
	//req.Password; //必填  
				  //req.InstallID;  
				  //req.FutureSerial;  
	//strcpy(req.UserID, m_UserID);
	strcpy(req.AccountID, gUserID.c_str());
	strcpy(req.UserID, gUserID.c_str());
	strcpy(req.Password, gPassword.c_str());


	//req.VerifyCertNoFlag;  
	//req.CurrencyID="CNY"; //人民币必填  
	strncpy_s(req.CurrencyID, sizeof(req.CurrencyID), "CNY", sizeof("CNY"));

	req.TradeAmount= TradeAmount;
	                 //必填  
					 //req.FutureFetchAmount;  
					 //req.FeePayFlag;  
					 //req.CustFee;  
					 //req.BrokerFee;  
					 //req.Message;  
					 //req.Digest;  
					 //req.BankAccType;  
					 //req.DeviceID;  
					 //req.BankSecuAccType;  
					 //req.BrokerIDByBank;  
					 //req.BankSecuAcc;  
					 //req.BankPwdFlag;  
	req.SecuPwdFlag =  THOST_FTDC_BPWDF_BlankCheck;
	//req.OperNo;  
	//req.RequestID = reqInfo.nRequestID;
	req.RequestID =  nRequestID;
	//req.TID;  
	//req.TransferStatus;  
 
	//return mpUserSpi->ReqFromBankToFutureByFuture(&tn,1);//仓位管理		
	return mpUserSpi->ReqFromBankToFutureByFuture(&req,nRequestID); //银行转期货  
 
}
int  QUICKLIB_TD_API  ReqFromFutureToBankByFuture(
	char * BankID,
	//char * BankBranchID,
	//char * BrokerID,
	char *  BrokerBranchID,
	char *BankAccount,
	char * BankPassWord,
	char * AccountID,
	//char *Password,
	//char * CurrencyID,
	double  TradeAmount,
	int nRequestID)
{
 
	CThostFtdcReqTransferField req;
	memset(&req, 0, sizeof(CThostFtdcReqTransferField));

	//req.TradeCode;  
	//req.BankID; //必填  
	strcpy(req.BrokerID, gBrokerID.c_str());

	//req.BankBranchID; //必填  
	if (req.BankBranchID[0] == 0)
	{
		strcpy(req.BankBranchID, "0000");
	}
	//req.BrokerID; //必填  
	//req.BrokerBranchID; //必填  
	//if (req.BrokerBranchID[0] == 0)
	//{
	//	strcpy(req.BrokerBranchID, "0000");
	//}
	//req.TradeDate;  
	//req.TradeTime;  
	//req.BankSerial;  
	//req.TradingDay;  
	//req.PlateSerial;  
	//req.LastFragment;  
	//req.SessionID;  
	//req.CustomerName;  
	//req.IdCardType;  
	//req.IdentifiedCardNo;  
	//req.CustType;  
	//req.BankAccount; //必填  
	//req.BankPassWord; //必填  
	strcpy(req.BankAccount, BankAccount);
	strcpy(req.BankPassWord, BankPassWord);
	//req.AccountID;  
	//req.AccountID; //必填  
	//req.Password; //必填  
	//req.InstallID;  
	//req.FutureSerial;  
	//strcpy(req.UserID, m_UserID);
	strcpy(req.AccountID, gUserID.c_str());
	strcpy(req.UserID, gUserID.c_str());
	strcpy(req.Password, gPassword.c_str());


	//req.VerifyCertNoFlag;  
	//req.CurrencyID="CNY"; //人民币必填  
	strncpy_s(req.CurrencyID, sizeof(req.CurrencyID), "CNY", sizeof("CNY"));

	req.TradeAmount = TradeAmount;
	//必填  
	//req.FutureFetchAmount;  
	//req.FeePayFlag;  
	//req.CustFee;  
	//req.BrokerFee;  
	//req.Message;  
	//req.Digest;  
	//req.BankAccType;  
	//req.DeviceID;  
	//req.BankSecuAccType;  
	//req.BrokerIDByBank;  
	//req.BankSecuAcc;  
	//req.BankPwdFlag;  
	req.SecuPwdFlag = THOST_FTDC_BPWDF_BlankCheck;
	//req.OperNo;  
	//req.RequestID = reqInfo.nRequestID;
	req.RequestID = nRequestID;
	//req.TID;  
	//req.TransferStatus;  


	return  mpUserSpi->ReqFromFutureToBankByFuture(&req,nRequestID); //期货转银行  

}




int QryPosition(char *contract, int positiontype)
{

	//gPosition_S_Today::iterator it = gPosition_S_Today.find(contract);
	switch (positiontype)
	{
	case POSITION_SELL_TODAY:
	{
		// printf("POSITION_SELL_TODAY[%s][%d]\n", contract, gPosition_S_Today[contract]);
		if (gPosition_S_Today.find(contract) != gPosition_S_Today.end())
		{
			//printf("%s 查询POSITION_SELL_TODAY仓位%d\n", contract, gPosition_S_Today[contract]);


			return gPosition_S_Today[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("没找到该合约%s\n", contract);
			return 0;
		}



	}
	break;
	case POSITION_BUY_TODAY:
	{
		// printf("POSITION_BUY_TODAY[%s][%d]\n", contract, gPosition_B_Today[contract]);

		if (gPosition_B_Today.find(contract) != gPosition_B_Today.end())
		{
			// printf("%s 查询POSITION_BUY_TODAY仓位%d\n", contract, gPosition_B_Today[contract]);
			return gPosition_B_Today[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("没找到该合约%s\n", contract);
			return 0;
		}

	}
	break;
	case POSITION_SELL_HISTORY:
	{
		//printf("POSITION_SELL_HISTORY\n");
		if (gPosition_S_History.find(contract) != gPosition_S_History.end())
		{
			// printf("%s 查询POSITION_SELL_HISTORY仓位%d\n", contract, gPosition_S_History[contract]);
			return gPosition_S_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("没找到该合约%s\n", contract);
			return 0;
		}

	}
	break;
	case POSITION_BUY_HISTORY:
	{
		// printf("POSITION_BUY_HISTORY\n");
		if (gPosition_B_History.find(contract) != gPosition_B_History.end())
		{
			// printf("%s 查询POSITION_BUY_HISTORY仓位%d\n", contract, gPosition_B_History[contract]);
			return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		else
		{
			//printf("没找到该合约%s\n", contract);
			return 0;
		}

	}
	break;

	case POSITION_SELL_ALL:
	{  //  printf("POSITION_SELL_ALL\n");
		int allnum = 0;

		if (gPosition_S_History.find(contract) != gPosition_S_History.end())
		{
			// printf("%s A查询POSITION_SELL_ALL仓位%d\n", contract, gPosition_S_History[contract]);

			allnum = gPosition_S_History[contract];
			//return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		// else
		// {
		// printf("没找到该合约的策略%s\n", contract);
		//allnum= 0;
		// }


		if (gPosition_S_Today.find(contract) != gPosition_S_Today.end())
		{
			// printf("%s B查询POSITION_SELL_ALL仓位%d\n", contract, gPosition_S_Today[contract]);

			allnum = allnum + gPosition_S_Today[contract];
			//return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		// else
		// {
		// printf("没找到该合约的策略%s\n", contract);
		// allnum = 0;
		// }

		return allnum;
	}
	break;
	case POSITION_BUY_ALL:
	{   //printf("POSITION_BUY_ALL\n");
		int allnum = 0;

		if (gPosition_B_History.find(contract) != gPosition_B_History.end())
		{
			// printf("%s A查询POSITION_BUY_ALL仓位%d\n", contract, gPosition_B_History[contract]);

			allnum = gPosition_B_History[contract];
			//return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		//else
		// {
		// printf("没找到该合约的策略%s\n", contract);
		//allnum= 0;
		// }


		if (gPosition_B_Today.find(contract) != gPosition_B_Today.end())
		{
			// printf("%s B查询POSITION_BUY_ALL仓位%d\n", contract, gPosition_B_Today[contract]);

			allnum = allnum + gPosition_B_Today[contract];
			//return gPosition_B_History[contract];
			//memcpy(data[gMarket[pDepthMarketData->InstrumentID]],  pDepthMarketData, size);

			//	memcpy(depthdata[gMarket[pDepthMarketData->InstrumentID]], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		}
		//else
		// {
		// printf("没找到该合约的策略%s\n", contract);
		// // allnum = 0;
		// }
		return allnum;

	}
	break;
	default:
		printf("err get\n");
		return 0;
		break;
	}



	/*
	//map
	//string instrumentstr = pDepthMarketData->InstrumentID;
	QS_List::iterator it = mapTest.find(contract);
	if (it == mapTest.end())
	{
	//返回错误包
	//m_pConnect->SetErrorMg("未配置此券商!");
	//AddErrorPackage(head);
	//if (allprintfstate) {
	printf("没找到该合约的策略%s\n", contract);
	//}
	//return -1;
	}
	else
	{
	//WriteLog(0, 100, "qisd_jy:%d, qsid_zx:%d ", qsid, it->second);
	for (int k = 0; k < it->second.strategyfilenum; k++)
	{
	//if (it->second.strategyfile[k] != "")
	//{
	//if (true)
	//{
	printf("[%s] 仓位[%d]\n", contract, (it->second.strategyfile[k]).c_str(), it->second.position[k]);
	//strategy((it->second.strategyfile[k]).c_str(), pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);

	}
	}
	*/


	//return 1;
}


int  ReqQryInstrument()
{

	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(CThostFtdcQryInstrumentField));

	//strcpy(req.BrokerID, gBrokerID.c_str());

	//strncpy_s(req.CurrencyID, sizeof(req.CurrencyID), "CNY", sizeof("CNY"));

	//req.TradeAmount = TradeAmount;

	//req.SecuPwdFlag = THOST_FTDC_BPWDF_BlankCheck;
	//req.OperNo;  
	//req.RequestID = reqInfo.nRequestID;
	//r//eq.RequestID = nRequestID;


	//return  mpUserSpi->ReqQryInstrument(&req, nRequestID); //期货转银行  
	return  mpUserSpi->ReqQryInstrument(&req, 1); //期货转银行  


}



void *QryPositionList(int i)


{
	/*
	if (gStatus)
	{
		return NULL;
	}
	if (i < 0 || (i >= (int)gMarket.size()))
	{
		return NULL;
	}
	else
	{
		//return data[i];
		return depthdata[i];
	}
	*/
	return NULL;
}


double QryBalance(bool BalanceType)
{
	if (BalanceType)
	{
		return TodayAllAmount; //动态权益
	}
	else
	{
		return YestayAllAmount; //静态权益
	
	}

 
}

double QryAvailable()
{

	return UserAmount;  //可用资金
 
}
void SetShowPosition(bool showstate)
{
	showpositionstate = showstate;
	//return UserAmount;  //可用资金

}
//double QryAvailable2()
//{

	//return UserAmount;  //可用资金

//}
//double ShowPosition()
//{

	//showpositionstate = setstate;
	//return 1.2;
//}

int   OnCmd()
{
	//trategy1();

	//int t = 0;
	//while (t<10)
	//{
	//t++;
	//	Sleep(1000);
	//	printf("%d\n",t);
	// g_event.ResetEvent();
	/*
	if (hEvent)
	{
	ResetEvent(hEvent);
	}
	else
	{
	hEvent = CreateEvent(NULL, TRUE, FALSE, "abc");//TRUE手动置位
	//hEvent = CreateEvent(NULL, FALSE, FALSE, "abc");//TRUE自动置位，无需ResetEvent
	}
	*/
	//HANDLE hearr[3];

	//hearr[0] = hEvent;

	//hearr[1] = hEvent;

	//hearr[2] = hEvent;

	DWORD dw = WaitForMultipleObjects(MAX_EVENTNUM, hEvent, FALSE, INFINITE);


	//printf("DW: %d\n",dw);
	switch (dw)
	{

		//case WAIT_FAILED:

		// Bad call to function (invalid handle?)

		//break;

		//case WAIT_TIMEOUT:

		// None of the objects became signaled within 5000 milliseconds.

		//break;

	case WAIT_OBJECT_0 + EID_OnFrontDisconnected:

		// The process identified by h[0] (hProcess1) terminated.
		return TD_NETCONNECT_BREAK;
		break;

	case WAIT_OBJECT_0 + EID_OnFrontConnected:

		// The process identified by h[1] (hProcess2) terminated.
		return TD_NETCONNECT_SCUESS;
		break;
	case WAIT_OBJECT_0 + EID_OnRspUserLogin_Scuess:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGIN_SCUESS;
		break;
	case WAIT_OBJECT_0 + EID_OnRspUserLogin_Failer:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGIN_DENIED;
		break;

/////////////////////////////////////////////////////////////////////////
	case WAIT_OBJECT_0 + EID_OnRspUserLoginout_Scuess:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGINOUT_SCUESS;
		break;
	case WAIT_OBJECT_0 + EID_OnRspUserLoginout_Failer:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGINOUT_DENIED;
		break;


///////////////////////////////////////////////////////////////////

	//case WAIT_OBJECT_0 + EID_OnRtnDepthMarketData:

		// The process identified by h[2] (hProcess3) terminated.
		//return 0;
		//break;
	case WAIT_OBJECT_0 + EID_IsErrorRspInfo:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_SYSTEM_ERROR;
		break;
	//case WAIT_OBJECT_0 + EID_OnRspSubMarketData:

		// The process identified by h[2] (hProcess3) terminated.
	//	return 
	//	break;
	//case WAIT_OBJECT_0 + EID_OnRspUnSubMarketData:

		// The process identified by h[2] (hProcess3) terminated.

	//	break;
	case WAIT_OBJECT_0 + EID_OnRspUserLogout:

		// The process identified by h[2] (hProcess3) terminated.
		return TD_LOGINOUT_SCUESS;
		break;

	case WAIT_OBJECT_0 + EID_OnRspOrder:
		return TD_ORDER_INFO;
		break;

	case WAIT_OBJECT_0 + EID_OnRspTrade:
		return TD_TRADE_INFO;
		break;


	case WAIT_OBJECT_0 + EID_OnRspQryAccountregister:
		return TD_QUERY_ACCOUNTREGISTER;
		break;


	case WAIT_OBJECT_0 + EID_OnRtnFromBankToFutureByFuture:
		return TD_BYFUTURE_BANKTOFUTURE;
		break;

	case WAIT_OBJECT_0 + EID_OnRtnFromFutureToBankByFuture:
		return TD_BYFUTURE_FUTURETOBANK;
		break;



	case WAIT_OBJECT_0 + EID_OnRspQueryMaxOrderVolume:
		return TD_QUERY_MAXORDERVOLUME;
		break;

		

	case WAIT_OBJECT_0 + EID_OnRtnInstrumentStatus:
		return TD_INSTRUMENT_STATUS;
		break;


	case WAIT_OBJECT_0 + EID_OnRspSettlementInfoConfirm:

		return TD_SETTLEMENTINFOCONFIRM;

		break;
	}
	//ResetEvent(hEvent);
	//SetEvent(hEvent);
	return TD_SYSTEM_NONE;
	//int t = 0;

	//while (t > 10)
	//{
	//}
	//	t++;

	//PulseEvent(hEvent);
	//printf("Wait for a New Tick\n");
	//::WaitForSingleObject(hEvent, INFINITE);
	//printf("A New Tick...\n");
	//SetEvent(hEvent);

	//Sleep(500);
	//}
	//printf("End \n");
	//return true;
	/*
	Py_Initialize();

	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("Test0010");	    //Test001:Python文件名
	pFunc = PyObject_GetAttrString(pModule, "add");	//Add:Python文件中的函数名
	PyObject *pArgs = PyTuple_New(2);               //函数调用的参数传递均是以元组的形式打包的,2表示参数个数
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 5));//0---序号  i表示创建int型变量
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 7));//1---序号
	//返回值
	PyObject *pReturn = NULL;
	pReturn = PyEval_CallObject(pFunc, pArgs);	    //调用函数
	//将返回值转换为int类型
	int result;
	PyArg_Parse(pReturn, "i", &result);    //i表示转换成int型变量
	cout << "5+7 = " << result << endl;

	//Py_Finalize();
	*/
}

//bool   OnTick()
//{
//trategy1();

//int t = 0;
//while (t<10)
//{
//t++;
//	Sleep(1000);
//	printf("%d\n",t);
// g_event.ResetEvent();
/*
if (hEvent)
{
ResetEvent(hEvent);
}
else
{
hEvent = CreateEvent(NULL, TRUE, FALSE, "abc");//TRUE手动置位
//hEvent = CreateEvent(NULL, FALSE, FALSE, "abc");//TRUE自动置位，无需ResetEvent
}
*/

//ResetEvent(hEvent);
//SetEvent(hEvent);

//int t = 0;

//while (t > 10)
//{
//}
//	t++;

//PulseEvent(hEvent);
//printf("Wait for a New Tick\n");
//::WaitForSingleObject(hEvent[EID_OnRtnDepthMarketData], INFINITE);
//printf("A New Tick...\n");
//SetEvent(hEvent);

//Sleep(500);
//}
//printf("End \n");
//return true;
/*
Py_Initialize();

PyObject * pModule = NULL;
PyObject * pFunc = NULL;
pModule = PyImport_ImportModule("Test0010");	    //Test001:Python文件名
pFunc = PyObject_GetAttrString(pModule, "add");	//Add:Python文件中的函数名
PyObject *pArgs = PyTuple_New(2);               //函数调用的参数传递均是以元组的形式打包的,2表示参数个数
PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 5));//0---序号  i表示创建int型变量
PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 7));//1---序号
//返回值
PyObject *pReturn = NULL;
pReturn = PyEval_CallObject(pFunc, pArgs);	    //调用函数
//将返回值转换为int类型
int result;
PyArg_Parse(pReturn, "i", &result);    //i表示转换成int型变量
cout << "5+7 = " << result << endl;

//Py_Finalize();
*/
//}
/*
char listname[31] = { 0 };
char *   GetTickInstrument()
{
if (cmdlist.size() <= 0)
{
return "";
}
//memcpy_s(StockData[stockid], sizeof(CSecurityFtdcL2TradeField), &(*cmdlist.begin()), sizeof(CSecurityFtdcL2TradeField));
//printf("stockid:[%d]\n", stockid)
//memcpy_s(&(StockData[stockid]->data), sizeof(CSecurityFtdcL2TradeField_S), &cmdlist.begin(), sizeof(CSecurityFtdcL2TradeField_S));
//StockData[stockid]->data.ExchangeID
//printf("原始数据 InstrumentID[%s] price[%0.02f]\n", cmdlist.begin()->InstrumentID, cmdlist.begin()->Price);
//char temp[200] = { 0 };
//_snprintf_s(temp,sizeof(temp),sizeof(temp),"%s||%d",)
//printf("获得数据allow[%d] InstrumentID[%s] price[%0.02f]\n", StockData[stockid]->allow, StockData[stockid]->data.InstrumentID, StockData[stockid]->data.Price);
//char * newdata = new char[31];
//memset
//_snprintf_s(&listname, sizeof(listname), sizeof(listname), "%s",cmdlist.begin()->Instrument);


memset(&listname, 0, sizeof(listname));
memcpy_s(&listname, sizeof(listname), cmdlist.begin()->content, sizeof(listname));

//临界区
EnterCriticalSection(&g_csdata);
cmdlist.erase(cmdlist.begin());
//临界区
LeaveCriticalSection(&g_csdata);
return listname;
}
*/
int GetUnGetCmdSize()
{
	return cmdlist.size()+ orderlist.size();
}

int  GetCmd()
{

	//return 
	//memcpy_s(StockData[stockid], sizeof(CSecurityFtdcL2TradeField), &(*cmdlist.begin()), sizeof(CSecurityFtdcL2TradeField));

	//printf("stockid:[%d]\n", stockid);
	

	//memcpy_s(&(StockData[stockid]->data), sizeof(CSecurityFtdcL2TradeField_S), &cmdlist.begin(), sizeof(CSecurityFtdcL2TradeField_S));

	//StockData[stockid]->data.ExchangeID

	//printf("原始数据 InstrumentID[%s] price[%0.02f]\n", cmdlist.begin()->InstrumentID, cmdlist.begin()->Price);


	//char temp[200] = { 0 };
	//_snprintf_s(temp,sizeof(temp),sizeof(temp),"%s||%d",)
	//printf("获得数据allow[%d] InstrumentID[%s] price[%0.02f]\n", StockData[stockid]->allow, StockData[stockid]->data.InstrumentID, StockData[stockid]->data.Price);
	//char * newdata = new char[31];
	//memset
	//_snprintf_s(&listname, sizeof(listname), sizeof(listname), "%s",cmdlist.begin()->Instrument);

	if (cmdlist.size() > 0)
	{
		//printf("aaaaaaaaaaaaaaaaaaa\n");
		//临界区
	   //EnterCriticalSection(&g_csdata);
	   return cmdlist.begin()->cmd;
	   //临界区
	   //EnterCriticalSection(&g_csdata);
	   //cmdlist.erase(cmdlist.begin());
	   //LeaveCriticalSection(&g_csdata);
	   //临界区
	}
	else if (orderlist.size() > 0)
	{
		return TD_ORDER_INFO;
	}	
 	else
	{
		return  TD_SYSTEM_NONE;
	}
}

char listcmd[31] = { 0 };
char *   GetCmdContent2()
{
	if (cmdlist.size() <= 0)
	{
		return "";
	}
	//memcpy_s(StockData[stockid], sizeof(CSecurityFtdcL2TradeField), &(*cmdlist.begin()), sizeof(CSecurityFtdcL2TradeField));

	//printf("stockid:[%d]\n", stockid);


	//memcpy_s(&(StockData[stockid]->data), sizeof(CSecurityFtdcL2TradeField_S), &cmdlist.begin(), sizeof(CSecurityFtdcL2TradeField_S));

	//StockData[stockid]->data.ExchangeID

	//printf("原始数据 InstrumentID[%s] price[%0.02f]\n", cmdlist.begin()->InstrumentID, cmdlist.begin()->Price);


	//char temp[200] = { 0 };
	//_snprintf_s(temp,sizeof(temp),sizeof(temp),"%s||%d",)
	//printf("获得数据allow[%d] InstrumentID[%s] price[%0.02f]\n", StockData[stockid]->allow, StockData[stockid]->data.InstrumentID, StockData[stockid]->data.Price);
	//char * newdata = new char[31];
	//memset
	//_snprintf_s(&listname, sizeof(listname), sizeof(listname), "%s",cmdlist.begin()->Instrument);


	memset(&listcmd, 0, sizeof(listcmd));
	memcpy_s(&listcmd, sizeof(listcmd), cmdlist.begin()->content, sizeof(listcmd));

	//临界区
	//EnterCriticalSection(&g_csdata);
	cmdlist.erase(cmdlist.begin());
	//临界区
	LeaveCriticalSection(&g_csdata);

	return listcmd;

}

void *GetCmdContent()
{
	if (cmdlist.size() <= 0)
	{
		return NULL;
	}
	else
	{
		memset(&listcmd, 0, sizeof(listcmd));
		memcpy_s(&listcmd, sizeof(listcmd), cmdlist.begin()->content, sizeof(listcmd));

		//临界区
		//EnterCriticalSection(&g_csdata);
		cmdlist.erase(cmdlist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);

		return listcmd;
	}
}

//订单回报
CThostFtdcOrderField * orderdata =  new CThostFtdcOrderField;
void *GetCmdContent_Order()
{		
	if(orderlist.size() > 0)
	{
		memset(orderdata, 0, sizeof(CThostFtdcOrderField));
		//临界区
		EnterCriticalSection(&g_csdata);
		/*
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///报单引用
	TThostFtdcOrderRefType	OrderRef;
	///用户代码
	TThostFtdcUserIDType	UserID;
	///报单价格条件
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TThostFtdcDirectionType	Direction;
	///组合开平标志
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TThostFtdcPriceType	LimitPrice;
	///数量
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TThostFtdcDateType	GTDDate;
	///成交量类型
	TThostFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TThostFtdcVolumeType	MinVolume;
	///触发条件
	TThostFtdcContingentConditionType	ContingentCondition;
	///止损价
	TThostFtdcPriceType	StopPrice;
	///强平原因
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TThostFtdcBoolType	IsAutoSuspend;
	///业务单元
	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	TThostFtdcRequestIDType	RequestID;
	///本地报单编号
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///会员代码
	TThostFtdcParticipantIDType	ParticipantID;
	///客户代码
	TThostFtdcClientIDType	ClientID;
	///合约在交易所的代码
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TThostFtdcTraderIDType	TraderID;
	///安装编号
	TThostFtdcInstallIDType	InstallID;
	///报单提交状态
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	TThostFtdcSequenceNoType	NotifySequence;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///报单编号
	TThostFtdcOrderSysIDType	OrderSysID;
	///报单来源
	TThostFtdcOrderSourceType	OrderSource;
	///报单状态
	TThostFtdcOrderStatusType	OrderStatus;
	///报单类型
	TThostFtdcOrderTypeType	OrderType;
	///今成交数量
	TThostFtdcVolumeType	VolumeTraded;
	///剩余数量
	TThostFtdcVolumeType	VolumeTotal;
	///报单日期
	TThostFtdcDateType	InsertDate;
	///委托时间
	TThostFtdcTimeType	InsertTime;
	///激活时间
	TThostFtdcTimeType	ActiveTime;
	///挂起时间
	TThostFtdcTimeType	SuspendTime;
	///最后修改时间
	TThostFtdcTimeType	UpdateTime;
	///撤销时间
	TThostFtdcTimeType	CancelTime;
	///最后修改交易所交易员代码
	TThostFtdcTraderIDType	ActiveTraderID;
	///结算会员编号
	TThostFtdcParticipantIDType	ClearingPartID;
	///序号
	TThostFtdcSequenceNoType	SequenceNo;
	///前置编号
	TThostFtdcFrontIDType	FrontID;
	///会话编号
	TThostFtdcSessionIDType	SessionID;
	///用户端产品信息
	TThostFtdcProductInfoType	UserProductInfo;
	///状态信息
	TThostFtdcErrorMsgType	StatusMsg;
	///用户强评标志
	TThostFtdcBoolType	UserForceClose;
	///操作用户代码
	TThostFtdcUserIDType	ActiveUserID;
	///经纪公司报单编号
	TThostFtdcSequenceNoType	BrokerOrderSeq;
	///相关报单
	TThostFtdcOrderSysIDType	RelativeOrderSysID;
	///郑商所成交数量
	TThostFtdcVolumeType	ZCETotalTradedVolume;
	///互换单标志
	TThostFtdcBoolType	IsSwapOrder;
	///营业部编号
	TThostFtdcBranchIDType	BranchID;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///资金账号
	TThostFtdcAccountIDType	AccountID;
	///币种代码
	TThostFtdcCurrencyIDType	CurrencyID;
	///IP地址
	TThostFtdcIPAddressType	IPAddress;
	///Mac地址
	TThostFtdcMacAddressType	MacAddress;
 */
		//orderdata->cmd = orderlist.begin()->cmd;
		memcpy_s(orderdata-> BrokerID, sizeof(TThostFtdcBrokerIDType), orderlist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(orderdata-> InvestorID, sizeof(TThostFtdcInvestorIDType), orderlist.begin()->InvestorID, sizeof(TThostFtdcInvestorIDType));
		
		
		memcpy_s(orderdata->InstrumentID, sizeof(TThostFtdcInstrumentIDType), orderlist.begin()->InstrumentID, sizeof(TThostFtdcInstrumentIDType));
		memcpy_s(orderdata->OrderRef, sizeof(TThostFtdcOrderRefType), orderlist.begin()->OrderRef, sizeof(TThostFtdcOrderRefType));
		memcpy_s(orderdata->UserID, sizeof(TThostFtdcUserIDType), orderlist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		orderdata->OrderPriceType = orderlist.begin()->OrderPriceType;
		orderdata->Direction = orderlist.begin()->Direction;
		memcpy_s(orderdata->CombOffsetFlag, sizeof(TThostFtdcCombOffsetFlagType), orderlist.begin()->CombOffsetFlag, sizeof(TThostFtdcCombOffsetFlagType));
		memcpy_s(orderdata->CombHedgeFlag, sizeof(TThostFtdcCombHedgeFlagType)  , orderlist.begin()->CombHedgeFlag, sizeof(TThostFtdcCombHedgeFlagType));
		orderdata->LimitPrice = orderlist.begin()->LimitPrice;
		orderdata->VolumeTotalOriginal = orderlist.begin()->VolumeTotalOriginal;
		orderdata->TimeCondition= orderlist.begin()->TimeCondition;
		memcpy_s(orderdata->GTDDate, sizeof(TThostFtdcDateType), orderlist.begin()->GTDDate, sizeof(TThostFtdcDateType));
		orderdata->VolumeCondition= orderlist.begin()->VolumeCondition;
		orderdata->MinVolume = orderlist.begin()->MinVolume;
		orderdata->ContingentCondition = orderlist.begin()->ContingentCondition;
		orderdata->StopPrice = orderlist.begin()->StopPrice;
		orderdata->ForceCloseReason = orderlist.begin()->ForceCloseReason;
		orderdata->IsAutoSuspend = orderlist.begin()->IsAutoSuspend;
		memcpy_s(orderdata->BusinessUnit, sizeof(TThostFtdcBusinessUnitType), orderlist.begin()->BusinessUnit, sizeof(TThostFtdcBusinessUnitType));
		

		orderlist.erase(orderlist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);
		return orderdata;
	}
	else
	{
		return NULL;
	}
}


//成交回报
CThostFtdcTradeField tradedata;
void *GetCmdContent_Trade()
{
	if (tradelist.size() > 0)
	{
		memset(&tradedata, 0, sizeof(CThostFtdcTradeField));
		//临界区
		EnterCriticalSection(&g_csdata);
		memcpy_s(tradedata.BrokerID, sizeof(TThostFtdcBrokerIDType), tradelist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(tradedata.InvestorID, sizeof(TThostFtdcInvestorIDType), tradelist.begin()->InvestorID, sizeof(TThostFtdcInvestorIDType));
		memcpy_s(tradedata.InstrumentID, sizeof(TThostFtdcInstrumentIDType), tradelist.begin()->InstrumentID, sizeof(TThostFtdcInstrumentIDType));
		memcpy_s(tradedata.OrderRef, sizeof(TThostFtdcOrderRefType), tradelist.begin()->OrderRef, sizeof(TThostFtdcOrderRefType));
		memcpy_s(tradedata.UserID, sizeof(TThostFtdcUserIDType), tradelist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		memcpy_s(tradedata.ExchangeID, sizeof(TThostFtdcExchangeIDType), tradelist.begin()->ExchangeID, sizeof(TThostFtdcExchangeIDType));  // b
		memcpy_s(tradedata.TradeID, sizeof(TThostFtdcTradeIDType), tradelist.begin()->TradeID, sizeof(TThostFtdcTradeIDType));  //b
		tradedata.Direction = tradelist.begin()->Direction;  //b
		memcpy_s(tradedata.OrderSysID, sizeof(TThostFtdcOrderSysIDType), tradelist.begin()->OrderSysID, sizeof(TThostFtdcOrderSysIDType));  //b
		memcpy_s(tradedata.ParticipantID, sizeof(TThostFtdcParticipantIDType), tradelist.begin()->ParticipantID, sizeof(TThostFtdcParticipantIDType));  //b
		memcpy_s(tradedata.ClientID, sizeof(TThostFtdcClientIDType), tradelist.begin()->ClientID, sizeof(TThostFtdcClientIDType));  //b	
		tradedata.TradingRole = tradelist.begin()->TradingRole;  //b
		memcpy_s(tradedata.ExchangeInstID, sizeof(TThostFtdcExchangeInstIDType), tradelist.begin()->ExchangeInstID, sizeof(TThostFtdcExchangeInstIDType));  //b
		tradedata.OffsetFlag = tradelist.begin()->OffsetFlag;  //b
		tradedata.HedgeFlag = tradelist.begin()->HedgeFlag;  //b
		tradedata.Price = tradelist.begin()->Price;  //b
		tradedata.Volume = tradelist.begin()->Volume;  //b
		memcpy_s(tradedata.TradeDate, sizeof(TThostFtdcDateType), tradelist.begin()->TradeDate, sizeof(TThostFtdcDateType));  //b
		memcpy_s(tradedata.TradeTime, sizeof(TThostFtdcTimeType), tradelist.begin()->TradeTime, sizeof(TThostFtdcTimeType));  //b
		tradedata.TradeType = tradelist.begin()->TradeType;  //b
		tradedata.PriceSource = tradelist.begin()->PriceSource;  //b
		memcpy_s(tradedata.TraderID, sizeof(TThostFtdcTraderIDType), tradelist.begin()->TraderID, sizeof(TThostFtdcTraderIDType));  //b
		memcpy_s(tradedata.OrderLocalID, sizeof(TThostFtdcOrderLocalIDType), tradelist.begin()->OrderLocalID, sizeof(TThostFtdcOrderLocalIDType));  //b
		memcpy_s(tradedata.ClearingPartID, sizeof(TThostFtdcParticipantIDType), tradelist.begin()->ClearingPartID, sizeof(TThostFtdcParticipantIDType));  //b
		memcpy_s(tradedata.BusinessUnit, sizeof(TThostFtdcBusinessUnitType), tradelist.begin()->BusinessUnit, sizeof(TThostFtdcBusinessUnitType));  //b
		tradedata.SequenceNo = tradelist.begin()->SequenceNo;  //b
		memcpy_s(tradedata.TradingDay, sizeof(TThostFtdcDateType), tradelist.begin()->TradingDay, sizeof(TThostFtdcDateType));  //b
		tradedata.SettlementID = tradelist.begin()->SettlementID;  //b
		tradedata.BrokerOrderSeq = tradelist.begin()->BrokerOrderSeq;  //b
		tradedata.TradeSource = tradelist.begin()->TradeSource;  //b

		tradelist.erase(tradelist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);
		//orderlist.begin()->AccountID
		//临界区
		//EnterCriticalSection(&g_csdata);
		//orderlist.erase(orderlist.begin());
		//临界区
		//LeaveCriticalSection(&g_csdata);

		//printf("c++[%d] BranchID[%s] InvestorID[%s]\n",
		//	orderdata->cmd, orderdata->content.BrokerID, orderdata->content.InvestorID);
		
		return &tradedata;
	}
	else
	{
		return NULL;
	}
}






//期货发起银行资金转期货通知
CThostFtdcRspTransferField  banktofuturebyfuturedata;// = new CThostFtdcRspTransferField;
void *GetCmdContent_BankToFutureByFuture()
{
	if (banktofuturebyfuturelist.size() > 0)
	{
		memset(&banktofuturebyfuturedata, 0, sizeof(CThostFtdcTradeField));
		//临界区
		EnterCriticalSection(&g_csdata);
		memcpy_s(banktofuturebyfuturedata.TradeCode, sizeof(TThostFtdcTradeCodeType), banktofuturebyfuturelist.begin()->TradeCode, sizeof(TThostFtdcTradeCodeType));
		memcpy_s(banktofuturebyfuturedata.BankID, sizeof(TThostFtdcBankIDType), banktofuturebyfuturelist.begin()->BankID, sizeof(TThostFtdcBankIDType));
		memcpy_s(banktofuturebyfuturedata.BankBranchID, sizeof(TThostFtdcBankBrchIDType), banktofuturebyfuturelist.begin()->BankBranchID, sizeof(TThostFtdcBankBrchIDType));
		memcpy_s(banktofuturebyfuturedata.BrokerID, sizeof(TThostFtdcBrokerIDType), banktofuturebyfuturelist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(banktofuturebyfuturedata.BrokerBranchID, sizeof(TThostFtdcFutureBranchIDType), banktofuturebyfuturelist.begin()->BrokerBranchID, sizeof(TThostFtdcFutureBranchIDType));
		memcpy_s(banktofuturebyfuturedata.TradeDate, sizeof(TThostFtdcTradeDateType), banktofuturebyfuturelist.begin()->TradeDate, sizeof(TThostFtdcTradeDateType));
		memcpy_s(banktofuturebyfuturedata.TradeTime, sizeof(TThostFtdcTradeTimeType), banktofuturebyfuturelist.begin()->TradeTime, sizeof(TThostFtdcTradeTimeType));
		memcpy_s(banktofuturebyfuturedata.BankSerial, sizeof(TThostFtdcBankSerialType), banktofuturebyfuturelist.begin()->BankSerial, sizeof(TThostFtdcBankSerialType));
		memcpy_s(banktofuturebyfuturedata.TradingDay, sizeof(TThostFtdcTradeDateType), banktofuturebyfuturelist.begin()->TradingDay, sizeof(TThostFtdcTradeDateType));
		banktofuturebyfuturedata.PlateSerial = banktofuturebyfuturelist.begin()->PlateSerial;
		banktofuturebyfuturedata.LastFragment = banktofuturebyfuturelist.begin()->LastFragment;
		banktofuturebyfuturedata.SessionID = banktofuturebyfuturelist.begin()->SessionID;
		memcpy_s(banktofuturebyfuturedata.CustomerName, sizeof(TThostFtdcIndividualNameType), banktofuturebyfuturelist.begin()->CustomerName, sizeof(TThostFtdcIndividualNameType));
		banktofuturebyfuturedata.IdCardType = banktofuturebyfuturelist.begin()->IdCardType;
		memcpy_s(banktofuturebyfuturedata.IdentifiedCardNo, sizeof(TThostFtdcIdentifiedCardNoType), banktofuturebyfuturelist.begin()->IdentifiedCardNo, sizeof(TThostFtdcIdentifiedCardNoType));
		banktofuturebyfuturedata.CustType = banktofuturebyfuturelist.begin()->CustType;
		memcpy_s(banktofuturebyfuturedata.BankAccount, sizeof(TThostFtdcBankAccountType), banktofuturebyfuturelist.begin()->BankAccount, sizeof(TThostFtdcBankAccountType));
		memcpy_s(banktofuturebyfuturedata.BankPassWord, sizeof(TThostFtdcPasswordType), banktofuturebyfuturelist.begin()->BankPassWord, sizeof(TThostFtdcPasswordType));
		memcpy_s(banktofuturebyfuturedata.AccountID, sizeof(TThostFtdcAccountIDType), banktofuturebyfuturelist.begin()->AccountID, sizeof(TThostFtdcAccountIDType));
		memcpy_s(banktofuturebyfuturedata.Password, sizeof(TThostFtdcPasswordType), banktofuturebyfuturelist.begin()->Password, sizeof(TThostFtdcPasswordType));
		banktofuturebyfuturedata.InstallID = banktofuturebyfuturelist.begin()->InstallID;
		banktofuturebyfuturedata.FutureSerial = banktofuturebyfuturelist.begin()->FutureSerial;
		memcpy_s(banktofuturebyfuturedata.UserID, sizeof(TThostFtdcUserIDType), banktofuturebyfuturelist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		banktofuturebyfuturedata.VerifyCertNoFlag = banktofuturebyfuturelist.begin()->VerifyCertNoFlag;
		memcpy_s(banktofuturebyfuturedata.CurrencyID, sizeof(TThostFtdcCurrencyIDType), banktofuturebyfuturelist.begin()->CurrencyID, sizeof(TThostFtdcCurrencyIDType));
		banktofuturebyfuturedata.TradeAmount = banktofuturebyfuturelist.begin()->TradeAmount;
		banktofuturebyfuturedata.FutureFetchAmount = banktofuturebyfuturelist.begin()->FutureFetchAmount;
		banktofuturebyfuturedata.FeePayFlag = banktofuturebyfuturelist.begin()->FeePayFlag;
		banktofuturebyfuturedata.CustFee = banktofuturebyfuturelist.begin()->CustFee;
		banktofuturebyfuturedata.BrokerFee = banktofuturebyfuturelist.begin()->BrokerFee;
		memcpy_s(banktofuturebyfuturedata.Message, sizeof(TThostFtdcAddInfoType), banktofuturebyfuturelist.begin()->Message, sizeof(TThostFtdcAddInfoType));
		memcpy_s(banktofuturebyfuturedata.Digest, sizeof(TThostFtdcDigestType), banktofuturebyfuturelist.begin()->Digest, sizeof(TThostFtdcDigestType));
		banktofuturebyfuturedata.BankAccType = banktofuturebyfuturelist.begin()->BankAccType;
		memcpy_s(banktofuturebyfuturedata.DeviceID, sizeof(TThostFtdcDeviceIDType), banktofuturebyfuturelist.begin()->DeviceID, sizeof(TThostFtdcDeviceIDType));
		banktofuturebyfuturedata.BankSecuAccType = banktofuturebyfuturelist.begin()->BankSecuAccType;
		memcpy_s(banktofuturebyfuturedata.BrokerIDByBank, sizeof(TThostFtdcBankCodingForFutureType), banktofuturebyfuturelist.begin()->BrokerIDByBank, sizeof(TThostFtdcBankCodingForFutureType));
		memcpy_s(banktofuturebyfuturedata.BankSecuAcc, sizeof(TThostFtdcBankAccountType), banktofuturebyfuturelist.begin()->BankSecuAcc, sizeof(TThostFtdcBankAccountType));
		banktofuturebyfuturedata.BankPwdFlag = banktofuturebyfuturelist.begin()->BankPwdFlag;
		banktofuturebyfuturedata.SecuPwdFlag = banktofuturebyfuturelist.begin()->SecuPwdFlag;
		memcpy_s(banktofuturebyfuturedata.OperNo, sizeof(TThostFtdcOperNoType), banktofuturebyfuturelist.begin()->OperNo, sizeof(TThostFtdcOperNoType));
		banktofuturebyfuturedata.RequestID = banktofuturebyfuturelist.begin()->RequestID;
		banktofuturebyfuturedata.TID= banktofuturebyfuturelist.begin()->TID;
		banktofuturebyfuturedata.TransferStatus = banktofuturebyfuturelist.begin()->TransferStatus;
		banktofuturebyfuturedata.ErrorID = banktofuturebyfuturelist.begin()->ErrorID;
		memcpy_s(banktofuturebyfuturedata.ErrorMsg, sizeof(TThostFtdcErrorMsgType), banktofuturebyfuturelist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));
//		memcpy_s(banktofuturebyfuturedata.LongCustomerName, sizeof(TThostFtdcLongIndividualNameType), banktofuturebyfuturelist.begin()->LongCustomerName, sizeof(TThostFtdcLongIndividualNameType));
		
	
		banktofuturebyfuturelist.erase(banktofuturebyfuturelist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);
		//orderlist.begin()->AccountID
		//临界区
		//EnterCriticalSection(&g_csdata);
		//orderlist.erase(orderlist.begin());
		//临界区
		//LeaveCriticalSection(&g_csdata);

		return &banktofuturebyfuturedata;
		//return &(orderlist.begin());
	}
	else
	{
		return NULL;
	}
}


//期货发起银行资金转期货通知
CThostFtdcRspTransferField  futuretobankbyfuturedata;
void *GetCmdContent_FutureToBankByFuture()
{
	if (futuretobankbyfuturelist.size() > 0)
	{
		memset(&futuretobankbyfuturedata, 0, sizeof(CThostFtdcTradeField));
		//临界区
		EnterCriticalSection(&g_csdata);
		memcpy_s(banktofuturebyfuturedata.TradeCode, sizeof(TThostFtdcTradeCodeType), banktofuturebyfuturelist.begin()->TradeCode, sizeof(TThostFtdcTradeCodeType));
		memcpy_s(banktofuturebyfuturedata.BankID, sizeof(TThostFtdcBankIDType), banktofuturebyfuturelist.begin()->BankID, sizeof(TThostFtdcBankIDType));
		memcpy_s(banktofuturebyfuturedata.BankBranchID, sizeof(TThostFtdcBankBrchIDType), banktofuturebyfuturelist.begin()->BankBranchID, sizeof(TThostFtdcBankBrchIDType));
		memcpy_s(banktofuturebyfuturedata.BrokerID, sizeof(TThostFtdcBrokerIDType), banktofuturebyfuturelist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(banktofuturebyfuturedata.BrokerBranchID, sizeof(TThostFtdcFutureBranchIDType), banktofuturebyfuturelist.begin()->BrokerBranchID, sizeof(TThostFtdcFutureBranchIDType));
		memcpy_s(banktofuturebyfuturedata.TradeDate, sizeof(TThostFtdcTradeDateType), banktofuturebyfuturelist.begin()->TradeDate, sizeof(TThostFtdcTradeDateType));
		memcpy_s(banktofuturebyfuturedata.TradeTime, sizeof(TThostFtdcTradeTimeType), banktofuturebyfuturelist.begin()->TradeTime, sizeof(TThostFtdcTradeTimeType));
		memcpy_s(banktofuturebyfuturedata.BankSerial, sizeof(TThostFtdcBankSerialType), banktofuturebyfuturelist.begin()->BankSerial, sizeof(TThostFtdcBankSerialType));
		memcpy_s(banktofuturebyfuturedata.TradingDay, sizeof(TThostFtdcTradeDateType), banktofuturebyfuturelist.begin()->TradingDay, sizeof(TThostFtdcTradeDateType));
		banktofuturebyfuturedata.PlateSerial = banktofuturebyfuturelist.begin()->PlateSerial;
		banktofuturebyfuturedata.LastFragment = banktofuturebyfuturelist.begin()->LastFragment;
		banktofuturebyfuturedata.SessionID = banktofuturebyfuturelist.begin()->SessionID;
		memcpy_s(banktofuturebyfuturedata.CustomerName, sizeof(TThostFtdcIndividualNameType), banktofuturebyfuturelist.begin()->CustomerName, sizeof(TThostFtdcIndividualNameType));
		banktofuturebyfuturedata.IdCardType = banktofuturebyfuturelist.begin()->IdCardType;
		memcpy_s(banktofuturebyfuturedata.IdentifiedCardNo, sizeof(TThostFtdcIdentifiedCardNoType), banktofuturebyfuturelist.begin()->IdentifiedCardNo, sizeof(TThostFtdcIdentifiedCardNoType));
		banktofuturebyfuturedata.CustType = banktofuturebyfuturelist.begin()->CustType;
		memcpy_s(banktofuturebyfuturedata.BankAccount, sizeof(TThostFtdcBankAccountType), banktofuturebyfuturelist.begin()->BankAccount, sizeof(TThostFtdcBankAccountType));
		memcpy_s(banktofuturebyfuturedata.BankPassWord, sizeof(TThostFtdcPasswordType), banktofuturebyfuturelist.begin()->BankPassWord, sizeof(TThostFtdcPasswordType));
		memcpy_s(banktofuturebyfuturedata.AccountID, sizeof(TThostFtdcAccountIDType), banktofuturebyfuturelist.begin()->AccountID, sizeof(TThostFtdcAccountIDType));
		memcpy_s(banktofuturebyfuturedata.Password, sizeof(TThostFtdcPasswordType), banktofuturebyfuturelist.begin()->Password, sizeof(TThostFtdcPasswordType));
		banktofuturebyfuturedata.InstallID = banktofuturebyfuturelist.begin()->InstallID;
		banktofuturebyfuturedata.FutureSerial = banktofuturebyfuturelist.begin()->FutureSerial;
		memcpy_s(banktofuturebyfuturedata.UserID, sizeof(TThostFtdcUserIDType), banktofuturebyfuturelist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		banktofuturebyfuturedata.VerifyCertNoFlag = banktofuturebyfuturelist.begin()->VerifyCertNoFlag;
		memcpy_s(banktofuturebyfuturedata.CurrencyID, sizeof(TThostFtdcCurrencyIDType), banktofuturebyfuturelist.begin()->CurrencyID, sizeof(TThostFtdcCurrencyIDType));
		banktofuturebyfuturedata.TradeAmount = banktofuturebyfuturelist.begin()->TradeAmount;
		banktofuturebyfuturedata.FutureFetchAmount = banktofuturebyfuturelist.begin()->FutureFetchAmount;
		banktofuturebyfuturedata.FeePayFlag = banktofuturebyfuturelist.begin()->FeePayFlag;
		banktofuturebyfuturedata.CustFee = banktofuturebyfuturelist.begin()->CustFee;
		banktofuturebyfuturedata.BrokerFee = banktofuturebyfuturelist.begin()->BrokerFee;
		memcpy_s(banktofuturebyfuturedata.Message, sizeof(TThostFtdcAddInfoType), banktofuturebyfuturelist.begin()->Message, sizeof(TThostFtdcAddInfoType));
		memcpy_s(banktofuturebyfuturedata.Digest, sizeof(TThostFtdcDigestType), banktofuturebyfuturelist.begin()->Digest, sizeof(TThostFtdcDigestType));
		banktofuturebyfuturedata.BankAccType = banktofuturebyfuturelist.begin()->BankAccType;
		memcpy_s(banktofuturebyfuturedata.DeviceID, sizeof(TThostFtdcDeviceIDType), banktofuturebyfuturelist.begin()->DeviceID, sizeof(TThostFtdcDeviceIDType));
		banktofuturebyfuturedata.BankSecuAccType = banktofuturebyfuturelist.begin()->BankSecuAccType;
		memcpy_s(banktofuturebyfuturedata.BrokerIDByBank, sizeof(TThostFtdcBankCodingForFutureType), banktofuturebyfuturelist.begin()->BrokerIDByBank, sizeof(TThostFtdcBankCodingForFutureType));
		memcpy_s(banktofuturebyfuturedata.BankSecuAcc, sizeof(TThostFtdcBankAccountType), banktofuturebyfuturelist.begin()->BankSecuAcc, sizeof(TThostFtdcBankAccountType));
		banktofuturebyfuturedata.BankPwdFlag = banktofuturebyfuturelist.begin()->BankPwdFlag;
		banktofuturebyfuturedata.SecuPwdFlag = banktofuturebyfuturelist.begin()->SecuPwdFlag;
		memcpy_s(banktofuturebyfuturedata.OperNo, sizeof(TThostFtdcOperNoType), banktofuturebyfuturelist.begin()->OperNo, sizeof(TThostFtdcOperNoType));
		banktofuturebyfuturedata.RequestID = banktofuturebyfuturelist.begin()->RequestID;
		banktofuturebyfuturedata.TID = banktofuturebyfuturelist.begin()->TID;
		banktofuturebyfuturedata.TransferStatus = banktofuturebyfuturelist.begin()->TransferStatus;
		banktofuturebyfuturedata.ErrorID = banktofuturebyfuturelist.begin()->ErrorID;
		memcpy_s(banktofuturebyfuturedata.ErrorMsg, sizeof(TThostFtdcErrorMsgType), banktofuturebyfuturelist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));
//		memcpy_s(banktofuturebyfuturedata.LongCustomerName, sizeof(TThostFtdcLongIndividualNameType), banktofuturebyfuturelist.begin()->LongCustomerName, sizeof(TThostFtdcLongIndividualNameType));



		futuretobankbyfuturelist.erase(futuretobankbyfuturelist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);
		//orderlist.begin()->AccountID
		//临界区
		//EnterCriticalSection(&g_csdata);
		//orderlist.erase(orderlist.begin());
		//临界区
		//LeaveCriticalSection(&g_csdata);

		return &futuretobankbyfuturedata;
		//return &(orderlist.begin());
	}
	else
	{
		return NULL;
	}
}



//期货发起银行资金转期货通知
CThostFtdcQueryMaxOrderVolumeField  querymaxordervolumedata;;
void *GetCmdContent_QueryMaxOrderVolume()
{
	if (querymaxordervolumelist.size() > 0)
	{
		memset(&querymaxordervolumedata, 0, sizeof(CThostFtdcQueryMaxOrderVolumeField));
		EnterCriticalSection(&g_csdata);
		memcpy_s(querymaxordervolumedata.BrokerID, sizeof(TThostFtdcBrokerIDType), querymaxordervolumelist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(querymaxordervolumedata.InvestorID, sizeof(TThostFtdcInvestorIDType), querymaxordervolumelist.begin()->InvestorID, sizeof(TThostFtdcInvestorIDType));
		memcpy_s(querymaxordervolumedata.InstrumentID, sizeof(TThostFtdcInstrumentIDType), querymaxordervolumelist.begin()->InstrumentID, sizeof(TThostFtdcInstrumentIDType));
		querymaxordervolumedata.Direction = querymaxordervolumelist.begin()->Direction;
		querymaxordervolumedata.OffsetFlag = querymaxordervolumelist.begin()->OffsetFlag;
		querymaxordervolumedata.HedgeFlag = querymaxordervolumelist.begin()->HedgeFlag;
		querymaxordervolumedata.MaxVolume = querymaxordervolumelist.begin()->MaxVolume;
		querymaxordervolumelist.erase(querymaxordervolumelist.begin());
		LeaveCriticalSection(&g_csdata);
		return &querymaxordervolumedata;
	}
	else
	{
		return NULL;
	}
}




//结算确认
CThostFtdcSettlementInfoConfirmField settlementdata;// = new CThostFtdcSettlementInfoConfirmField;
void *GetCmdContent_Settlement()
{
	if (settlementlist.size() > 0)
	{
		memset(&settlementdata, 0, sizeof(CThostFtdcSettlementInfoConfirmField));
		//临界区
		EnterCriticalSection(&g_csdata);
		
		memcpy_s(settlementdata.BrokerID,    sizeof(TThostFtdcBrokerIDType), settlementlist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(settlementdata.InvestorID,  sizeof(TThostFtdcInvestorIDType), settlementlist.begin()->InvestorID, sizeof(TThostFtdcInvestorIDType));
		memcpy_s(settlementdata.ConfirmDate, sizeof(TThostFtdcDateType), settlementlist.begin()->ConfirmDate, sizeof(TThostFtdcDateType));
		memcpy_s(settlementdata.ConfirmTime, sizeof(TThostFtdcTimeType), settlementlist.begin()->ConfirmTime, sizeof(TThostFtdcTimeType));

		settlementlist.erase(settlementlist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);


		return &settlementdata;
	}
	else
	{
		return NULL;
	}
}


//错误数据
CThostFtdcRspInfoField errdata;// = new  CThostFtdcRspInfoField;
void *GetCmdContent_Error()
{
	if (errorlist.size() > 0)
	{
		memset(&errdata, 0, sizeof(CThostFtdcRspInfoField));
		//临界区
		EnterCriticalSection(&g_csdata);

		errdata.ErrorID = errorlist.begin()->ErrorID;
		memcpy_s(errdata.ErrorMsg, sizeof(TThostFtdcErrorMsgType), errorlist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));

		errorlist.erase(errorlist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);
		return &errdata;
	}
	else
	{
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
 



//登录
CThostFtdcRspUserLoginField logindata;// = new CThostFtdcRspUserLoginField;
void *GetCmdContent_LoginScuess()
{
	if (loginlist.size() > 0)
	{
		memset(&logindata, 0, sizeof(CThostFtdcRspUserLoginField));
		//临界区
		EnterCriticalSection(&g_csdata);

		//errdata->ErrorID = loginlist.begin()->ErrorID;
		memcpy_s(logindata.TradingDay, sizeof(TThostFtdcDateType), loginlist.begin()->TradingDay, sizeof(TThostFtdcDateType));
		memcpy_s(logindata.LoginTime,  sizeof(TThostFtdcTimeType), loginlist.begin()->LoginTime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.BrokerID,   sizeof(TThostFtdcBrokerIDType), loginlist.begin()->BrokerID, sizeof(TThostFtdcBrokerIDType));
		memcpy_s(logindata.UserID, sizeof(TThostFtdcUserIDType), loginlist.begin()->UserID, sizeof(TThostFtdcUserIDType));
		memcpy_s(logindata.SystemName, sizeof(TThostFtdcSystemNameType), loginlist.begin()->SystemName, sizeof(TThostFtdcSystemNameType));
		logindata.FrontID = loginlist.begin()->FrontID;
		logindata.SessionID = loginlist.begin()->SessionID;
		memcpy_s(logindata.MaxOrderRef, sizeof(TThostFtdcOrderRefType), loginlist.begin()->MaxOrderRef, sizeof(TThostFtdcOrderRefType));
		
		memcpy_s(logindata.SHFETime, sizeof(TThostFtdcTimeType), loginlist.begin()->SHFETime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.DCETime, sizeof(TThostFtdcTimeType), loginlist.begin()->DCETime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.CZCETime, sizeof(TThostFtdcTimeType), loginlist.begin()->CZCETime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.FFEXTime, sizeof(TThostFtdcTimeType), loginlist.begin()->FFEXTime, sizeof(TThostFtdcTimeType));
		memcpy_s(logindata.INETime, sizeof(TThostFtdcTimeType), loginlist.begin()->INETime, sizeof(TThostFtdcTimeType));
		loginlist.erase(loginlist.begin());

		//临界区
		LeaveCriticalSection(&g_csdata);
		return &logindata;
	}
	else
	{
		return NULL;
	}
}



//连接
int * connectdata = new int;
void *GetCmdContent_Connected()
{
	if (connectlist.size() > 0)
	{
		memset(connectdata, 0, sizeof(int));
		//临界区
		EnterCriticalSection(&g_csdata);

		//errdata->ErrorID = connectlist.begin()->ErrorID;
		//memcpy_s(errdata->ErrorMsg, sizeof(TThostFtdcErrorMsgType), connectlist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));

		connectlist.erase(connectlist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);
		return connectdata;
	}
	else
	{
		return NULL;
	}
}

//请求查询合约保证金率响应
CThostFtdcInstrumentMarginRateField * GroupMargindata = new CThostFtdcInstrumentMarginRateField;
void *GetCmdContent_ProductGroupMargin()
{
	if (MarginRatelist.size() > 0)
	{
		memset(GroupMargindata, 0, sizeof(CThostFtdcInstrumentMarginRateField));
		//临界区
		EnterCriticalSection(&g_csdata);

		//errdata->ErrorID = ProductGroupMarginlist.begin()->ErrorID;
		////memcpy_s(errdata->ErrorMsg, sizeof(TThostFtdcErrorMsgType), ProductGroupMarginlist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));

		MarginRatelist.erase(MarginRatelist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);
		return GroupMargindata;
	}
	else
	{
		return NULL;
	}
}



//估计字段要自己定义，或多个登录状态的定义
//list <CThostFtdcRspUserLoginField> loginlist;
//list <CThostFtdcRspUserLoginField>::iterator login_Iter;

//list <CThostFtdcSettlementInfoConfirmField> connectlist;
//list <CThostFtdcSettlementInfoConfirmField>::iterator connect_Iter;

///请求查询合约保证金率响应
//list <CThostFtdcInstrumentMarginRateField> MarginRatelist;
//list <CThostFtdcInstrumentMarginRateField>::iterator MarginRate_Iter;

///请求查询合约手续费率响应
//list <CThostFtdcInstrumentCommissionRateField> CommissionRatelist;
//list <CThostFtdcInstrumentCommissionRateField>::iterator CommissionRate_Iter;



//请求查询合约手续费率响应
CThostFtdcInstrumentCommissionRateField * CommissionRatedata = new CThostFtdcInstrumentCommissionRateField;
void *GetCmdContent_CommissionRate()
{
	if (CommissionRatelist.size() > 0)
	{
		memset(CommissionRatedata, 0, sizeof(CThostFtdcInstrumentCommissionRateField));
		//临界区
		EnterCriticalSection(&g_csdata);

		//errdata->ErrorID = CommissionRatelist.begin()->ErrorID;
		//memcpy_s(errdata->ErrorMsg, sizeof(TThostFtdcErrorMsgType), CommissionRatelist.begin()->ErrorMsg, sizeof(TThostFtdcErrorMsgType));

		CommissionRatelist.erase(CommissionRatelist.begin());
		//临界区
		LeaveCriticalSection(&g_csdata);
		return CommissionRatedata;
	}
	else
	{
		return NULL;
	}
}



