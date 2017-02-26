#1.本文件及调用的Python文件为范例代码
#2.本文件及调用的库文件Quicklib CTP期货资管交易库和交易库遵循 开源协议GPL v3
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

# -*- coding=utf-8 -*-
from ctypes import *
class QL_CThostFtdcOrderField(Structure):
    _fields_ = [('BrokerID', 			     c_char * 11),   #经纪公司代码
                ('InvestorID',		             c_char * 13),   #投资者代码
                ('InstrumentID',	             c_char * 31),   #合约代码
                ('OrderRef',		             c_char * 13),   #报单引用
                ('UserID',			     c_char * 16),   #用户代码
                ('OrderPriceType', 	             c_char * 1),    #报单价格条件
                ('Direction',		             c_char * 1),    #买卖方向
                ('CombOffsetFlag',		     c_char * 5),    #组合开平标志
                ('CombHedgeFlag',		     c_char * 5),    #组合投机套保标志
                ('LimitPrice',		             c_double),      #价格
                ('VolumeTotalOriginal',		     c_int),         #数量
                ('TimeCondition',		     c_char * 1),    #有效期类型
                ('GTDDate',			     c_char * 9),    #GTD日期
                ('VolumeCondition',		     c_char * 1),    #成交量类型
                ('MinVolume',			     c_int),         #最小成交量
                ('ContingentCondition',		     c_char * 1),    #触发条件
                ('StopPrice',		             c_double),      #止损价
                ('ForceCloseReason',		     c_char * 1),    #强平原因
                ('IsAutoSuspend',		     c_int),         #自动挂起标志
                ('BusinessUnit',		     c_char * 21),   #业务单元
                ('RequestID',			     c_int),         #请求编号
                ('OrderLocalID',		     c_char * 13),   #本地报单编号
                ('ExchangeID', 			     c_char * 9),    #交易所代码
                ('ParticipantID',		     c_char * 11),   #会员代码
                ('ClientID',			     c_char * 11),   #客户代码
                ('ExchangeInstID',		     c_char * 31),   #合约在交易所的代码
                ('TraderID',			     c_char * 21),   #交易所交易员代码
                ('InstallID',			     c_int32),       #安装编号
                ('OrderSubmitStatus',		     c_char * 1),    #报单提交状态
                ('NotifySequence',		     c_int32),       #报单提示序号
                ('TradingDay',			     c_char * 9),    #交易日
                ('SettlementID',		     c_int32),       #结算编号
                ('OrderSysID',			     c_char * 21),   #报单编号
                ('OrderSource',			     c_char * 1),    #报单来源
                ('OrderStatus',			     c_char * 1),    #报单状态
                ('OrderType',			     c_char * 1),    #报单类型
                ('VolumeTraded',		     c_int32),       #今成交数量
                ('VolumeTotal',			     c_int32),       #剩余数量
                ('InsertDate',			     c_char * 9),    #报单日期
                ('InsertTime',			     c_char * 9),    #委托时间
                ('ActiveTime',			     c_char * 9),    #激活时间
                ('SuspendTime',			     c_char * 9),    #挂起时间
                ('UpdateTime',			     c_char * 9),    #最后修改时间
                ('CancelTime',			     c_char * 9),    #撤销时间
                ('ActiveTraderID',		     c_char * 21),   #最后修改交易所交易员代码
                ('ClearingPartID',		     c_char * 11),   #结算会员编号
                ('SequenceNo',			     c_int32),       #序号
                ('FrontID',			     c_int32),       #前置编号
                ('SessionID',			     c_int32),       #会话编号
                ('UserProductInfo',		     c_char * 11),   #用户端产品信息
                ('StatusMsg',			     c_char * 81),   #状态信息
                ('UserForceClose',		     c_int32),       #用户强评标志
                ('ActiveUserID',		     c_char * 16),   #操作用户代码
                ('BrokerOrderSeq',		     c_int32),       #经纪公司报单编号          
                ('RelativeOrderSysID',		     c_char * 21),   #相关报单
                ('ZCETotalTradedVolume',	     c_int32),       #郑商所成交数量
                ('IsSwapOrder',		             c_int32),       #互换单标志
                ('BranchID',	                     c_char * 9),    #营业部编号
                ('InvestUnitID',		     c_char * 17),   #投资单元代码
                ('AccountID',	                     c_char * 13),   #资金账号
                ('CurrencyID',		             c_char * 4),    #币种代码
                ('IPAddress',	                     c_char * 16),   # IP地址        
                ('MacAddress',	                     c_char * 21)    # Mac地址              
                ]
    pass

