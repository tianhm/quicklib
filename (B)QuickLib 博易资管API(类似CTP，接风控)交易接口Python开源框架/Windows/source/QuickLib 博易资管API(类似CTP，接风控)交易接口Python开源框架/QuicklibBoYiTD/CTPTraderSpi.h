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

#pragma once

//授权功能
#include "SharedMemoryServer.h"
#define MAX_MAP_NUM   3000  //内存共享订阅数
#define MAX_PROCESS_NUM   300  //内存共享

 
//RSA
#include <atlstr.h> 
//#include "RSABigInt.h"
//RSA

//HANDLE hMapFileHash[MAX_PROCESS_NUM];//进程数量CRC32值
class QLCTPTraderSpi: public CThostFtdcTraderSpi
{
public:

	//授权功能

	//内存共享
	bool CheckMemoryExit();
	HANDLE hMapFile[MAX_MAP_NUM];
	LPCTSTR pBuf;
	//void WriteToMemory(const char *mdata, int id);
	//void WriteToMemoryProcess(const char *mdata, int id);
	//void WriteToMemoryProcessID(const char *mdata, int id);
	//内存共享

	int id = -1;
	int licnum = 5; //授权数量
	int processid = MAX_MAP_NUM; //不容易被占用

	HANDLE hMapFileMaxProcessID;//进程最大ID值，计数

	bool CheckMemoryExit2();
	//bool ExitCheckState;
	//授权功能

	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason); //添加的

	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);//客户端认证响应 //need


	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//登出请求响应 
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast); //need



	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, 
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);  //ADD 2016.12.28

	//合约交易状态通知
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);//ADD


	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);	//自己增加 

 


	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);





	virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///请求查询合约保证金率响应
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///请求查询合约手续费率响应
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX应该合并一个
	///请求查询合约响应					
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspQryInstrument2(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	///查询最大报单数量响应
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//新增加的


	///请求查询银期签约关系响应
	virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///期货发起银行资金转期货通知
	virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer);

	///期货发起期货资金转银行通知
	virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer);


 public: //更改为public
		///请求查询资金账户
	void ReqQryTradingAccount();
	///请求查询投资者持仓
	void ReqQryInvestorPosition();
 	///请求查询合约(乘数)
	void ReqQryInstrument(char *Instrument);

	///查询最大报单数量请求
	int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID);
 
	//查询保证金率，新增
	void  ReqQryInvestorProductGroupMargin(char *Instrument);
	void  ReqQryInstrumentMarginRate(char *Instrument);
	//void ReqQryInvestorPosition();


	///请求查询合约
	int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID);

	///请求查询转帐流水
	//virtual int ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID);

	///请求查询银期签约关系
	//virtual int ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID);

	///请求查询签约银行
	virtual int ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID);


	///期货发起银行资金转期货请求
	int ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID);

	///期货发起期货资金转银行请求
	int ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID);







	HANDLE hSyncObj;
	int iRequestID;
	int iOrderRef;
	bool bInitOK;

	int FRONT_ID;
	int SESSION_ID;

public:

	int InsertOrder(char *InstrumentID, TThostFtdcDirectionType dir,char offsetFlag, char priceType, double price, int num);

	int DeleteOrder(char *InstrumentID, DWORD orderRef);

	void ReqUserLogin();

	void ReqSettlementInfoConfirm();

	QLCTPTraderSpi();
	~QLCTPTraderSpi();

	bool Init();
	bool IsInitOK(){return bInitOK;}
};