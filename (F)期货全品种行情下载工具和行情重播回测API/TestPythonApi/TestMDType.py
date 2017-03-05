# -*- coding=utf-8 -*-

from ctypes import *

class sDepMarketData(Structure):
	_fields_ = [('TradingDay', 			c_char * 9),
				('InstrumentID',		c_char * 31),
				('ExchangeID',			c_char * 9),
				('ExchangeInstID',		c_char * 31),
				('LastPrice',			c_double),
				('PreSettlementPrice', 	c_double),
				('PreClosePrice',		c_double),
				('PreOpenInterest',		c_double),
				('OpenPrice',			c_double),
				('HighestPrice',		c_double),
				('LowestPrice',			c_double),
				('Volume',				c_int),
				('Turnover',			c_double),
				('OpenInterest',		c_double),
				('ClosePrice',			c_double),
				('SettlementPrice',		c_double),
				('UpperLimitPrice',		c_double),
				('LowerLimitPrice',		c_double),
				('PreDelta',			c_double),
				('CurrDelta',			c_double),
				('UpdateTime',			c_char * 9),
				('UpdateMillisec',		c_int32),
				('BidPrice1', 			c_double),
				('BidVolume1',			c_int32),
				('AskPrice1',			c_double),
				('AskVolume1',			c_int32),
				('BidPrice2',			c_double),
				('BidVolume2',			c_int32),
				('AskPrice2',			c_double),
				('AskVolume2',			c_int32),
				('BidPrice3',			c_double),
				('BidVolume3',			c_int32),
				('AskPrice3',			c_double),
				('AskVolume3',			c_int32),
				('BidPrice4',			c_double),
				('BidVolume4',			c_int32),
				('AskPrice4',			c_double),
				('AskVolume4',			c_int32),
				('BidPrice5',			c_double),
				('BidVolume5',			c_int32),
				('AskPrice5',			c_double),
				('AskVolume5',			c_int32),
				('AveragePrice',		c_double)
	]
	pass





# Direction or bsflag
TD_Buy 					= c_char('0')	# 买
TD_Sell 					= c_char('1')	# 卖

# offsetFlag
TD_Open 					= c_char('0')	# 开仓
TD_Close  				        = c_char('1')	# 平仓
TD_ForceClose 			                = c_char('2')	# 强平
TD_CloseToday 			                = c_char('3')	# 平今
TD_CloseYesterday 		                = c_char('4')	# 平昨
TD_ForceOff 				        = c_char('5')	# 强减
TD_LocalForceClose 		                = c_char('6')	# 本地强平


# price type
TD_OPT_AnyPrice  				= c_char('1')	# 任意价
TD_OPT_LimitPrice  				= c_char('2')	# 限价
TD_OPT_BestPrice  				= c_char('3')	# 最优价
TD_OPT_LastPrice  				= c_char('4')	# 最新价
TD_OPT_LastPricePlusOneTicks  	                = c_char('5')	# 最新价浮动上浮1个ticks
TD_OPT_LastPricePlusTwoTicks  	                = c_char('6')	# 最新价浮动上浮2个ticks
TD_OPT_LastPricePlusThreeTicks                  = c_char('7')	# 最新价浮动上浮3个ticks
TD_OPT_AskPrice1  				= c_char('8')	# 卖一价
TD_OPT_AskPrice1PlusOneTicks  	                = c_char('9')	# 卖一价浮动上浮1个ticks
TD_OPT_AskPrice1PlusTwoTicks  	                = c_char('A')	# 卖一价浮动上浮2个ticks
TD_OPT_AskPrice1PlusThreeTicks                  = c_char('B')	# 卖一价浮动上浮3个ticks
TD_OPT_BidPrice1  				= c_char('C')	# 买一价
TD_OPT_BidPrice1PlusOneTicks              	= c_char('D')	# 买一价浮动上浮1个ticks
TD_OPT_BidPrice1PlusTwoTicks  	                = c_char('E')	# 买一价浮动上浮2个ticks
TD_OPT_BidPrice1PlusThreeTicks                  = c_char('F')	# 买一价浮动上浮3个ticks


TD_Dynamic					= 1	# 动态止损
TD_Static   				        = 2	# 静态止损

TD_POSITION_Sell_Today               =9001  # 今日空单
TD_POSITION_Buy_Today                =9002  # 今日多单
TD_POSITION_Sell_History             =9003  # 非今日空单
TD_POSITION_Buy_History              =9004  # 非今日多单
TD_POSITION_Sell_All                 =9005  # 空单总计
TD_POSITION_Buy_All                  =9006  # 多单总计






# 周期定义
TD_ALL			                        = 10000  	# 所有周期
TD_M1 					        = 10001  	# M1   1分钟
TD_M3 					        = 10002  	# M3   3分钟
TD_M5 					        = 10003  	# M5   5分钟
TD_M10 					        = 10004  	# M10  10分钟
TD_M15 					        = 10005  	# M15  15分钟
TD_M30 					        = 10006  	# M30  30分钟
TD_M60 					        = 10007  	# M60  60分钟
TD_M120 			                = 10008  	# M120 120分钟
TD_D1			                        = 10009  	# D1   1日



# PRICE TYPE
TD_CLOSE 					= 10010 #c_char('0')	# 收盘价
TD_OPEN 					= 10011 #c_char('1')	# 开盘价
TD_HIGH 					= 10012 #c_char('2')	# 最高价
TD_LOW 					        = 10013 #c_char('3')	# 最低价