class QL_CThostFtdcTradeField(Structure):
    _fields_ = [('BrokerID', 			     c_char * 11),   #经纪公司代码
                ('InvestorID',		             c_char * 13),   #投资者代码
                ('InstrumentID',	             c_char * 31),   #合约代码
                ('OrderRef',		             c_char * 13),   #报单引用
                ('UserID',			     c_char * 16),   #用户代码
                ('ExchangeID', 	                     c_char * 9),    #交易所代码
                ('TradeID',		             c_char * 21),   #成交编号
                ('Direction',		             c_char * 1),    #买卖方向
                ('OrderSysID',		             c_char * 21),   #报单编号
                ('ParticipantID',		     c_char * 11),   #会员代码
                ('ClientID',		             c_char * 11),   #客户代码
                ('TradingRole',		             c_char * 1),    #交易角色
                ('ExchangeInstID',		     c_char * 31),   #合约在交易所的代码
                ('OffsetFlag',		             c_char * 1),    #开平标志
                ('HedgeFlag',			     c_char * 1),    #投机套保标志
                ('Price',		             c_double),      #价格
                ('Volume',		             c_double),      #数量
                ('TradeDate',		             c_char * 9),    #成交日期
                ('TradeTime',		             c_char * 9),    #成交时间
                ('TradeType',		             c_char * 1),    #成交类型
                ('PriceSource',			     c_char * 1),    #成交价来源
                ('TraderID',		             c_char * 21),   #交易所交易员代码
                ('OrderLocalID', 		     c_char * 13),   #本地报单编号
                ('ClearingPartID',		     c_char * 11),   #结算会员编号
                ('BusinessUnit',	             c_char * 21),   #业务单元
                ('SequenceNo',		             c_int32),       #序号
                ('TradingDay',			     c_char * 9),    #交易日
                ('SettlementID',	             c_int32),       #结算编号
                ('BrokerOrderSeq',		     c_int32),       #经纪公司报单编号
                ('TradeSource',		             c_char * 1)     #成交来源      
                ]
    pass

class QL_CThostFtdcInstrumentStatusField(Structure):
    _fields_ = [('ExchangeID', 			     c_char * 11),   #交易所代码
                ('ExchangeInstID',		     c_char * 13),   #合约在交易所的代码
                ('SettlementGroupID',	             c_char * 31),   #结算组代码
                ('InstrumentID',		     c_char * 13),   #合约代码
                ('InstrumentStatus',	             c_char * 16),   #合约交易状态
                ('TradingSegmentSN', 	             c_char * 9),    #交易阶段编号
                ('EnterTime',		             c_char * 21),   #进入本状态时间
                ('EnterReason',		             c_char * 1)     #进入本状态原因
                ]
    pass
class QL_CThostFtdcSettlementInfoConfirmField(Structure):
    _fields_ = [('BrokerID', 			     c_char * 11),   #经纪公司代码
                ('InvestorID',		             c_char * 13),   #投资者代码
                ('ConfirmDate',	                     c_char * 9),    #确认日期
                ('ConfirmTime',			     c_char * 9)     #确认时间
                ]
    pass

