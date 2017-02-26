# -*- coding=utf-8 -*-

from ctypes import c_char

# Direction or bsflag
YT_D_Buy 					= c_char('0')	# 买
YT_D_Sell 					= c_char('1')	# 卖



# offsetFlag
YT_OF_Open 					= c_char('0')	# 开仓
YT_OF_Close  				= c_char('1')	# 平仓
YT_OF_ForceClose 			= c_char('2')	# 强平
YT_OF_CloseToday 			= c_char('3')	# 平今
YT_OF_CloseYesterday 		= c_char('4')	# 平昨
YT_OF_ForceOff 				= c_char('5')	# 强减
YT_OF_LocalForceClose 		= c_char('6')	# 本地强平


# price type
YT_OPT_AnyPrice  				= c_char('1')	# 任意价
YT_OPT_LimitPrice  				= c_char('2')	# 限价
YT_OPT_BestPrice  				= c_char('3')	# 最优价
YT_OPT_LastPrice  				= c_char('4')	# 最新价
YT_OPT_LastPricePlusOneTicks  	= c_char('5')	# 最新价浮动上浮1个ticks
YT_OPT_LastPricePlusTwoTicks  	= c_char('6')	# 最新价浮动上浮2个ticks
YT_OPT_LastPricePlusThreeTicks  = c_char('7')	# 最新价浮动上浮3个ticks
YT_OPT_AskPrice1  				= c_char('8')	# 卖一价
YT_OPT_AskPrice1PlusOneTicks  	= c_char('9')	# 卖一价浮动上浮1个ticks
YT_OPT_AskPrice1PlusTwoTicks  	= c_char('A')	# 卖一价浮动上浮2个ticks
YT_OPT_AskPrice1PlusThreeTicks  = c_char('B')	# 卖一价浮动上浮3个ticks
YT_OPT_BidPrice1  				= c_char('C')	# 买一价
YT_OPT_BidPrice1PlusOneTicks  	= c_char('D')	# 买一价浮动上浮1个ticks
YT_OPT_BidPrice1PlusTwoTicks  	= c_char('E')	# 买一价浮动上浮2个ticks
YT_OPT_BidPrice1PlusThreeTicks  = c_char('F')	# 买一价浮动上浮3个ticks


YT_Dynamic					= 1	# 动态止损
YT_Static   				        = 2	# 静态止损





YT_POSITION_Sell_Today               =9001  # 今日空单
YT_POSITION_Buy_Today                =9002  # 今日多单
YT_POSITION_Sell_History             =9003  # 非今日空单
YT_POSITION_Buy_History              =9004  # 非今日多单
YT_POSITION_Sell_All                 =9005  # 空单总计
YT_POSITION_Buy_All                  =9006  # 多单总计
