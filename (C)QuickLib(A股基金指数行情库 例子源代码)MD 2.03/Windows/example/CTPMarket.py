# -*- coding=utf-8 -*-

from CTPMarketType import *
import time

class CTPMarket(object):
	def __init__(self):
		#self.d1 = CDLL('thostmduserapi.dll')
		self.d2 = CDLL('QuickLibAShareMD.dll')
		
		
		i = 0
		
		while( i<20):
		      time.sleep(1)
	              i = i+ 1		      
		      if i>20:
			 print('market init error')  
			 return
		      if (self.d2.IsInitOK()):
			  break		
		
		print('market init success')
		time.sleep(3)	 
 

		self.fGetData = self.d2.GetData
		self.fGetData.argtypes = [c_int32]
		self.fGetData.restype = c_void_p
		
		self.fSetPrintState = self.d2.SetPrintState
		self.fSetPrintState.argtypes = [c_bool]
		
		self.fGetUnGetCmdSize = self.d2.GetUnGetCmdSize
		self.fGetUnGetCmdSize.argtypes = []		
		self.fGetUnGetCmdSize.restype = c_int32	

		self.fSubscribe = self.d2.Subscribe
		self.fSubscribe.argtypes = [c_char_p,c_bool]
		
		
		self.fSubscribe1 = self.d2.Subscribe1
		self.fSubscribe1.argtypes = [c_char_p,c_int32,c_bool]
		
		
		self.fSubscribe2 = self.d2.Subscribe2
		self.fSubscribe2.argtypes = [c_char_p,c_int32,c_int32,c_bool]
		
		
		self.fSubscribe3 = self.d2.Subscribe3
		self.fSubscribe3.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_bool]
		
		
		self.fSubscribe4 = self.d2.Subscribe4
		self.fSubscribe4.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32,c_bool]
		
		
		self.fSubscribe5 = self.d2.Subscribe5
		self.fSubscribe5.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32,c_int32,c_bool]
		
		
		self.fSubscribe6 = self.d2.Subscribe6
		self.fSubscribe6.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32,c_bool]
		
		
		self.fSubscribe7 = self.d2.Subscribe7
		self.fSubscribe7.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32,c_bool]
		
		
		self.fSubscribe8 = self.d2.Subscribe8
		self.fSubscribe8.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32,c_int32,c_bool]		
		

		
		
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
		
		
		#self.fReadInstrument = self.d2.ReadInstrument
		#self.fReadInstrument.argtypes = [c_bool]
		#self.fReadInstrument.restype = c_bool		
		
		
		
		self.fSetTitle = self.d2.SetTitle
		self.fSetTitle.argtypes = [c_char_p]
		self.fSetTitle.restype = c_void_p		
				


		
		self.fLog = self.d2.Log
		self.fLog.argtypes = [c_char_p,c_char_p]
		self.fLog.restype = c_void_p		
				

		self.fOnCmd = self.d2.OnCmd
		self.fOnCmd.argtypes = []
		self.fOnCmd.restype = c_int32	
		
		self.fGetCmd = self.d2.GetCmd
		self.fGetCmd.argtypes = []
		self.fGetCmd.restype = c_int32
		
		self.fGetCmdContent = self.d2.GetCmdContent
		self.fGetCmdContent.argtypes = []
		self.fGetCmdContent.restype = c_char_p		
				
		
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
		#self.InstrumentNum = self.d2.GetInstrumentNum()
		#self.InstrumentNum.argtypes = []
		#self.InstrumentNum.restype = c_int32			
		
		self.InstrumentNum = self.d2.GetInstrumentNum()
		#self.fTestMA = self.d2.Test_MA
		
		
                self.fMA = self.d2.MA
		self.fMA.argtypes = [c_char_p,c_int32,c_int32,c_int32,c_int32]	
		self.fMA.restype = c_double
		
		#print 'InstrumentNum : %d\n'%self.InstrumentNum
                		
		self.fGetApiVersion = self.d2.GetApiVersion
		self.fGetApiVersion.argtypes = []		
		self.fGetApiVersion.restype = c_char_p				
	
 
		self.fRegisterFront = self.d2.RegisterFront
		self.fRegisterFront.argtypes = [c_char_p]		
		
		self.fGetCmdContent_Tick = self.d2.GetCmdContent_Tick
		self.fGetCmdContent_Tick.argtypes = []
		self.fGetCmdContent_Tick.restype = c_char_p			
	
		self.Index = dict()
		for i in range(self.InstrumentNum):
			data = self.fGetData(i)
			data = cast(data, POINTER(sDepMarketData))
			#print str(data[0].InstrumentID)
			self.Index[str(data[0].InstrumentID)] = data
		pass




	 
	 
 
	        self.Index = dict()
	        #for i in range(20000):	
	        #print '%d\n'%self.InstrumentNum
	        usnum=0;
	        j=0;
	        #while(usnum==self.InstrumentNum)
		while(j<60):
		          time.sleep(1)
		          j = j+ 1		      
		          if j>50:
			          print('Dict init error')  
			          return

		          for i in range(self.InstrumentNum):	

			          #time.sleep(0.01)
			          try:
				          data = self.fGetData(i)
				          data = cast(data, POINTER(sDepMarketData))
				          if data[0].InstrumentID<>"":
					          usnum=usnum+1;

				          #print u"\n元素[%s]"%data[0].InstrumentID
				          #print u"最新价A [%0.02f]"%data[0].LastPrice;
				          #print u"开A [%0.02f]"%data[0].OpenPrice;
				          #print u"收A [%0.02f]"%data[0].ClosePrice;
				          #print u"高A [%0.02f]"%data[0].HighPrice;
				          #print u"低A [%0.02f]"%data[0].LowPrice;

				          self.Index[str(data[0].InstrumentID)] = data

				          #print u"最新价B [%0.02f]"%self.Index[str(data[0].InstrumentID)][0].LastPrice
				          #print u"最新价B [%0.02f]"%self.Index[str(data[0].InstrumentID)][0].OpenPrice
				          #print u"最新价B [%0.02f]"%self.Index[str(data[0].InstrumentID)][0].ClosePrice



			          except:
				          sss=0
				          #print 'error%d'%i
			          #time.sleep(100)
			          pass
		          if usnum>=self.InstrumentNum:
			      print('Dict init success')  
			      break
		          else:  
			      print('Dict init not complete[%d]'%usnum)  
			      print('Total[%d]'%self.InstrumentNum)  
			      #break	


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
			return round(self.Index[contract][0].LastPrice, 3)
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
			return round(self.Index[contract][0].PreClosePrice, 3)
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
			return round(self.Index[contract][0].OpenPrice, 3)
		else:
			return -1

	def HighestPrice(self, contract):
		# 最高价
		if contract in self.Index:
			return round(self.Index[contract][0].HighestPrice, 3)
		else:
			return -1

	def LowestPrice(self, contract):
		# 最低价
		if contract in self.Index:
			return round(self.Index[contract][0].LowestPrice, 3)
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
			return round(self.Index[contract][0].ClosePrice, 3)
		else:
			return -1

	def SettlementPrice(self, contract):
		# 本次结算价
		if contract in self.Index:
			return round(self.Index[contract][0].SettlementPrice, 3)
		else:
			return -1

	def UpperLimitPrice(self, contract):
		# 涨停板价
		if contract in self.Index:
			return round(self.Index[contract][0].UpperLimitPrice, 3)
		else:
			return -1

	def LowerLimitPrice(self, contract):
		# 跌停板价
		if contract in self.Index:
			return round(self.Index[contract][0].LowerLimitPrice, 3)
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
			return round(self.Index[contract][0].BidPrice1, 3)
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
			return round(self.Index[contract][0].AskPrice1, 3)
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
			return round(self.Index[contract][0].BidPrice2, 3)
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
			return round(self.Index[contract][0].AskPrice2, 3)
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
			return round(self.Index[contract][0].BidPrice3, 3)
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
			return round(self.Index[contract][0].AskPrice3, 3)
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
			return round(self.Index[contract][0].BidPrice4, 3)
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
			return round(self.Index[contract][0].AskPrice4, 3)
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
			return round(self.Index[contract][0].BidPrice5, 3)
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
			return round(self.Index[contract][0].AskPrice5, 3)
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
			return round(self.Index[contract][0].AveragePrice, 3)
		else:
			return None
	#ADD
	def ActionDay(self, contract):
		# 业务日期
		if contract in self.Index:
			return self.Index[contract][0].ActionDay
		else:
			return ''
		
	def InstrumentName(self, contract):
		# 合约名称
		if contract in self.Index:
			return self.Index[contract][0].InstrumentName
		else:
			return ''			
		
	def TradingCount(self, contract):
		# 成交笔数
		if contract in self.Index:
			return self.Index[contract][0].TradingCount
		else:
			return ''	
		
	def PERatio1(self, contract):
		# 市盈率
		if contract in self.Index:
			return self.Index[contract][0].PERatio1
		else:
			return ''		
		
	def PERatio2(self, contract):
		# 市盈率
		if contract in self.Index:
			return self.Index[contract][0].PERatio2
		else:
			return ''
		
	def PriceUpDown1(self, contract):
		# 价格升跌1
		if contract in self.Index:
			return self.Index[contract][0].PriceUpDown1
		else:
			return ''		

	def PriceUpDown2(self, contract):
		# 价格升跌2
		if contract in self.Index:
			return self.Index[contract][0].PriceUpDown2
		else:
			return ''			

	def Subcribe(self, contract,printfstate):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe(c_char_p(contract),printfstate)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data

	def Subcribe1(self, contract,period1,printfstate):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe1(c_char_p(contract),period1,printfstate)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data
		#self.fAddPeriod(c_char_p(contract),c_char_p(period1))
		
	def Subcribe2(self, contract,period1,period2,printfstate):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe2(c_char_p(contract),period1,period2,printfstate)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data
		#self.fAddPeriod(c_char_p(contract),c_char_p(period1))
		#self.fAddPeriod(c_char_p(contract),c_char_p(period2))
		
	def Subcribe3(self, contract,period1,period2,period3,printfstate):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe3(c_char_p(contract),period1,period2,period3,printfstate)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data
		#self.fAddPeriod(c_char_p(contract),c_char_p(period1))
		#self.fAddPeriod(c_char_p(contract),c_char_p(period2))
		#self.fAddPeriod(c_char_p(contract),c_char_p(period3))
		
	def Subcribe4(self, contract,period1,period2,period3,period4,printfstate):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe4(c_char_p(contract),period1,period2,period3,period4,printfstate)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data
		
	def Subcribe5(self, contract,period1,period2,period3,period4,period5,printfstate):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe5(c_char_p(contract),period1,period2,period3,period4,period5,printfstate)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data	
		
	def Subcribe6(self, contract,period1,period2,period3,period4,period5,period6,printfstate):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe6(c_char_p(contract),period1,period2,period3,period4,period5,period6,printfstate)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data			
		
	def Subcribe7(self, contract,period1,period2,period3,period4,period5,period6,period7,printfstate):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe7(c_char_p(contract),period1,period2,period3,period4,period5,period6,period7,printfstate)
		data = self.fGetData(len(self.Index))
		data = cast(data, POINTER(sDepMarketData))
		self.Index[contract] = data	
		
	def Subcribe8(self, contract,period1,period2,period3,period4,period5,period6,period7,period8,printfstate):
		# 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
		self.fSubscribe8(c_char_p(contract),period1,period2,period3,period4,period5,period6,period7,period8,printfstate)
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
		
		
	#def ReadInstrumentIni(self,showstate):
	#	self.fReadInstrument(showstate)	
		
	
	def SetTitle(self,title):
		try:
		    return self.fSetTitle(title)		
	        except:
	            return 0;		
	
	def LogFile(self,content):
		return self.fLog(content)


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

	def RegisterFront(self,pszFrontAddress):
		self.fRegisterFront(pszFrontAddress)
		
	def GetCmdContent_Tick(self):
		#错误信息回调
		return self.fGetCmdContent_Tick()				