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

#导入CTP交易库
from CTPTrader import *
trader = CTPTrader()   #交易接口类赋值给变量 

#------------------------------------------TD回调函数、相关变量结束----------------------------------------------
#回调类型
TD_EMPTY                    = 8000 #登录成功
TD_LOGIN_SCUESS             = 8001 #登录成功
TD_LOGIN_DENIED             = 8002 #登录被拒绝
TD_LOGIN_ERRORPASSWORD      = 8003 #密码错误
TD_LOGINOUT_SCUESS          = 8004 #登出成功
TD_LOGINOUT_DENIED          = 8005 #登出被拒绝
TD_NETCONNECT_SCUESS        = 8006 #连接成功
TD_NETCONNECT_BREAK         = 8007 #断开连接
TD_NETCONNECT_FAILER        = 8008 #连接失败
#TD_SUBCRIBE_SCUESS         = 8009 #订阅成功
#TD_UNSUBCRIBE_SCUESS       = 8010 #取消订阅成功 
#TD_NEWTICK                 = 8011 #新Tick到来 
TD_ERROR                    = 8011 #错误应答 
TD_ORDER_INFO               = 8012 #订单回报
TD_TRADE_INFO               = 8013 #成交回报
TD_INSTRUMENT_STATUS        = 8014 #合约交易状态

TD_BYFUTURE_BANKTOFUTURE    = 8015 #期货发起银行资金转期货通知
TD_BYFUTURE_FUTURETOBANK    = 8016 #期货发起期货资金转银行通知

TD_SETTLEMENTINFOCONFIRM    = 8017 #结算单确认回调
TD_MAXORDERVOLUME         = 8014 #最大允许报单数量回调

def TD_OnEmptyCmd():
    #回调指令缓冲区已为空（因为短时间获得多个指令，时间间隔态度，在下面的for i in range(market.GetUnGetCmdSize()):循环执行了多次已经完成了）
    print "---------------TD_OnEmptyCmd---------------"
    
def TD_OnUserLogin():
    #登录成功
    print "---------------TD_OnUserLogin---------------"   
    data = cast(trader.GetCmdContent_LoginScuess(), POINTER(QL_CThostFtdcRspUserLoginField))
    print "TradingDay %s"%(str(data[0].TradingDay))              #交易日
    print "LoginTime %s"%(str(data[0].LoginTime))                #登录成功时间
    print "BrokerID %s"%(str(data[0].BrokerID))                  #经纪公司代码
    print "UserID %s"%(str(data[0].UserID))                      #用户代码        
    print "SystemName %s"%(str(data[0].SystemName))              #交易系统名称
    print "FrontID %s"%(str(data[0].FrontID))                    #前置编号     
    print "SessionID %s"%(str(data[0].SessionID))                #会话编号
    print "MaxOrderRef %s"%(str(data[0].MaxOrderRef))            #最大报单引用
    print "SHFETime %s"%(str(data[0].SHFETime))                  #上期所时间
    print "DCETime %s"%(str(data[0].DCETime))                    #大商所时间
    print "CZCETime %s"%(str(data[0].CZCETime))                  #郑商所时间
    print "FFEXTime %s"%(str(data[0].FFEXTime))                  #中金所时间       
    print "INETime %s"%(str(data[0].INETime))                    #能源中心时间
    
def TD_OnUserLoginDenied():
    #登录被拒绝
    print "---------------TD_OnUserLoginDenied---------------"       
    
def TD_OnUserLoginErrPassword():
    #登录密码错误
    print "---------------TD_OnUserLoginErrPassword---------------"       
    
def TD_OnUserLogout():
    #登出成功
    print "---------------TD_OnUserLogout---------------"    

def TD_OnFrontConnected():
    #连接成功
    print "---------------TD_OnFrontConnected---------------"       
    
def TD_OnFrontDisconnected():
    #断开连接
    print "---------------TD_OnFrontDisconnected---------------"    
    
def TD_OnFrontConnectedFailer():
    #连接失败
    print "---------------TD_OnFrontConnectedFailer---------------"
    
def TD_OnError():
    #错误信息回报
    print "---------------TD_OnRspError---------------"   
    data = cast(trader.GetCmdContent_Error(), POINTER(QL_CThostFtdcRspInfoField))
    print "ErrorID %s"%(str(data[0].ErrorID))              #错误代码
    print "ErrorMsg %s"%(str(data[0].ErrorMsg))            #错误信息

