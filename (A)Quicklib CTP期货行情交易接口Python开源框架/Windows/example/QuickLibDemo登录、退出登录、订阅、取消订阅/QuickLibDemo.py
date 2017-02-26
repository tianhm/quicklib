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

#导入CTP行情库
from CTPMarket import *
#导入时间库
import time, datetime
market = CTPMarket()   #行情接口类赋值给变量
 

#限制交易时间
today = datetime.date.today()
gStart1 = datetime.datetime(today.year, today.month, today.day, 9, 30, 0) #开盘时间1
gEnd1 = datetime.datetime(today.year, today.month, today.day, 11, 30, 0)  #收盘时间1
gStart2 = datetime.datetime(today.year, today.month, today.day, 13, 0, 0) #开盘时间2
gEnd2 = datetime.datetime(today.year, today.month, today.day, 15, 0, 0)   #收盘时间2
gExitTime = datetime.datetime(today.year, today.month, today.day, 15, 1, 0) #退出运行的时间

def IsStockTrade():
    now = datetime.datetime.now()
    if ((gStart1 < now and now < gEnd1) or
        (gStart2 < now and now < gEnd2)):
            return True
    else:
        return False
    
#------------------------------------------MD回调函数、相关变量开始----------------------------------------------
num=0    

#回调类型
MD_EMPTY                    = 8000 #无消息
MD_LOGIN_SCUESS             = 8001 #登录成功
MD_LOGIN_DENIED             = 8002 #登录被拒绝
#MD_LOGIN_ERRORPASSWORD     = 8003 #密码错误(行情没有密码错误)
MD_LOGINOUT_SCUESS          = 8004 #登出成功
MD_NETCONNECT_SCUESS        = 8005 #连接成功
MD_NETCONNECT_BREAK         = 8006 #断开连接
MD_NETCONNECT_FAILER        = 8007 #连接失败
MD_SUBCRIBE_SCUESS          = 8008 #订阅成功
MD_UNSUBCRIBE_SCUESS        = 8009 #取消订阅成功 
MD_NEWTICK                  = 8010 #新Tick到来 
MD_SYSTEM_ERROR             = 8011 #错误应答 
MD_QRY_FORQUOTE             = 8012 #询价通知 

def MD_OnEmptyCmd():
    #回调指令缓冲区已为空（因为短时间获得多个指令，时间间隔态度，在下面的for i in range(market.GetUnGetCmdSize()):循环执行了多次已经完成了）
    print "---------------MD_OnEmptyCmd---------------" 
def MD_OnUserLogin():
    #登录成功
    print "---------------MD_OnUserLogin---------------" 
    data = cast(market.GetCmdContent_LoginScuess(), POINTER(QL_CThostFtdcRspUserLoginField))
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
def MD_OnUserLoginDenied():
    #登录被拒绝
    print "---------------MD_OnUserLoginDenied---------------"         
def MD_OnUserLogout():
    #登出成功
    print "---------------MD_OnUserLogout---------------"
    data = cast(market.GetCmdContent_LoginOut(), POINTER(QL_CThostFtdcRspUserLoginField))
    print "BrokerID %s"%(str(data[0].BrokerID))            #期货公司brokeid
    print "UserID %s"%(str(data[0].UserID))                #账户    
def MD_OnFrontConnected():
    #与行情服务器连接成功
    #当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    print "---------------MD_OnFrontConnected---------------"    
def MD_OnFrontDisconnected():
    #与行情服务器断开连接
    #当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    print "---------------MD_OnFrontDisconnected---------------"
def MD_OnFrontConnectedFailer():
    #连接失败
    print "---------------MD_OnFrontConnectedFailer---------------"  
def MD_OnSubMarketData():
    #订阅成功
    print "---------------MD_OnSubMarketData---------------"
    data = cast(market.GetCmdContent_SubMarketData(), POINTER(QL_Instrument))
    print "InstrumentID %s"%(str(data[0].InstrumentID))              #合约代码  
