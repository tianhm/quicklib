# -*- coding=utf-8 -*-
from CTPMarketType import *
import time
#1.本文件及调用的Python文件为范例代码
#2.本文件及调用的库文件Quicklib CTP期货行情库和交易库遵循 开源协议GPL v3
#简单的说：对基于GPL v3协议的源代码，若个人或机构仅仅是自己使用，则可以闭源。
#若基于该开源代码，开发出程序或衍生产品用于商业行为则也必须开源。

#Quciklib Python框架和工具遵循GPL v3协议包括：
#（1）Quicklib CTP   期货行情库
#（2）Quicklib CTP   期货交易库
#（3）Quicklib CTP2  A股行情库
#（4）Quicklib MOM模式  博易资管交易库
#（用于接入资管投顾系统，MOM模式可实现私募进行投顾的选拔考核，并通过自己的风控系统接入实盘）

#Quciklib Python框架和工具暂不遵循开源协议包括：
#（5）Quicklib 监控器库（预警、监控、交易信号数据复制、跟单）（可免费试用）

#对Quciklib开源库做出贡献的，并得到原始作者肯定的，将公布在http://www.quciklib.cn网站上，
#并添加在《开源说明和感谢.txt》，并将该文件不断更新放入每一个新版本的Quicklib库里。

#原始作者：QQ 147423661 林(王登高)
#官方网站：http://www.quicklib.cn
#官方QQ群：5172183(1群)、25884087(2群)