def TD_OnOrder():
    #订单回报
    print "---------------TD_OnRspOrder---------------"
    data = cast(trader.GetCmdContent_Order(), POINTER(QL_CThostFtdcOrderField))    
    print "BrokerID %s"%(str(data[0].BrokerID))            #经纪公司代码
    print "InvestorID %s"%(str(data[0].InvestorID))
    print "InstrumentID %s"%(str(data[0].InstrumentID))
    print "OrderRef %s"%(str(data[0].OrderRef))    
    print "UserID %s"%(str(data[0].UserID))
    print "OrderPriceType %s"%(str(data[0].OrderPriceType))
    print "Direction %s"%(str(data[0].Direction))
    print "CombOffsetFlag %s"%(str(data[0].CombOffsetFlag))    
    print "CombHedgeFlag %s"%(str(data[0].CombHedgeFlag))
    print "LimitPrice %s"%(str(data[0].LimitPrice))    
    print "VolumeTotalOriginal %s"%(str(data[0].VolumeTotalOriginal))
    print "TimeCondition %s"%(str(data[0].TimeCondition))    
    print "GTDDate %s"%(str(data[0].GTDDate))        
    print "MinVolume %s"%(str(data[0].MinVolume))    
    print "ContingentCondition %s"%(str(data[0].ContingentCondition))        
    print "StopPrice %s"%(str(data[0].StopPrice))    
    print "ForceCloseReason %s"%(str(data[0].ForceCloseReason))
    print "IsAutoSuspend %s"%(str(data[0].IsAutoSuspend))    
    print "BusinessUnit %s"%(str(data[0].BusinessUnit))
    print "RequestID %s"%(str(data[0].RequestID))    
    print "OrderLocalID %s"%(str(data[0].OrderLocalID))
    print "ExchangeID %s"%(str(data[0].ExchangeID))    
    print "ParticipantID %s"%(str(data[0].ParticipantID))
    print "ClientID %s"%(str(data[0].ClientID))    
    print "ExchangeInstID %s"%(str(data[0].ExchangeInstID))
    print "TraderID %s"%(str(data[0].TraderID))    
    print "InstallID %s"%(str(data[0].InstallID))
    print "OrderSubmitStatus %s"%(str(data[0].OrderSubmitStatus))    
    print "NotifySequence %s"%(str(data[0].NotifySequence))  
    print "TradingDay %s"%(str(data[0].TradingDay))    
    print "SettlementID %s"%(str(data[0].SettlementID))      
    print "OrderSysID %s"%(str(data[0].OrderSysID))    
    print "OrderSource %s"%(str(data[0].OrderSource))          
    print "OrderStatus %s"%(str(data[0].OrderStatus))
    print "OrderType %s"%(str(data[0].OrderType))    
    print "VolumeTraded %s"%(str(data[0].VolumeTraded))          
    print "VolumeTotal %s"%(str(data[0].VolumeTotal))
    
def TD_OnInstrumentStatus():
    #合约交易状态通知
    print "---------------TD_OnInstrumentStatus---------------"
    data = cast(trader.GetCmdContent_Order(), POINTER(QL_CThostFtdcInstrumentStatusField))    
    print "ExchangeID %s"%(str(data[0].ExchangeID))                #交易所代码
    print "ExchangeInstID %s"%(str(data[0].ExchangeInstID))        #合约在交易所的代码
    print "SettlementGroupID %s"%(str(data[0].SettlementGroupID))  #结算组代码
    print "InstrumentID %s"%(str(data[0].InstrumentID))            #合约代码
    print "InstrumentStatus %s"%(str(data[0].InstrumentStatus))    #合约交易状态
    print "TradingSegmentSN %s"%(str(data[0].TradingSegmentSN))    #交易阶段编号
    print "EnterTime %s"%(str(data[0].EnterTime))                  #进入本状态时间
    print "EnterReason %s"%(str(data[0].EnterReason))              #进入本状态原因
    