def MD_OnUnSubMarketData():
    #取消订阅行情成功
    print "---------------MD_OnUnSubMarketData---------------"
    data = cast(market.GetCmdContent_UnSubMarketData(), POINTER(QL_Instrument))
    print "InstrumentID %s"%(str(data[0].InstrumentID))              #合约代码  
def MD_OnTick():
    #新的一笔Tick数据驱动
    #print "---------------MD_OnTick---------------"       
    global num
    num=num+1
    #取得新TICK的合约代码
    Instrument =market.GetCmdContent_Tick() 
    #print "Instrument %s"%Instrument
    #打印该合约数据, 可增加交易策略逻辑计算，计算进程放入其它线程或进程中，以免耗时计算阻塞行情接收和其它回调
    print u"(%d)%s %s [%0.02f][%0.00f]"%(num,Instrument,market.InstrumentID(Instrument), market.LastPrice(Instrument), market.Volume(Instrument))
def MD_OnError():
    #错误信息回报
    print "---------------MD_OnRspError---------------"   
    data = cast(market.GetCmdContent_Error(), POINTER(QL_CThostFtdcRspInfoField))
    print "ErrorID %s"%(str(data[0].ErrorID))              #错误代码
    print "ErrorMsg %s"%(str(data[0].ErrorMsg))            #错误信息    
def MD_OnForQuote():
    #询价通知
    print "---------------MD_OnForQuote---------------"   
    data = cast(market.GetCmdContent_Forquote(), POINTER(QL_CThostFtdcForQuoteRspField))
    print "TradingDay %s"%(str(data[0].TradingDay))                #交易日
    print "InstrumentID %s"%(str(data[0].InstrumentID))            #合约代码        
    print "ForQuoteSysID %s"%(str(data[0].ForQuoteSysID))          #询价编号
    print "ForQuoteTime %s"%(str(data[0].ForQuoteTime))            #询价时间            
    print "ActionDay %s"%(str(data[0].ActionDay))                  #业务日期
    print "ExchangeID %s"%(str(data[0].ExchangeID))                #交易所代码    
mddict={
          MD_EMPTY:MD_OnEmptyCmd,
          MD_LOGIN_SCUESS:MD_OnUserLogin,
          MD_LOGIN_DENIED:MD_OnUserLoginDenied,
          MD_LOGINOUT_SCUESS:MD_OnUserLogout,
          MD_NETCONNECT_SCUESS:MD_OnFrontConnected,
          MD_NETCONNECT_BREAK:MD_OnFrontDisconnected,
          MD_NETCONNECT_FAILER:MD_OnFrontConnectedFailer,
          MD_SUBCRIBE_SCUESS:MD_OnSubMarketData,
          MD_UNSUBCRIBE_SCUESS:MD_OnUnSubMarketData,
          MD_NEWTICK:MD_OnTick,
          MD_SYSTEM_ERROR:MD_OnError,
          MD_QRY_FORQUOTE:MD_OnForQuote
        }