class QL_CThostFtdcQueryMaxOrderVolumeField(Structure):
    _fields_ = [('BrokerID', 			     c_char * 11),   #经纪公司代码
                ('InvestorID',		             c_char * 13),   #投资者代码
                ('InstrumentID',	             c_char * 31),   #合约代码
                ('Direction',			     c_char * 1),    #买卖方向
                ('OffsetFlag',			     c_char * 1),    #开平标志
                ('HedgeFlag',			     c_char * 1),    #投机套保标志
                ('MaxVolume',			     c_int32),       #最大允许报单数量
                ]
    pass



class QL_CThostFtdcRspInfoField(Structure):
    _fields_ = [('ErrorID', 			     c_int32),       #错误代码
                ('ErrorMsg',		             c_char * 81)    #错误信息
                ]
    pass

class QL_CThostFtdcRspUserLoginField(Structure):
    _fields_ = [('TradingDay', 			     c_char * 9),       #交易日
                ('LoginTime',		             c_char * 9),       #登录成功时间
                ('BrokerID',		             c_char * 11),      #经纪公司代码                
                ('UserID',		             c_char * 16),      #用户代码                
                ('SystemName',		             c_char * 41),      #交易系统名称
                ('FrontID',		             c_int32),          #前置编号
                ('SessionID',		             c_int32),          #会话编号                
                ('MaxOrderRef',		             c_char * 13),      #最大报单引用                
                ('SHFETime',		             c_char * 9),       #上期所时间                
                ('DCETime',		             c_char * 9),       #大商所时间                
                ('CZCETime',		             c_char * 9),       #郑商所时间
                ('FFEXTime',		             c_char * 9),       #中金所时间                
                ('INETime',		             c_char * 9)        #能源中心时间                
                ]
    pass

      
class QL_CThostFtdcRspTransferField(Structure):
    _fields_ = [('TradeCode', 			     c_char * 7),       #业务功能码
                ('BankID',		             c_char * 4),       #银行代码
                ('BankBranchID',		     c_char * 5),       #银行分支机构代码                
                ('BrokerID',		             c_char * 11),      #期商代码                
                ('BrokerBranchID',		     c_char * 31),      #期商分支机构代码
                ('TradeDate',		             c_char * 9),       #交易日期
                ('TradeTime',		             c_char * 9),       #交易时间                
                ('BankSerial',		             c_char * 13),      #银行流水号                
                ('TradingDay',		             c_char * 9),       #交易系统日期                
                ('PlateSerial',		             c_int32),          #银期平台消息流水号                
                ('LastFragment',		     c_char * 1),       #最后分片标志
                ('SessionID',		             c_int32),          #会话号                
                ('CustomerName',		     c_char * 51),      #客户姓名
                ('IdCardType',		             c_char * 1),       #证件类型
                ('IdentifiedCardNo',		     c_char * 51),      #证件号码
                ('CustType',		             c_char * 1),       #客户类型                
                ('BankAccount',		             c_char * 41),      #银行帐号                
                ('BankPassWord',		     c_char * 41),      #银行密码                
                ('AccountID',		             c_char * 13),      #投资者帐号                
                ('Password',		             c_char * 41),      #期货密码
                ('InstallID',		             c_int32),          #安装编号                
                ('FutureSerial',		     c_int32),          #期货公司流水号
                ('UserID',		             c_char * 16),      #用户标识
                ('VerifyCertNoFlag',		     c_char * 1),       #验证客户证件号码标志
                ('CurrencyID',		             c_char * 4),       #币种代码                
                ('TradeAmount',		             c_double),         #转帐金额                
                ('FutureFetchAmount',		     c_double),         #期货可取金额                
                ('FeePayFlag',		             c_char * 1),       #费用支付标志                
                ('CustFee',		             c_double),         #应收客户费用
                ('BrokerFee',		             c_double),         #应收期货公司费用                
                ('Message',		             c_char * 129),     #发送方给接收方的消息
                ('Digest',		             c_char * 36),      #摘要                
                ('BankAccType',		             c_char * 1),       #银行帐号类型
                ('DeviceID',		             c_char * 3),       #渠道标志                
                ('BankSecuAccType',		     c_char * 1),       #期货单位帐号类型
                ('BrokerIDByBank',		     c_char * 33),      #期货公司银行编码                
                ('BankSecuAcc',		             c_char * 41),      #期货单位帐号                
                ('BankPwdFlag',		             c_char * 1),       #银行密码标志
                ('SecuPwdFlag',		             c_char * 1),       #期货资金密码核对标志                
                ('OperNo',		             c_char * 17),      #交易柜员
                ('RequestID',		             c_int32),          #请求编号                
                ('TID',		                     c_int32),          #交易ID
                ('TransferStatus',		     c_char * 1),       #转账交易状态                
                ('ErrorID',		             c_int32),          #错误代码
                ('ErrorMsg',		             c_char * 81),      #错误信息                
                ('LongCustomerName',		     c_char * 161)      #长客户姓名                    
                
                ]
    pass


