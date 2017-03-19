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

#ifdef PYCTPMARKET_EXPORTS
#define QUCIKLIB_MD_API __declspec(dllexport)
#else
#define QUCIKLIB_MD_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif 
	//获取硬件信息
	//QUCIKLIB_MD_API char *  GetHardDiskId();
	//QUCIKLIB_MD_API char *  GetCPUInfo();
	//QUCIKLIB_MD_API char *  GetMacAddress();


	QUCIKLIB_MD_API char *  GetApiVersion();
	QUCIKLIB_MD_API char *  GetTradingDay();
	void QUCIKLIB_MD_API RegisterFront(char *pszFrontAddress);
	void QUCIKLIB_MD_API RegisterNameServer(char *pszNsAddress);

	
	QUCIKLIB_MD_API char *  GetCmdContent_Tick();
	QUCIKLIB_MD_API void *  GetCmdContent_Error();

	QUCIKLIB_MD_API void *  GetCmdContent_SubMarketData();
	QUCIKLIB_MD_API void *  GetCmdContent_UnSubMarketData();

	QUCIKLIB_MD_API void *  GetCmdContent_LoginScuess();
	QUCIKLIB_MD_API void *  GetCmdContent_LoginFailer();
	QUCIKLIB_MD_API void *  GetCmdContent_LoginOut();

	QUCIKLIB_MD_API void *  GetCmdContent_Forquote();
	/*

	 ///初始化
	 ///@remark 初始化运行环境,只有调用后,接口才开始工作
	 void QUCIKLIB_MD_API Init();

	///订阅询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	int QUCIKLIB_MD_API SubscribeForQuoteRsp(char *ppInstrumentID[], int nCount);

	///退订询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	int QUCIKLIB_MD_API UnSubscribeForQuoteRsp(char *ppInstrumentID[], int nCount);

	///注册名字服务器用户信息
	///@param pFensUserInfo：用户信息。
	void QUCIKLIB_MD_API RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo);

	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	 void QUCIKLIB_MD_API Release();



	 ///注册回调接口
	 ///@param pSpi 派生自回调接口类的实例
	 void QUCIKLIB_MD_API RegisterSpi(CThostFtdcMdSpi *pSpi);
	 */
	 /////////////////////////////////////////
	//用户登录请求
	int QUCIKLIB_MD_API ReqUserLogin();
	//用户登出请求
	int QUCIKLIB_MD_API ReqUserLogout();
	//取消订阅
	void QUCIKLIB_MD_API UnSubscribeMarketData(const char *InstrumentID);

	void QUCIKLIB_MD_API Subscribe(const char *InstrumentID);
	void QUCIKLIB_MD_API Subscribe1(const char *InstrumentID, int periodtype1);
	void QUCIKLIB_MD_API Subscribe2(const char *InstrumentID, int periodtype1, int periodtype2);
	void QUCIKLIB_MD_API Subscribe3(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3);
	void QUCIKLIB_MD_API Subscribe4(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4);
	void QUCIKLIB_MD_API Subscribe5(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5);
	void QUCIKLIB_MD_API Subscribe6(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5, int periodtype6);
	void QUCIKLIB_MD_API Subscribe7(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5, int periodtype6, int periodtype7);
	void QUCIKLIB_MD_API Subscribe8(const char *InstrumentID, int periodtype1, int periodtype2, int periodtype3, int periodtype4, int periodtype5, int periodtype6, int periodtype7, int periodtype8);

    //询价
	void QUCIKLIB_MD_API SubscribeForQuoteRsp(char *InstrumentID);


	

	////////////////////////////////////////////////////////////////////////
	void QUCIKLIB_MD_API SetPrintState(bool printfstate);

	int QUCIKLIB_MD_API GetCmd();
	QUCIKLIB_MD_API char * GetCmdContent();
	int QUCIKLIB_MD_API OnCmd();
	int QUCIKLIB_MD_API GetUnGetCmdSize();


	int QUCIKLIB_MD_API GetUnGetLogSize();
	QUCIKLIB_MD_API char * GetLog(); //获得日志内容

	void QUCIKLIB_MD_API SetRejectdataTime(double  begintime1,double endtime1,double begintime2,double endtime2, double begintime3, double endtime3, double begintime4, double endtime4);


	//void  QUCIKLIB_MD_API strategy1();

	//void QUCIKLIB_MD_API TestArr(int &numbers, int a);

	void QUCIKLIB_MD_API TestArr(char** pIpAddList);
	 


	void QUCIKLIB_MD_API SetTitle(const char * title);
	void QUCIKLIB_MD_API Log(const char * filename, const char * content);

	bool QUCIKLIB_MD_API ReadInstrument();



	void QUCIKLIB_MD_API SaveTick(int index);

 
 //QUCIKLIB_MD_API char * Read_Ini(const char * filename, const char * option, const char * key);


	//char  QUCIKLIB_MD_API Read_Ini(const char * filename, const char * option, const char * key);


	 

	//void QUCIKLIB_MD_API Log(const char *name,const char *content);



	//bool QUCIKLIB_MD_API SetInstrumentNumber(int number);//取消了

 
	void QUCIKLIB_MD_API AddPeriod(const char *InstrumentID, int periodtype, bool printfdata);

	void QUCIKLIB_MD_API AddStopMonitor(const char *InstrumentID, int OrderRef,int mode,double percent);

	void QUCIKLIB_MD_API DeleteStopMonitor(const char *InstrumentID, int OrderRef, int mode, double percent);
	
	double QUCIKLIB_MD_API GetPeriodData(const char *InstrumentID, int periodtype, int PriceType, int ref);

 

	double QUCIKLIB_MD_API MA(const char *InstrumentID, int periodtype,int PriceType,int ref,int number);
	double QUCIKLIB_MD_API RSI(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);
	//double QUCIKLIB_MD_API SAR(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);
	double QUCIKLIB_MD_API SAR(const char *InstrumentID, int periodtype, int PriceType, int ref, int number, double step, double maxvalue);

	double QUCIKLIB_MD_API MACD(const char *InstrumentID, int periodtype, int PriceType, int ref, int number1,int number2,int number3); 

	double QUCIKLIB_MD_API CCI(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);
	double QUCIKLIB_MD_API ATR(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);
	//double QUCIKLIB_MD_API SAR(const char *InstrumentID, int periodtype, int PriceType, int ref, int number);



	//bool QUCIKLIB_MD_API CROSSUP(int price_Small0, int priceLong0, int priceSmall1, int priceLong1);

	//bool QUCIKLIB_MD_API CROSSDOWN(int priceSmall0, int priceLong0, int priceSmall1, int priceLong1);


	bool QUCIKLIB_MD_API CROSSUP(const char *InstrumentID, int indicators,int periodtype, int PriceType, int period1, int period2, bool printstate);

	bool QUCIKLIB_MD_API CROSSDOWN(const char *InstrumentID, int indicators, int periodtype, int PriceType, int period1, int period2, bool printstate);


    //策略
	bool QUCIKLIB_MD_API CROSSUP_S(int strategyid, int periodtype, int PriceType, int period1, int period2);
	bool QUCIKLIB_MD_API CROSSDOWN_S(int strategyid, int periodtype, int PriceType, int period1, int period2);






	void QUCIKLIB_MD_API *GetData(int index);
	
	int QUCIKLIB_MD_API GetInstrumentNum();

	int QUCIKLIB_MD_API IsInitOK();

#ifdef __cplusplus
}
#endif