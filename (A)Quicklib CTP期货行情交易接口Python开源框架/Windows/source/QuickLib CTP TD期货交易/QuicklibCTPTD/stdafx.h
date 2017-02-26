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

#undef UNICODE
#undef _UNICODE

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here
#include "ThostTraderApi/ThostFtdcUserApiDataType.h"
#include "ThostTraderApi/ThostFtdcUserApiStruct.h"
#include "ThostTraderApi/ThostFtdcTraderApi.h"

#include <string>
#include <iostream>
#include <map>
#include <fstream>

#define PYCTPTRADER_EXPORTS

#define TYPE_NUM 20  //品种数量应该于MD 订阅一致

#include <list>
struct cmdcontent
{
	int cmd;
	char content[31];
};
struct TT
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
};

//MAX_EVENTNUM取可以设置回调事件种类的最大值64，最大定义64个指令，不得更改为大于64的值
#define MAX_EVENTNUM  64
//回调事件均以"EID_Function"格式,其中"EID_"开头，"Function"是接收到此回调事件回调函数的名称
#define  EID_OnFrontDisconnected      0
#define  EID_OnFrontConnected         1
#define  EID_OnRspUserLogin_Scuess    2
#define  EID_OnRspUserLogin_Failer    3
#define  EID_OnRspUserLoginout_Scuess 4
#define  EID_OnRspUserLoginout_Failer 5
#define  EID_OnRtnDepthMarketData     6
#define  EID_IsErrorRspInfo           7
#define  EID_OnRspSubMarketData       8
#define  EID_OnRspUnSubMarketData     9
#define  EID_OnRspUserLogout          10

//trader
#define  EID_OnRspOrder                     11
#define  EID_OnRspTrade                     12     //add  2016.12.28
#define  EID_OnRtnInstrumentStatus          13     //add
#define  EID_OnRspQryAccountregister        14     //add 签约关系响应

#define  EID_OnRtnFromBankToFutureByFuture  15     //add
#define  EID_OnRtnFromFutureToBankByFuture  16     //add
#define  EID_OnRspQueryMaxOrderVolume       17     //add
#define  EID_OnRspSettlementInfoConfirm     18    //add

//回调类型
#define TD_SYSTEM_NONE                8000 //无
#define TD_LOGIN_SCUESS               8001 //登录成功
#define TD_LOGIN_DENIED               8002 //登录被拒绝
#define TD_LOGIN_ERRORPASSWORD        8003 //密码错误 ??
#define TD_LOGINOUT_SCUESS            8004 //登出成功
#define TD_LOGINOUT_DENIED            8005 //登录被拒绝    //ADD 2016.12.28
#define TD_NETCONNECT_SCUESS          8006 //连接成功
#define TD_NETCONNECT_BREAK           8007 //断开连接
#define TD_NETCONNECT_FAILER          8008 //连接失败 ??
//#define SYSTEM_SUBCRIBE_SCUESS  8008 //订阅成功
//#define SYSTEM_UNSUBCRIBE_SCUESS  8009 //取消订阅成功
//#define SYSTEM_NEWTICK  8010 //新Tick到来
#define TD_SYSTEM_ERROR  8011 //错误应答

#define TD_ORDER_INFO                 8012 //ORDER
#define TD_TRADE_INFO                 8013 //TRADER
#define TD_INSTRUMENT_STATUS          8014 //合约交易状态

#define TD_QUERY_ACCOUNTREGISTER      8015 //签约关系响应
#define TD_BYFUTURE_BANKTOFUTURE      8016 //期货发起银行资金转期货通知
#define TD_BYFUTURE_FUTURETOBANK      8017 //期货发起期货资金转银行通知
#define TD_QUERY_MAXORDERVOLUME       8018 //

#define TD_SETTLEMENTINFOCONFIRM      8019