QL_Long 					= 0	# 买
QL_Short 					= 1	# 卖

# Direction or bsflag
QL_D_Buy 					= c_char('0')	# 买
QL_D_Sell 					= c_char('1')	# 卖



# offsetFlag
QL_OF_Open 					= c_char('0')	# 开仓
QL_OF_Close  				= c_char('1')	# 平仓
QL_OF_ForceClose 			= c_char('2')	# 强平
QL_OF_CloseToday 			= c_char('3')	# 平今
QL_OF_CloseYesterday 		= c_char('4')	# 平昨
QL_OF_ForceOff 				= c_char('5')	# 强减
QL_OF_LocalForceClose 		= c_char('6')	# 本地强平


# price type
QL_OPT_AnyPrice  				= c_char('1')	# 任意价
QL_OPT_LimitPrice  				= c_char('2')	# 限价
QL_OPT_BestPrice  				= c_char('3')	# 最优价
QL_OPT_LastPrice  				= c_char('4')	# 最新价
QL_OPT_LastPricePlusOneTicks  	= c_char('5')	# 最新价浮动上浮1个ticks
QL_OPT_LastPricePlusTwoTicks  	= c_char('6')	# 最新价浮动上浮2个ticks
QL_OPT_LastPricePlusThreeTicks  = c_char('7')	# 最新价浮动上浮3个ticks
QL_OPT_AskPrice1  				= c_char('8')	# 卖一价
QL_OPT_AskPrice1PlusOneTicks  	= c_char('9')	# 卖一价浮动上浮1个ticks
QL_OPT_AskPrice1PlusTwoTicks  	= c_char('A')	# 卖一价浮动上浮2个ticks
QL_OPT_AskPrice1PlusThreeTicks  = c_char('B')	# 卖一价浮动上浮3个ticks
QL_OPT_BidPrice1  				= c_char('C')	# 买一价
QL_OPT_BidPrice1PlusOneTicks  	= c_char('D')	# 买一价浮动上浮1个ticks
QL_OPT_BidPrice1PlusTwoTicks  	= c_char('E')	# 买一价浮动上浮2个ticks
QL_OPT_BidPrice1PlusThreeTicks  = c_char('F')	# 买一价浮动上浮3个ticks


QL_Dynamic					= 1	# 动态止损
QL_Static   				        = 2	# 静态止损


QL_Dynamic_Capital					= 0	# 动态止损
QL_Static_Capital   				        = 1	# 静态止损


QL_POSITION_Sell_Today               =9001  # 今日空单
QL_POSITION_Buy_Today                =9002  # 今日多单
QL_POSITION_Sell_History             =9003  # 非今日空单
QL_POSITION_Buy_History              =9004  # 非今日多单
QL_POSITION_Sell_All                 =9005  # 所有空单
QL_POSITION_Buy_All                  =9006  # 所有多单