class CTPMarket(object):
	def __init__(self):
		#self.d1 = CDLL('thostmduserapi.dll')
		self.d2 = CDLL('QuickLibMD.dll')
		i = 0
		while (i < 5):
			time.sleep(1)
			if (self.d2.IsInitOK() == 0):
				i += 1
			else:
				break
		else:
			print('market init error')
			return

		self.fReqUserLogin = self.d2.ReqUserLogin
		self.fReqUserLogin.argtypes = []
		self.fReqUserLogin.restype = c_int32
		
		
		self.fReqUserLogout = self.d2.ReqUserLogout
		self.fReqUserLogout.argtypes = []
		self.fReqUserLogout.restype = c_int32		
		
		self.fUnSubscribeMarketData = self.d2.UnSubscribeMarketData
		self.fUnSubscribeMarketData.argtypes = [c_char_p]
		
		self.fOnCmd = self.d2.OnCmd
		self.fOnCmd.argtypes = []
		self.fOnCmd.restype = c_int32
		
		self.fGetCmdContent_Tick = self.d2.GetCmdContent_Tick
		self.fGetCmdContent_Tick.argtypes = []
		self.fGetCmdContent_Tick.restype = c_char_p	
		
		self.fGetCmdContent_SubMarketData = self.d2.GetCmdContent_SubMarketData
		self.fGetCmdContent_SubMarketData.argtypes = []
		self.fGetCmdContent_SubMarketData.restype = c_void_p			
		
		self.fGetCmdContent_UnSubMarketData = self.d2.GetCmdContent_UnSubMarketData
		self.fGetCmdContent_UnSubMarketData.argtypes = []
		self.fGetCmdContent_UnSubMarketData.restype = c_void_p			

		self.fGetCmdContent_Forquote = self.d2.GetCmdContent_Forquote
		self.fGetCmdContent_Forquote.argtypes = []
		self.fGetCmdContent_Forquote.restype = c_void_p	
		
		self.fGetCmdContent_Error = self.d2.GetCmdContent_Error
		self.fGetCmdContent_Error.argtypes = []
		self.fGetCmdContent_Error.restype = c_void_p	
		
		self.fGetCmdContent_LoginScuess = self.d2.GetCmdContent_LoginScuess
		self.fGetCmdContent_LoginScuess.argtypes = []
		self.fGetCmdContent_LoginScuess.restype = c_void_p
		
		self.fGetCmdContent_LoginFailer = self.d2.GetCmdContent_LoginFailer
		self.fGetCmdContent_LoginFailer.argtypes = []
		self.fGetCmdContent_LoginFailer.restype = c_void_p
		
		self.fGetCmdContent_LoginOut = self.d2.GetCmdContent_LoginOut
		self.fGetCmdContent_LoginOut.argtypes = []
		self.fGetCmdContent_LoginOut.restype = c_void_p
		
		self.fGetCmd = self.d2.GetCmd
		self.fGetCmd.argtypes = []
		self.fGetCmd.restype = c_int32
	
		self.fGetCmdContent = self.d2.GetCmdContent
		self.fGetCmdContent.argtypes = []
		self.fGetCmdContent.restype = c_char_p		
		
		self.fGetUnGetCmdSize = self.d2.GetUnGetCmdSize
		self.fGetUnGetCmdSize.argtypes = []		
		self.fGetUnGetCmdSize.restype = c_int32		
		
		self.fGetApiVersion = self.d2.GetApiVersion
		self.fGetApiVersion.argtypes = []		
		self.fGetApiVersion.restype = c_char_p				
		
		self.fGetTradingDay = self.d2.GetTradingDay
		self.fGetTradingDay.argtypes = []		
		self.fGetTradingDay.restype = c_char_p
		
		self.fRegisterFront = self.d2.RegisterFront
		self.fRegisterFront.argtypes = [c_char_p]		
 
		
		self.fRegisterNameServer = self.d2.RegisterNameServer
		self.fRegisterNameServer.argtypes = [c_char_p]		
		
		self.fSetPrintState = self.d2.SetPrintState
		self.fSetPrintState.argtypes = [c_bool]
		

		self.fGetData = self.d2.GetData
		self.fGetData.argtypes = [c_int32]
		self.fGetData.restype = c_void_p

		self.fSubscribe = self.d2.Subscribe
		self.fSubscribe.argtypes = [c_char_p]
		
		self.fSubscribeForQuoteRsp = self.d2.SubscribeForQuoteRsp
		self.fSubscribeForQuoteRsp.argtypes = [c_char_p]		
		
		
		self.fSubscribe1 = self.d2.Subscribe1
		self.fSubscribe1.argtypes = [c_char_p,c_int32]
		
		
		self.fSubscribe2 = self.d2.Subscribe2
		self.fSubscribe2.argtypes = [c_char_p,c_int32,c_int32]
		
		
		self.fSubscribe3 = self.d2.Subscribe3
		self.fSubscribe3.argtypes = [c_char_p,c_int32,c_int32,c_int32]
		
		
		self.fSubscribe4 = self.d2.Subscribe4
		self.fSubscribe4.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32]
		
		
		self.fSubscribe5 = self.d2.Subscribe5
		self.fSubscribe5.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32,c_int32]
		
		
		self.fSubscribe6 = self.d2.Subscribe6
		self.fSubscribe6.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32]
		
		
		self.fSubscribe7 = self.d2.Subscribe7
		self.fSubscribe7.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32]
		
		
		self.fSubscribe8 = self.d2.Subscribe8
		self.fSubscribe8.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32]		
		

		self.InstrumentNum = self.d2.GetInstrumentNum()
		
		
		#self.fAddPeriod = self.d2.AddPeriod
		#self.fAddPeriod.argtypes = [c_char_p]	
		
		self.fAddStopMonitor = self.d2.AddStopMonitor
		self.fAddStopMonitor.argtypes = [c_int32,c_int32,c_double]
		self.fAddStopMonitor.restype = c_int32			
		
		
		
		self.fGetPeriodData = self.d2.GetPeriodData
		self.fGetPeriodData.argtypes = [c_char_p,c_int32,c_int32,c_int32]
		self.fGetPeriodData.restype = c_double	
		
		
		self.fSaveTick = self.d2.SaveTick
		self.fSaveTick.argtypes = [c_int32]
		self.fSaveTick.restype = c_void_p
		
		
		self.fReadInstrument = self.d2.ReadInstrument
		self.fReadInstrument.argtypes = []
		self.fReadInstrument.restype = c_bool		
		
		
		
		self.fSetTitle = self.d2.SetTitle
		self.fSetTitle.argtypes = [c_char_p]
		self.fSetTitle.restype = c_void_p		
				


		
		self.fLog = self.d2.Log
		self.fLog.argtypes = [c_char_p,c_char_p]
		self.fLog.restype = c_void_p		
				
		self.fSetRejectdataTime = self.d2.SetRejectdataTime
		self.fSetRejectdataTime.argtypes = [c_double,c_double,c_double,c_double,c_double,c_double,c_double,c_double]
		self.fSetRejectdataTime.restype = c_void_p			
		
		self.fAddPeriod = self.d2.AddPeriod
		self.fAddPeriod.argtypes = [c_char_p,c_int32,c_bool]	
		
		
		#fCrossUp(contract, periodtype, PriceType, period1, period2)
	        self.fCrossUp = self.d2.CROSSUP
		self.fCrossUp.argtypes = [c_char_p,c_int32,c_int32,c_int32]
		self.fCrossUp.restype = c_bool
		
	        self.fCrossDown = self.d2.CROSSDOWN	
		self.fCrossDown.argtypes = [c_char_p,c_int32,c_int32,c_int32]
		self.fCrossDown.restype = c_bool
		
		
		#策略函数
	        self.fCrossUp_s = self.d2.CROSSUP_S
		self.fCrossUp_s.argtypes = [c_int32,c_int32,c_int32,c_int32]
		self.fCrossUp_s.restype = c_bool
		
	        self.fCrossDown_s = self.d2.CROSSDOWN_S
		self.fCrossDown_s.argtypes = [c_int32,c_int32,c_int32,c_int32]
		self.fCrossDown_s.restype = c_bool		
		
                #market.MA('zn1607',YT_M1,500,'YT_CLOSE')		
		
		
		#self.fTestMA = self.d2.Test_MA
		
		
                self.fMA = self.d2.MA
		self.fMA.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32]	
		self.fMA.restype = c_double
		

		self.Index = dict()
		for i in range(self.InstrumentNum):
			data = self.fGetData(i)
			data = cast(data, POINTER(sDepMarketData))
			self.Index[str(data[0].InstrumentID)] = data
		pass

	def TradingDay(self, contract):
		# 交易日
		if contract in self.Index:
			return self.Index[contract][0].TradingDay
		else:
			return ''

	def InstrumentID(self, contract):
		# 合约代码
		if contract in self.Index:
			return self.Index[contract][0].InstrumentID
		else:
			return ''

	def ExchangeID(self, contract):
		# 交易所代码
		if contract in self.Index:
			return self.Index[contract][0].ExchangeID
		else:
			return ''

	def ExchangeInstID(self, contract):
		# 合约在交易所的代码
		if contract in self.Index:
			return self.Index[contract][0].ExchangeInstID
		else:
			return ''

	def LastPrice(self, contract):
		# 最新价
		if contract in self.Index:
			return round(self.Index[contract][0].LastPrice, 1)
		else:
			return -1

	def PreSettlementPrice(self, contract):
		# 上次结算价
		if contract in self.Index:
			return round(self.Index[contract][0].PreSettlementPrice, 1)
		else:
			return -1

	def PreClosePrice(self, contract):
		# 昨收盘
		if contract in self.Index:
			return round(self.Index[contract][0].PreClosePrice, 1)
		else:
			return -1

	def PreOpenInterest(self, contract):
		# 昨持仓量
		if contract in self.Index:
			return self.Index[contract][0].PreOpenInterest
		else:
			return -1

	def OpenPrice(self, contract):
		# 今开盘
		if contract in self.Index:
			return round(self.Index[contract][0].OpenPrice, 1)
		else:
			return -1

	def HighestPrice(self, contract):
		# 最高价
		if contract in self.Index:
			return round(self.Index[contract][0].HighestPrice, 1)
		else:
			return -1

	def LowestPrice(self, contract):
		# 最低价
		if contract in self.Index:
			return round(self.Index[contract][0].LowestPrice, 1)
		else:
			return -1

	def Volume(self, contract):
		# 数量
		if contract in self.Index:
			return self.Index[contract][0].Volume
		else:
			return -1

	def Turnover(self, contract):
		# 成交金额
		if contract in self.Index:
			return self.Index[contract][0].Turnover
		else:
			return -1

	def OpenInterest(self, contract):
		# 持仓量
		if contract in self.Index:
			return self.Index[contract][0].OpenInterest
		else:
			return -1

	def ClosePrice(self, contract):
		# 今收盘
		if contract in self.Index:
			return round(self.Index[contract][0].ClosePrice, 1)
		else:
			return -1

	def SettlementPrice(self, contract):
		# 本次结算价
		if contract in self.Index:
			return round(self.Index[contract][0].SettlementPrice, 1)
		else:
			return -1

	def UpperLimitPrice(self, contract):
		# 涨停板价
		if contract in self.Index:
			return round(self.Index[contract][0].UpperLimitPrice, 1)
		else:
			return -1

	def LowerLimitPrice(self, contract):
		# 跌停板价
		if contract in self.Index:
			return round(self.Index[contract][0].LowerLimitPrice, 1)
		else:
			return -1

	def PreDelta(self, contract):
		# 昨虚实度
		if contract in self.Index:
			return self.Index[contract][0].PreDelta
		else:
			return -1

	def CurrDelta(self, contract):
		# 今虚实度
		if contract in self.Index:
			return self.Index[contract][0].CurrDelta
		else:
			return -1

	def UpdateTime(self, contract):
		# 最后修改时间
		if contract in self.Index:
			return self.Index[contract][0].UpdateTime
		else:
			return ''

	def UpdateMillisec(self, contract):
		# 最后修改毫秒
		if contract in self.Index:
			return self.Index[contract][0].UpdateMillisec
		else:
			return 0

	def BidPrice1(self, contract):
		# 申买价一
		if contract in self.Index:
			return round(self.Index[contract][0].BidPrice1, 1)
		else:
			return -1

	def BidVolume1(self, contract):
		# 申买量一
		if contract in self.Index:
			return round(self.Index[contract][0].BidVolume1, 1)
		else:
			return -1

	def AskPrice1(self, contract):
		# 申卖价一
		if contract in self.Index:
			return round(self.Index[contract][0].AskPrice1, 1)
		else:
			return -1

	def AskVolume1(self, contract):
		# 申卖量一
		if contract in self.Index:
			return round(self.Index[contract][0].AskVolume1, 1)
		else:
			return -1

	def BidPrice2(self, contract):
		# 申买价二
		if contract in self.Index:
			return round(self.Index[contract][0].BidPrice2, 1)
		else:
			return -1

	def BidVolume2(self, contract):
		# 申买量二
		if contract in self.Index:
			return round(self.Index[contract][0].BidVolume2, 1)
		else:
			return None

	def AskPrice2(self, contract):
		# 申卖价二
		if contract in self.Index:
			return round(self.Index[contract][0].AskPrice2, 1)
		else:
			return None

	def AskVolume2(self, contract):
		# 申卖量二
		if contract in self.Index:
			return round(self.Index[contract][0].AskVolume2, 1)
		else:
			return None

	def BidPrice3(self, contract):
		# 申买价三
		if contract in self.Index:
			return round(self.Index[contract][0].BidPrice3, 1)
		else:
			return None

	def BidVolume3(self, contract):
		# 申买量三
		if contract in self.Index:
			return round(self.Index[contract][0].BidVolume3, 1)
		else:
			return None

	def AskPrice3(self, contract):
		# 申卖价三
		if contract in self.Index:
			return round(self.Index[contract][0].AskPrice3, 1)
		else:
			return None

	def AskVolume3(self, contract):
		# 申卖量三
		if contract in self.Index:
			return round(self.Index[contract][0].AskVolume3, 1)
		else:
			return None

	def BidPrice4(self, contract):
		# 申买价四
		if contract in self.Index:
			return round(self.Index[contract][0].BidPrice4, 1)
		else:
			return None

	def BidVolume4(self, contract):
		# 申买量四
		if contract in self.Index:
			return round(self.Index[contract][0].BidVolume4, 1)
		else:
			return None

	def AskPrice4(self, contract):
		# 申卖价四
		if contract in self.Index:
			return round(self.Index[contract][0].AskPrice4, 1)
		else:
			return None

	def AskVolume4(self, contract):
		# 申卖量四
		if contract in self.Index:
			return round(self.Index[contract][0].AskVolume4, 1)
		else:
			return None

	def BidPrice5(self, contract):
		# 申买价五
		if contract in self.Index:
			return round(self.Index[contract][0].BidPrice5, 1)
		else:
			return None

	def BidVolume5(self, contract):
		# 申买量五
		if contract in self.Index:
			return round(self.Index[contract][0].BidVolume5, 1)
		else:
			return None

	def AskPrice5(self, contract):
		# 申卖价五
		if contract in self.Index:
			return round(self.Index[contract][0].AskPrice5, 1)
		else:
			return None

	def AskVolume5(self, contract):
		# 申卖量五
		if contract in self.Index:
			return (self.Index[contract][0].AskVolume5, 1)
		else:
			return None

	def AveragePrice(self, contract):
		# 当日均价
		if contract in self.Index:
			return round(self.Index[contract][0].AveragePrice, 1)
		else:
			return None
		
	#订阅询价
	def SubscribeForQuoteRsp(self, contract):
                # 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribeForQuoteRsp(c_char_p(contract))
                #data = self.fGetData(len(self.Index))
                #data = cast(data, POINTER(sDepMarketData))
                #self.Index[contract] = data		
		

	def Subcribe(self, contract):
                # 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe(c_char_p(contract))
                data = self.fGetData(len(self.Index))
                data = cast(data, POINTER(sDepMarketData))
                self.Index[contract] = data

	def Subcribe1(self, contract,period1):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe1(c_char_p(contract),period1)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data
		#self.fAddPeriod(c_char_p(contract),c_char_p(period1))
		
	def Subcribe2(self, contract,period1,period2):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe2(c_char_p(contract),period1,period2)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data
		#self.fAddPeriod(c_char_p(contract),c_char_p(period1))
		#self.fAddPeriod(c_char_p(contract),c_char_p(period2))
		
	def Subcribe3(self, contract,period1,period2,period3):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe3(c_char_p(contract),period1,period2,period3)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data
		#self.fAddPeriod(c_char_p(contract),c_char_p(period1))
		#self.fAddPeriod(c_char_p(contract),c_char_p(period2))
		#self.fAddPeriod(c_char_p(contract),c_char_p(period3))
		
	def Subcribe4(self, contract,period1,period2,period3,period4):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe4(c_char_p(contract),period1,period2,period3,period4)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data
		
	def Subcribe5(self, contract,period1,period2,period3,period4,period5):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe5(c_char_p(contract),period1,period2,period3,period4,period5)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data	
		
	def Subcribe6(self, contract,period1,period2,period3,period4,period5,period6):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe6(c_char_p(contract),period1,period2,period3,period4,period5,period6)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data			
		
	def Subcribe7(self, contract,period1,period2,period3,period4,period5,period6,period7):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe7(c_char_p(contract),period1,period2,period3,period4,period5,period6,period7)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data	
		
	def Subcribe8(self, contract,period1,period2,period3,period4,period5,period6,period7,period8):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe8(c_char_p(contract),period1,period2,period3,period4,period5,period6,period7,period8)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data					


	#def testMA():
		# MA测试
		#self.fTestMA()	

	def MA(self, contract, periodtype, pricetype, ref,number):
		# MA测试
		return self.fMA(contract,periodtype, pricetype, ref, number)
			
	def CrossUp(self, contract, periodtype, pricetype, period1, period2):
		self.fCrossUp(contract, periodtype, pricetype, period1, period2)
	
	def CrossDown(self, contract, periodtype, pricetype, period1, period2):
		self.fCrossDown(contract, periodtype, pricetype, period1, period2)
 
        #策略函数
	def CrossDown_s(self,strategyid,periodtype, pricetype, period1, period2):
		self.fCrossDown_s(strategyid,periodtype, pricetype, period1, period2)
 
	def AddPeriod(self, contract,periodtype):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fAddPeriod(contract,periodtype,True)
		#data = self.fGetData(len(self.Index))
		#data = cast(data, POINTER(sDepMarketData))
		#self.Index[contract] = data

	#def AddPeriod(self, contract):
		# MA测试
		#self.fAddPeriod(c_char_p(contract))
	#设置止损监控
	def AddStopMonitor(self, orderRef,Mode,percent):
		return self.fAddStopMonitor(orderRef,Mode,percent)	

	def GetPeriodData(self, contract,periodtype,pricetype,ref):
		return self.fGetPeriodData(contract,periodtype,pricetype,ref)	
	
	def SaveTick(self,index):
	        self.fSaveTick(index)
		
	def ReadInstrumentIni(self):
		return self.fReadInstrument()	
	
	def SetTitle(self,title):
	        try:
			return self.fSetTitle(title)		
	        except:
			return 0	
	
	def Log(self,content):
		return self.fLog(content)
	
	def SetRejectdataTime(self,begintime1,endtime1,begintime2,endtime2,begintime3,endtime3,begintime4,endtime4):
		return self.fSetRejectdataTime(begintime1,endtime1,begintime2,endtime2,begintime3,endtime3,begintime4,endtime4)
	
	def Login(self):
		return self.fReqUserLogin()
	
	def Logout(self):
		return self.fReqUserLogout()
	
	def UnSubscribeMarketData(self, contract):
		return self.fUnSubscribeMarketData(contract)
	
	def OnCmd(self):
		return self.fOnCmd()
	
	def GetCmd(self):
		#fGetCmd(), fGetCmdContent()必须配对同时使用
		return (self.fGetCmd(),self.fGetCmdContent()) 	
	
	def SetPrintState(self,printstate):
		return self.fSetPrintState(printstate)
	
	def GetUnGetCmdSize(self):
		return self.fGetUnGetCmdSize()
	
	def GetApiVersion(self):
		return self.fGetApiVersion()
	
	def GetTradingDay(self):
		return self.fGetTradingDay()
	
	def RegisterFront(self,pszFrontAddress):
		self.fRegisterFront(pszFrontAddress)
		  
	def RegisterNameServer(self,pszNsAddress):
		self.fRegisterNameServer(pszNsAddress)
		
	def GetCmdContent_Tick(self):
		#错误信息回调
		return self.fGetCmdContent_Tick()
	
	def GetCmdContent_SubMarketData(self):
		#错误信息回调
		return self.fGetCmdContent_SubMarketData()
	
	def GetCmdContent_UnSubMarketData(self):
		#错误信息回调
		return self.fGetCmdContent_UnSubMarketData()	
	
	
	
	def GetCmdContent_Forquote(self):
		#错误信息回调
		return self.fGetCmdContent_Forquote()
	
	
	def GetCmdContent_Error(self):
		#错误信息回调
		return self.fGetCmdContent_Error()
	
	def GetCmdContent_LoginScuess(self):
		#错误信息回调
		return self.fGetCmdContent_LoginScuess()
	
	def GetCmdContent_LoginFailer(self):
		#错误信息回调
		return self.fGetCmdContent_LoginFailer()	
	
	def GetCmdContent_LoginOut(self):
		#错误信息回调
		return self.fGetCmdContent_LoginOut()		
	
		  