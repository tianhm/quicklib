/*
1.本文件为Quicklib 期货交易库底层代码
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

#ifdef PYCTPTRADER_EXPORTS
#	define QUICKLIB_TD_API __declspec(dllexport)
#else
#	define QUICKLIB_TD_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

int QUICKLIB_TD_API Login();

int QUICKLIB_TD_API InsertOrderByRate(char *Instrument, char direction, char offsetFlag, char priceType, double price,double rate, bool BalanceType,int multiplier);
int QUICKLIB_TD_API InsertOrder(char *Instrument,char direction, char offsetFlag, char priceType, double price, int num);
int QUICKLIB_TD_API DeleteOrder(char *Instrument, int OrderRef);
int QUICKLIB_TD_API QryTradedVol(int OrderRef);
int QUICKLIB_TD_API QryPosition(char *Instrument,int positiontype);   

int QUICKLIB_TD_API ReqQueryMaxOrderVolume(char * BrokerID, char * InvestorID, char * InstrumentID, char Direction, char  OffsetFlag, char  HedgeFlag, int MaxVolume);

int  QUICKLIB_TD_API ReqQryContractBank();
double  QUICKLIB_TD_API QryExchangeMarginRate(char *Instrument, int positiontype);    //保证金率
double  QUICKLIB_TD_API QryUnderlyingMultiple(char *Instrument);    //乘数

///期货发起银行资金转期货请求
//int  QUICKLIB_TD_API  ReqFromBankToFutureByFuture(int nRequestID);  //ADD

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
	int nRequestID);

///期货发起期货资金转银行请求
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
	int nRequestID);  //ADD



int QUICKLIB_TD_API ReqQryInstrument();



void QUICKLIB_TD_API *QryPositionList(int i);
double QUICKLIB_TD_API QryBalance(bool BalanceType);     //1静态权益 0动态权益 自己增加
double QUICKLIB_TD_API QryAvailable();   //可用资金
void QUICKLIB_TD_API SetShowPosition(bool showstate);   //可用资金

int QUICKLIB_TD_API GetCmd();
QUICKLIB_TD_API char * GetCmdContent2();

void QUICKLIB_TD_API * GetCmdContent();

void QUICKLIB_TD_API * GetCmdContent_Order();
void QUICKLIB_TD_API * GetCmdContent_Trade();


void QUICKLIB_TD_API * GetCmdContent_BankToFutureByFuture();
void QUICKLIB_TD_API * GetCmdContent_FutureToBankByFuture();

void QUICKLIB_TD_API * GetCmdContent_QueryMaxOrderVolume();


void QUICKLIB_TD_API * GetCmdContent_Settlement();
void QUICKLIB_TD_API * GetCmdContent_Error();

void QUICKLIB_TD_API * GetCmdContent_LoginScuess();
void QUICKLIB_TD_API * GetCmdContent_Connected();
void QUICKLIB_TD_API * GetCmdContent_ProductGroupMargin();
void QUICKLIB_TD_API * GetCmdContent_CommissionRate();


void QUICKLIB_TD_API * GetCmdContent_AccountRegist();

void QUICKLIB_TD_API * GetCmdContent_BankToFutureByFuture();
void QUICKLIB_TD_API * GetCmdContent_FutureToBankByFuture();
 


int QUICKLIB_TD_API OnCmd();
int QUICKLIB_TD_API GetUnGetCmdSize();

//double QUICKLIB_TD_API QryAvailable2();   //可用资金
#ifdef __cplusplus
}
#endif