#------------------------------------------MD回调函数、相关变量结束----------------------------------------------
# main()为程序入口函数，所有的行情、交易订阅、指标调用、下单的逻辑均写在此函数内执行
def main():
    market.SetTitle(u"程序标题")
    print(u"官方QQ群 5172183 \n");
    #os.system("QucikLib CTP接口期货Tick数据采集器，保存csv格式 QQ群 5172183")    
 
    # Login()，不需要参数，Login读取QuickLibTD.ini的配置信息，并登录
    # 返回0， 表示登录成功，
    # 返回1， FutureTDAccount.ini错误
    # 返回2， 登录超时
 

    #设置拒绝接收行情服务器数据的时间，有时候（特别是模拟盘）在早晨6-8点会发送前一天的行情数据，若不拒收的话，会导致历史数据错误，本方法最多可以设置4个时间段进行拒收数据
    market.SetRejectdataTime(0.0400, 0.0840, 0.1530, 0.2030, NULL, NULL, NULL, NULL);
    # 一共9个订阅函数：
    # Subcribe(无周期参数，只接受Tick数据，而不生成和保存周期价格)
    # Subcribe1(1个周期参数)
    # Subcribe2(2个周期参数)
    # Subcribe3(3个周期参数)
    # Subcribe4(4个周期参数)
    # Subcribe5(5个周期参数)
    # Subcribe6(6个周期参数)
    # Subcribe7(7个周期参数)
    # Subcribe8(8个周期参数)
    # 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
    # 调用以上8个订阅函数(Subcribe,Subcribe1,Subcribe2,Subcribe3,Subcribe4,Subcribe5,Subcribe6,Subcribe7)后，可以用AddPeriod函数添加周期参数
    # 订阅函数实参传递时,对周期参数请避免重复,在周期参数重复传参时，库会自动做检查会当做1次处理。故Subcribe8在不重复传参的情况下，已经包含了所有周期，故无需使用AddPeriod添加周期。
    # 尽量避免使用不到的周期参数，可以节省内存和CPU占用
    # 周期参数：
    # QL_M1    1分钟周期
    # QL_M3    3分钟周期
    # QL_M5    5分钟周期
    # QL_M10   10分钟周期 
    # QL_M15   15分钟周期
    # QL_M30   30分钟周期
    # QL_M60   60分钟周期
    # QL_M120  120分钟周期
    # QL_D1    日线周期
    # QL_ALL   包括了所有周期(QL_M1,QL_M3,QL_M5,QL_M10,QL_M15,QL_M30,QL_M60,QL_M120,QL_D1)  

    #Subcribe系列函数最后一个参数，true表示打印tick数据，false表示不打印
    market.Subcribe('zn1701')                #订阅品种zn1610，接收Tick数据,不根据Tick生成其他周期价格数据,但可根据AddPeriod函数添加周期价格数据的设置
    market.Subcribe('zn1705')              
    # main()函数内的以上部分代码只执行一次，以下while(1)循环内的代码，会一直循环执行，可在这个循环内需增加策略判断，达到下单条件即可下单
 
 
    #判断当前时间是否在交易时间内，如果在返回真，则开始执行
    if (IsStockTrade()):
            print(u"Wait for a New Cmd(MD)\n");
            #判断是否有新Tick数据，while循环不需要Sleep,当没有新Tick时，会处在阻塞状态
            mddict[market.OnCmd()]()
            print(u"Get A New cmd(MD)\n");     
           #直接指定合约名称打印数据
           #print market.LastPrice('zn1701')     #打印该品种在行情接口的变量LastPrice (最新价)
           #print market.BidPrice1('zn1705')     #打印该品种在行情接口的变量BidPrice           
  
           #time.sleep(3)  #系统休眠
    else:
            print u"没到开盘时间"
    
    #取消订阅
    market.UnSubscribeMarketData('zn1701')
    #退出登录
    market.Logout()
 
    time.sleep(8)  #系统休眠0.1秒
    #第一次是自动登录，退出登录后，如需再登陆，需添加以下登陆代码
    retLogin = market.Login()  #调用交易接口元素，通过 “ 接口变量.元素（接口类内部定义的方法或变量） ” 形式调用
    # Login()，不需要参数，Login读取QuickLibTD.ini的配置信息，并登录
    # 返回0， 表示登录成功，
    # 返回1， FutureTDAccount.ini错误
    # 返回2， 登录超时
    #print ('login: ', retLogin)   
    if retLogin==0:
        print u'登陆行情服务器成功'
    else:
        print u'登陆行情服务器失败' 
    #重新订阅行情
    market.Subcribe('ni1701')
    market.Subcribe('ni1705')
    time.sleep(3)  #系统休眠0.1秒
    while(1):  #死循环，反复执行
        print(u"Wait for a New Cmd(MD)\n");
        #判断是否有新Tick数据，while循环不需要Sleep,当没有新Tick时，会处在阻塞状态
        mddict[market.OnCmd()]()
        print(u"Get A New cmd(MD)\n");                    
                     
                     
 
if __name__ == '__main__':
    main()
    

    
 
    
    
    