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
//本地程序数据共享
#include "SharedMemoryServer.h"


SharedMemoryServer::SharedMemoryServer(const char * code)
{

	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		code);                 // name of mapping object

	if (hMapFile == NULL)
	{
		//_tprintf(TEXT("Could not create file mapping object (%d).\n"),
		//	GetLastError());


		//CString temp;
		//temp.Format("Could not create file mapping object %d", GetLastError());
		//AfxMessageBox(temp);
		printf("Could not create file mapping object %d", GetLastError());
		failerstate = true;
		return;// true;
	}
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		//_tprintf(TEXT("Could not map view of file (%d).\n"),
		//	GetLastError());


		//CString temp;
		//temp.Format("Could not map view of file %d", GetLastError());
		//AfxMessageBox(temp);

		printf("Could not map view of file %d", GetLastError());

		CloseHandle(hMapFile);
		failerstate = true;
		return;// true;
	}

}


SharedMemoryServer::~SharedMemoryServer()
{

}





bool  SharedMemoryServer::CreateShareMemory(const char * code, const char * szMsg,int MsgLen)
{
	

	//CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
	CopyMemory((PVOID)pBuf, szMsg, (MsgLen * sizeof(char)));
	//_getch();

	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);
	 
	//printf("finish\n");

	//CString temp;
	//temp.Format("%s %s",code,szMsg);
	//AfxMessageBox(temp);

	//system("pause");
	printf("%s %s", code, szMsg);
 

	return false;
}