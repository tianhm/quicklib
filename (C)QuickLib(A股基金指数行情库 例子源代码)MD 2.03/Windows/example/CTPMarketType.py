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
				('Volume',			c_longlong),
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
				('BidVolume1',			c_longlong),
				('AskPrice1',			c_double),
				('AskVolume1',			c_longlong),
				('BidPrice2',			c_double),
				('BidVolume2',			c_longlong),
				('AskPrice2',			c_double),
				('AskVolume2',			c_longlong),
				('BidPrice3',			c_double),
				('BidVolume3',			c_longlong),
				('AskPrice3',			c_double),
				('AskVolume3',			c_longlong),
				('BidPrice4',			c_double),
				('BidVolume4',			c_longlong),
				('AskPrice4',			c_double),
				('AskVolume4',			c_longlong),
				('BidPrice5',			c_double),
				('BidVolume5',			c_longlong),
				('AskPrice5',			c_double),
				('AskVolume5',			c_longlong),
				('AveragePrice',		c_double),
	                        
	                        ('ActionDay',	  	        c_char * 9),
	                        ('InstrumentName',		c_char * 21),
	                        ('TradingCount',		c_longlong),
	                        ('PERatio1',		        c_double),
	                        ('PERatio2',		        c_double),
	                        
	                        ('PriceUpDown1',		c_double),
	                        ('PriceUpDown2',		c_double),
	                        
	]
	pass








# 周期定义
QL_ALL			                        = 10000  	# 所有周期
QL_M1 					        = 10001  	# M1   1分钟
QL_M3 					        = 10002  	# M3   3分钟
QL_M5 					        = 10003  	# M5   5分钟
QL_M10 					        = 10004  	# M10  10分钟
QL_M15 					        = 10005  	# M15  15分钟
QL_M30 					        = 10006  	# M30  30分钟
QL_M60 					        = 10007  	# M60  60分钟
QL_M120 			                = 10008  	# M120 120分钟
QL_D1			                        = 10009  	# D1   1日



# PRICE TYPE
QL_CLOSE 					= 10010 #c_char('0')	# 收盘价
QL_OPEN 					= 10011 #c_char('1')	# 开盘价
QL_HIGH 					= 10012 #c_char('2')	# 最高价
QL_LOW 					        = 10013 #c_char('3')	# 最低价