def TD_OnTrade():
    #订单回报
    print "---------------TD_OnTrade---------------"
    data = cast(trader.GetCmdContent_Trade(), POINTER(QL_CThostFtdcTradeField))    
    print "BrokerID %s"%(str(data[0].BrokerID))            #经纪公司代码
    print "InvestorID %s"%(str(data[0].InvestorID))
    print "InstrumentID %s"%(str(data[0].InstrumentID))
    print "OrderRef %s"%(str(data[0].OrderRef))    
    print "UserID %s"%(str(data[0].UserID))
    print "ExchangeID %s"%(str(data[0].ExchangeID))
    print "TradeID %s"%(str(data[0].TradeID))
    print "Direction %s"%(str(data[0].Direction))    
    print "OrderSysID %s"%(str(data[0].OrderSysID))   
    print "ParticipantID %s"%(str(data[0].ParticipantID))    
    print "ClientID %s"%(str(data[0].ClientID))        
    print "TradingRole %s"%(str(data[0].TradingRole))    
    print "ExchangeInstID %s"%(str(data[0].ExchangeInstID))
    print "OffsetFlag %s"%(str(data[0].OffsetFlag))    
    print "HedgeFlag %s"%(str(data[0].HedgeFlag))
    print "Price %0.02f"%(str(data[0].Price))    
    print "Volume %0.02f"%(str(data[0].Volume))
    print "TradeDate %s"%(str(data[0].TradeDate))    
    print "TradeTime %s"%(str(data[0].TradeTime))
    print "TradeType %s"%(str(data[0].TradeType))    
    print "PriceSource %s"%(str(data[0].PriceSource))
    print "TraderID %s"%(str(data[0].TraderID))  
    print "OrderLocalID %s"%(str(data[0].OrderLocalID))    
    print "ClearingPartID %s"%(str(data[0].ClearingPartID))      
    print "BusinessUnit %s"%(str(data[0].BusinessUnit))
    print "SequenceNo %d"%(str(data[0].SequenceNo))          
    print "TradingDay %s"%(str(data[0].TradingDay))
    print "SettlementID %d"%(str(data[0].SettlementID))    
    print "BrokerOrderSeq %d"%(str(data[0].BrokerOrderSeq))          
    print "TradeSource %s"%(str(data[0].TradeSource))
        
def TD_OnSettlementInfoConfirm():
    #结算确认回报
    print "---------------TD_OnRspSettlementInfoConfirm---------------"   
    data = cast(trader.GetCmdContent_Settlement(), POINTER(QL_CThostFtdcSettlementInfoConfirmField))
    print "BrokerID %s"%(str(data[0].BrokerID))              #经纪公司代码
    print "InvestorID %s"%(str(data[0].InvestorID))          #投资者代码
    print "ConfirmDate %s"%(str(data[0].ConfirmDate))        #确认日期
    print "ConfirmTime %s"%(str(data[0].ConfirmTime))        #确认时间
    
def TD_OnMaxOrderVolume():
    #查询最大报单数量响应
    print "---------------TD_OnRspSettlementInfoConfirm---------------"   
    data = cast(trader.GetCmdContent_QueryMaxOrderVolume(), POINTER(QL_CThostFtdcQueryMaxOrderVolumeField))
    print "BrokerID %s"%(str(data[0].BrokerID))              #经纪公司代码
    print "InvestorID %s"%(str(data[0].InvestorID))          #投资者代码
    print "InstrumentID %s"%(str(data[0].InstrumentID))      #合约代码
    print "Direction %s"%(str(data[0].Direction))            #买卖方向      
    print "OffsetFlag %s"%(str(data[0].OffsetFlag))          #开平标志
    print "HedgeFlag %s"%(str(data[0].HedgeFlag))            #投机套保标志
    print "MaxVolume %s"%(str(data[0].MaxVolume))            #最大允许报单数量
    
    
