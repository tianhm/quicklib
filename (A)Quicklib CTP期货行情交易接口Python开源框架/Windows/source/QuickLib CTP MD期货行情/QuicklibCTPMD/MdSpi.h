/*
1.本文件为Quicklib 期货行情库底层代码
2.本文件及调用的库文件Quicklib CTP期货行情库和交易库遵循 开源协议GPL v3
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
#pragma once
#include <map>
#include <string>
#include <algorithm>
#include "iostream"

#include <iostream> 
#include <windows.h>
using namespace std;
struct InstrumentInfo
{
	string strategyfile[300];
	//int strategy[100];
	int strategyfilenum;
	int position[100];
	bool tradestate;
};

#include "def.h"
/*
class CStrategy : public CWinThread
{
public:
	//CStrategy();
	void strategy();

};
 */

class CMdSpi : public CThostFtdcMdSpi
{

public:

	double begintime1;
	double begintime2;
	double begintime3;
	double begintime4;

	double endtime1;
	double endtime2;
	double endtime3;
	double endtime4;
	//void  strategy();
	//CStrategy *m_pCStrategyThread;


	BOOL mInitOK;
	HANDLE mhSyncObj;
	CThostFtdcMdApi *mpUserApi;

	int RequestID;
	//void strategy();

	//int savetickstate;

	void WirteTick_Detail(const char * InstrumentID, const CThostFtdcDepthMarketDataField *pDepthMarketData);
	void WirteTick_Simple(const char * InstrumentID, const char * ticktime, double price);


	CMdSpi();
	~CMdSpi();
	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast);

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);


 
	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///询价通知
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

	// class CthostMdApi::Init()
	BOOL Init();

	BOOL IsInitOK(){return mInitOK;}

    //询价
	void SubscribeForQuoteRsp(char * InstrumentID);

	void SubscribeMarketData();
	void UnSubscribeMarketData();

	int ReqUserLogin();

	int ReqUserLogout();

	char * GetApiVersion();

	char *  GetTradingDay();
	void   RegisterFront(char *pszFrontAddress);
	void   RegisterNameServer(char *pszNsAddress);
private:

	// 
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);

};