def TD_OnRtnFromBankToFutureByFuture():
    #期货发起银行资金转期货通知
    print "---------------TD_OnRtnFromBankToFutureByFuture---------------"
    data = cast(trader.GetCmdContent_BankToFutureByFuture(), POINTER(QL_CThostFtdcRspTransferField))
    print "TradeCode %s"%(str(data[0].TradeCode))                    #业务功能码
    print "BankID %s"%(str(data[0].BankID))                          #银行代码
    print "BankBranchID %s"%(str(data[0].BankBranchID))              #银行分支机构代码
    print "BrokerID %s"%(str(data[0].BrokerID))                      #期商代码
    print "BrokerBranchID %s"%(str(data[0].BrokerBranchID))          #期商分支机构代码    
    print "TradeDate %s"%(str(data[0].TradeDate))                    #交易日期      
    print "TradeTime %s"%(str(data[0].TradeTime))                    #交易时间
    print "BankSerial %s"%(str(data[0].BankSerial))                  #银行流水号
    print "TradingDay %s"%(str(data[0].TradingDay))                  #交易系统日期
    print "PlateSerial %d"%(str(data[0].PlateSerial))                #银期平台消息流水号
    print "LastFragment %s"%(str(data[0].LastFragment))              #最后分片标志
    print "SessionID %d"%(str(data[0].SessionID))                    #会话号
    print "CustomerName %s"%(str(data[0].CustomerName))              #客户姓名      
    print "IdCardType %s"%(str(data[0].IdCardType))                  #证件类型
    print "IdentifiedCardNo %s"%(str(data[0].IdentifiedCardNo))      #证件号码
    print "CustType %s"%(str(data[0].CustType))                      #客户类型
    print "BankAccount %s"%(str(data[0].BankAccount))                #银行帐号
    print "BankPassWord %s"%(str(data[0].BankPassWord))              #银行密码
    print "AccountID %s"%(str(data[0].AccountID))                    #投资者帐号
    print "Password %s"%(str(data[0].Password))                      #期货密码      
    print "InstallID %d"%(str(data[0].InstallID))                    #安装编号
    print "FutureSerial %d"%(str(data[0].FutureSerial))              #期货公司流水号
    print "UserID %s"%(str(data[0].UserID))                          #用户标识
    print "VerifyCertNoFlag %s"%(str(data[0].VerifyCertNoFlag))      #验证客户证件号码标志
    print "CurrencyID %s"%(str(data[0].CurrencyID))                  #币种代码
    print "TradeAmount %0.02f"%(str(data[0].TradeAmount))            #转帐金额
    print "FutureFetchAmount %0.02f"%(str(data[0].FutureFetchAmount))#期货可取金额      
    print "FeePayFlag %s"%(str(data[0].FeePayFlag))                  #费用支付标志
    print "CustFee %0.02f"%(str(data[0].CustFee))                    #应收客户费用
    print "BrokerFee %0.02f"%(str(data[0].BrokerFee))                #应收期货公司费用
    print "Message %s"%(str(data[0].Message))                        #发送方给接收方的消息
    print "Digest %s"%(str(data[0].Digest))                          #摘要
    print "BankAccType %s"%(str(data[0].BankAccType))                #银行帐号类型
    print "DeviceID %s"%(str(data[0].DeviceID))                      #渠道标志      
    print "BankSecuAccType %s"%(str(data[0].BankSecuAccType))        #期货单位帐号类型
    print "BrokerIDByBank %s"%(str(data[0].BrokerIDByBank))          #期货公司银行编码
    print "BankSecuAcc %s"%(str(data[0].BankSecuAcc))                #期货单位帐号
    print "BankPwdFlag %s"%(str(data[0].BankPwdFlag))                #银行密码标志
    print "SecuPwdFlag %s"%(str(data[0].SecuPwdFlag))                #期货资金密码核对标志
    print "OperNo %s"%(str(data[0].OperNo))                          #交易柜员
    print "RequestID %d"%(str(data[0].RequestID))                    #请求编号      
    print "TID %d"%(str(data[0].TID))                                #交易ID
    print "TransferStatus %s"%(str(data[0].TransferStatus))          #转账交易状态
    print "ErrorID %d"%(str(data[0].ErrorID))                        #错误代码
    print "ErrorMsg %s"%(str(data[0].ErrorMsg))                      #错误信息      
    print "LongCustomerName %s"%(str(data[0].LongCustomerName))      #长客户姓名
   
    
def TD_OnRtnFromFutureToBankByFuture():
    #期货发起期货资金转银行通知
    print "---------------TD_OnRtnFromFutureToBankByFuture---------------"
    data = cast(trader.GetCmdContent_FutureToBankByFuture(), POINTER(QL_CThostFtdcRspTransferField))
    print "TradeCode %s"%(str(data[0].TradeCode))                    #业务功能码
    print "BankID %s"%(str(data[0].BankID))                          #银行代码
    print "BankBranchID %s"%(str(data[0].BankBranchID))              #银行分支机构代码
    print "BrokerID %s"%(str(data[0].BrokerID))                      #期商代码
    print "BrokerBranchID %s"%(str(data[0].BrokerBranchID))          #期商分支机构代码    
    print "TradeDate %s"%(str(data[0].TradeDate))                    #交易日期      
    print "TradeTime %s"%(str(data[0].TradeTime))                    #交易时间
    print "BankSerial %s"%(str(data[0].BankSerial))                  #银行流水号
    print "TradingDay %s"%(str(data[0].TradingDay))                  #交易系统日期
    print "PlateSerial %d"%(str(data[0].PlateSerial))                #银期平台消息流水号
    print "LastFragment %s"%(str(data[0].LastFragment))              #最后分片标志
    print "SessionID %d"%(str(data[0].SessionID))                    #会话号
    print "CustomerName %s"%(str(data[0].CustomerName))              #客户姓名      
    print "IdCardType %s"%(str(data[0].IdCardType))                  #证件类型
    print "IdentifiedCardNo %s"%(str(data[0].IdentifiedCardNo))      #证件号码
    print "CustType %s"%(str(data[0].CustType))                      #客户类型
    print "BankAccount %s"%(str(data[0].BankAccount))                #银行帐号
    print "BankPassWord %s"%(str(data[0].BankPassWord))              #银行密码
    print "AccountID %s"%(str(data[0].AccountID))                    #投资者帐号
    print "Password %s"%(str(data[0].Password))                      #期货密码      
    print "InstallID %d"%(str(data[0].InstallID))                    #安装编号
    print "FutureSerial %d"%(str(data[0].FutureSerial))              #期货公司流水号
    print "UserID %s"%(str(data[0].UserID))                          #用户标识
    print "VerifyCertNoFlag %s"%(str(data[0].VerifyCertNoFlag))      #验证客户证件号码标志
    print "CurrencyID %s"%(str(data[0].CurrencyID))                  #币种代码
    print "TradeAmount %0.02f"%(str(data[0].TradeAmount))            #转帐金额
    print "FutureFetchAmount %0.02f"%(str(data[0].FutureFetchAmount))#期货可取金额      
    print "FeePayFlag %s"%(str(data[0].FeePayFlag))                  #费用支付标志
    print "CustFee %0.02f"%(str(data[0].CustFee))                    #应收客户费用
    print "BrokerFee %0.02f"%(str(data[0].BrokerFee))                #应收期货公司费用
    print "Message %s"%(str(data[0].Message))                        #发送方给接收方的消息
    print "Digest %s"%(str(data[0].Digest))                          #摘要
    print "BankAccType %s"%(str(data[0].BankAccType))                #银行帐号类型
    print "DeviceID %s"%(str(data[0].DeviceID))                      #渠道标志      
    print "BankSecuAccType %s"%(str(data[0].BankSecuAccType))        #期货单位帐号类型
    print "BrokerIDByBank %s"%(str(data[0].BrokerIDByBank))          #期货公司银行编码
    print "BankSecuAcc %s"%(str(data[0].BankSecuAcc))                #期货单位帐号
    print "BankPwdFlag %s"%(str(data[0].BankPwdFlag))                #银行密码标志
    print "SecuPwdFlag %s"%(str(data[0].SecuPwdFlag))                #期货资金密码核对标志
    print "OperNo %s"%(str(data[0].OperNo))                          #交易柜员
    print "RequestID %d"%(str(data[0].RequestID))                    #请求编号      
    print "TID %d"%(str(data[0].TID))                                #交易ID
    print "TransferStatus %s"%(str(data[0].TransferStatus))          #转账交易状态
    print "ErrorID %d"%(str(data[0].ErrorID))                        #错误代码
    print "ErrorMsg %s"%(str(data[0].ErrorMsg))                      #错误信息      
    print "LongCustomerName %s"%(str(data[0].LongCustomerName))      #长客户姓名
      
tddict={
          TD_EMPTY:TD_OnEmptyCmd,
          TD_LOGIN_SCUESS:TD_OnUserLogin,
          TD_LOGIN_DENIED:TD_OnUserLoginDenied,
          TD_LOGIN_ERRORPASSWORD:TD_OnUserLoginErrPassword,
          TD_LOGINOUT_SCUESS:TD_OnUserLogout,
          TD_NETCONNECT_SCUESS:TD_OnFrontConnected,
          TD_NETCONNECT_BREAK:TD_OnFrontDisconnected,
          TD_NETCONNECT_FAILER:TD_OnFrontConnectedFailer,
          TD_ERROR:TD_OnError,
          TD_ORDER_INFO:TD_OnOrder,
          TD_TRADE_INFO:TD_OnTrade,
          TD_INSTRUMENT_STATUS:TD_OnInstrumentStatus,
          TD_BYFUTURE_BANKTOFUTURE:TD_OnRtnFromBankToFutureByFuture,
          TD_BYFUTURE_FUTURETOBANK:TD_OnRtnFromFutureToBankByFuture,          
          TD_SETTLEMENTINFOCONFIRM:TD_OnSettlementInfoConfirm,
          TD_MAXORDERVOLUME:TD_OnMaxOrderVolume
        }

#------------------------------------------TD回调函数、相关变量结束----------------------------------------------

# main()为程序入口函数，所有的行情、交易订阅、指标调用、下单的逻辑均写在此函数内执行
def main():
    print(u"官方QQ群 5172183 \n");
    retLogin = trader.Login()  #调用交易接口元素，通过 “ 接口变量.元素（接口类内部定义的方法或变量） ” 形式调用
    # Login()，不需要参数，Login读取QuickLibTD.ini的配置信息，并登录
    # 返回0， 表示登录成功，
    # 返回1， FutureTDAccount.ini错误
    # 返回2， 登录超时
    print (u'login:%d '%retLogin)   
    #if retLogin==0:
    #    print u'Python:登陆交易成功'
    #else:
    #    print u'Python:登陆交易失败'
    
    #持仓数据在后台更新时，参数True为显示持仓状态，False为不显示持仓状态（仅对控制台有效）   
    trader.SetShowPosition(True)
    #注意simnow模拟盘的交易服务器不稳定，经常会出现查询不到的情况。实盘账户绑定的交易服务器无此问题。
    #trader.ReqQryContractBank()
    while(1):  #死循环，反复执行
        #请求查询签约银行
  
        
        print(u"Wait for a New Cmd(TD)\n");
        #消息驱动，包括了各种回调，在没有消息到来时，一直处于阻塞状态，不占用CPU。当回调函数内有大量耗时的CPU计算时，建议回调函数内采用多进程或进程池来进行计算处理，以免阻塞消息驱动线程。
        tddict[trader.OnCmd()]()
        print(u"Get A New cmd(TD)\n");
        #OrderRef2 = trader.InsertOrder('ag1706', QL_D_Buy, QL_OF_Open, QL_OPT_LimitPrice, 22450, 1)    
        #如果值为-999999999（初始值），则表示尚未获得数据
        

        #ReqFromBankToFutureByFuture(BankID, BrokerBranchID,BankAccount,BankPassWord,AccountID, TradeAmount,nRequestID)
        #trader.ReqFromBankToFutureByFuture("0000", "0000",BankAccount,BankPassWord,"035312", 100,1)
        
        print (u'(1)动态权益：%0.02f'%trader.QryBalance(True))
        print (u'(2)静态权益：%0.02f'%trader.QryBalance(False))      
        print (u'(3)可用资金：%0.02f'%trader.QryAvailable())
        print (u'(4)zn1701今日空单持仓：%d'%trader.QryPosition('rb1701',QL_POSITION_Sell_Today))   
        print (u'(5)zn1701今日多单持仓：%d'%trader.QryPosition('rb1701',QL_POSITION_Buy_Today))   
        print (u'(6)zn1701非今日空单持仓：%d'%trader.QryPosition('rb1701',QL_POSITION_Sell_History))   
        print (u'(7)zn1701非今日多单持仓：%d'%trader.QryPosition('rb1701',QL_POSITION_Buy_History))   
        print (u'(8)zn1701空单持仓总计：%d'%trader.QryPosition('rb1701',QL_POSITION_Sell_All))   
        print (u'(9)zn1701多单持仓总计：%d'%trader.QryPosition('rb1701',QL_POSITION_Buy_All))   
        
        #print '--------------------------------------------------------'
        time.sleep(3)  #sleep1秒，防止死循环导致CPU占有率过高，1即可，不宜过大，若过大会导致程序进程长时间无响应，丢失行情数据

if __name__ == '__main__':
    main()
    

    
 
    
    
    