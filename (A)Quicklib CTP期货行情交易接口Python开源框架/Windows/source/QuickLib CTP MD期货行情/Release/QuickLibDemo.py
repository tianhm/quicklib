#1.本文件及调用的Python文件为范例代码
#2.本文件及调用的库文件Quicklib CTP期货行情库和交易库遵循 开源协议GPL v3
#Quciklib Python框架和工具遵循GPL v3协议包括：
#（1）Quicklib CTP   期货行情库
#（2）Quicklib CTP   期货交易库
#（3）Quicklib CTP2  A股行情库
#Quciklib Python框架和工具暂不遵循开源协议包括：
#（4）Quicklib 监控器库（预警、监控、交易信号数据复制、跟单）（可免费试用）
#原始作者：QQ 147423661 林(王登高)
#对Quciklib开源库做出贡献的，并得到原始作者肯定的，将公布在http://www.quciklib.cn网站上
#官方网站：http://www.quicklib.cn
#官方QQ群：5172183(1群)、25884087(2群)

#导入CTP行情库
from CTPMarket import *
#导入多进程库
#import multiprocessing
import multiprocessing
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
    

def StrategyProcess(msg,price): #(Instrument,lastprice):
    #print u"********************** [%s]lastprice:%0.02f\n"%( Instrument,lastprice)
    print "StrategyProcess Instrument:", msg
    #print(name,price) 
    #print u"******[%s]\n"%msg
    return "done" + msg

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
MD_QRY_FORQUOTE             = 8011 #询价通知 

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
    market.SetTitle(u"程序标题%s"% market.GetApiVersion())
    #获得并打印对应的CTP API 版本号
    print (u"CTP API版本%s"%market.GetApiVersion())
    print (u"交易日%s"%market.GetTradingDay())
    print(u"官方QQ群 5172183 \n")
    
    #除了从配置文件读取注册服务器地址外，还可用RegisterFront添加注册多个行情服务器IP地址。稍后给出不读配置文件，只使用RegisterFront注册行情服务器地址的例子
    if False:
        #已从配置文件读取3个服务器地址，这里可以不添加注册了
        market.RegisterFront(u"tcp://180.168.146.187:10031") #添加注册行情服务器地址1
        market.RegisterFront(u"tcp://180.168.146.187:10031") #添加注册行情服务器地址2
        market.RegisterFront(u"tcp://180.168.146.187:10031") #添加注册行情服务器地址3
    
    #os.system("QucikLib CTP接口期货Tick数据采集器，保存csv格式 QQ群 5172183")    
    #从配置文件Instrument.ini  读取订阅的合约，每行写一个要订阅行情的合约，用调用ReadInstrument()的方式就无需通过调用Subcribe系列函数方式来订阅合约了，编译成exe后，也方便通过更改配置文件来更改合约
         
    #设置拒绝接收行情服务器数据的时间，有时候（特别是模拟盘）在早晨6-8点会发送前一天的行情数据，若不拒收的话，会导致历史数据错误，本方法最多可以设置4个时间段进行拒收数据
    #market.SetRejectdataTime(0.0400, 0.0840, 0.1530, 0.2030, NULL, NULL, NULL, NULL);    
    #OrderRef1 = trader.InsertOrder('zn1610', YT_D_Buy, YT_OF_Open, YT_OPT_LimitPrice, market.LastPrice('zn1610')+10, 1)
    #OrderRef1 = trader.InsertOrder('zn1610', YT_D_Buy, YT_OF_Open, YT_OPT_LimitPrice, market.LastPrice('zn1610')+10, 1)
    #读取合约订阅的配置文件
    
    if True:
        #订阅品种zn1610，接收Tick数据,不根据Tick生成其他周期价格数据,但可根据AddPeriod函数添加周期价格数据的设置
        #market.Subcribe('rb1705')                
        market.Subcribe('zn1705')
        market.Subcribe('ag1706')
        #market.Subcribe('au1706')
        #market.Subcribe('ni1701')
        #market.Subcribe('m1705')
        #market.Subcribe('y1705')
        #market.Subcribe('bu1706')
        #market.Subcribe('i1705')
        #market.Subcribe('CF1705')
        #询价
        #market.SubscribeForQuoteRsp('CF1705')
    else:
        #配置文件订阅函数下个版本修复，本例暂时采用Subcribe方法订阅
        market.ReadInstrumentIni()
 
    # 订阅合约时，请注意合约的大小写，中金所和郑州交易所是大写，上海和大连期货交易所是小写的
    # ReadInstrumentIni(True)调用订阅函数Subcribe，可以用AddPeriod函数添加周期参数
    # 尽量避免使用不到的周期参数，可以节省内存和CPU占用
    # 周期参数：
    # YT_M1    1分钟周期
    # YT_M3    3分钟周期
    # YT_M5    5分钟周期
    # YT_M10   10分钟周期 
    # YT_M15   15分钟周期
    # YT_M30   30分钟周期
    # YT_M60   60分钟周期
    # YT_M120  120分钟周期
    # YT_D1    日线周期
    # YT_ALL   包括了所有周期(YT_M1,YT_M3,YT_M5,YT_M10,YT_M15,YT_M30,YT_M60,YT_M120,YT_D1)  
    
    #给au1612添加根据tick生成的周期，尽量避免添加不适用的周期数据，可以降低CPU和内存占用
    market.AddPeriod('ag1706',YT_M1)   #添加M3周期（未在Subcribe、Subcribe1~Subcribe8函数中指定的周期，可以在本函数补充该品种周期，可多次调用函数设置同时保存多个周期）
    market.AddPeriod('ag1706',YT_M3)   #添加M3周期（未在Subcribe、Subcribe1~Subcribe8函数中指定的周期，可以在本函数补充该品种周期，可多次调用函数设置同时保存多个周期）
    #market.AddPeriod('ag1612',YT_M10)  #添加M10周期（未在Subcribe、Subcribe1~Subcribe8函数中指定的周期，可以在本函数补充该品种周期，可多次调用函数设置同时保存多个周期）
    #market.AddPeriod('ag1612',YT_M5)   #添加M5周期（未在Subcribe、Subcribe1~Subcribe8函数中指定的周期，可以在本函数补充该品种周期，可多次调用函数设置同时保存多个周期）
    #market.AddPeriod('zn1610',YT_ALL)  #添加所有M1、M3、M5、M10、M15、M30、M60、M120、D1周期（未在Subcribe、Subcribe1~Subcribe8函数中指定的周期，可以在本函数补充该品种周期，可多次调用函数设置同时保存多个周期）
    
    #保存Tick数据,参数1表示简单模式
    #market.SaveTick(2)
    
    print ('number:',  market.InstrumentNum)
    # main()函数内的以上部分代码只执行一次，以下while(1)循环内的代码，会一直循环执行，可在这个循环内需增加策略判断，达到下单条件即可下单

    if False:
        #***************本例暂时取消线程池部分代码，可考虑采用多线、多进程、MPI等方式实现****************        
        #进程数量，应该不大于CPU逻辑核心数
        ProcessNum=multiprocessing.cpu_count()
        print u"取本机CPU逻辑核心数%d"%ProcessNum
        #初始化线程池，只建立一次进程池，预设进程池的进程最大数量为ProcessNum
        pool = multiprocessing.Pool(processes = ProcessNum)
        #********************************************************************************************

    #字典保存各个合约tick计数，用于判断多少次tick计算1次策略，默认为0，从0开始计数
    perdealdict={"zn1701":0,"cu1701":0,"rb1706":0}
    while(1):  #死循环
   
        """        
        print(u"Wait for a New Cmd(MD)\n");
        #判断是否有新Tick数据，while循环不需要Sleep,当没有新Tick时，会处在阻塞状态
        mddict[market.OnCmd()]()
        print(u"Get A New cmd(MD)\n");

        print(u"Wait for a New Tick\n");
        if market.OnTick():  #判断是否有新Tick数据，while循环不需要Sleep,当没有新Tick时，会处在阻塞状态
            print(u"A New Tick\n");
            for i in range(market.GetUnGetTickSize()):
                name=market.GetTickInstrument() #取新TICK合约名称
                if name=="None":
                    #如何获得合约名None，则跳出本次循环。
                    continue;          
                #打印该合约数据 
                print(name,market.InstrumentID(name), market.LastPrice(name)) 
                #*****************本例暂时取消线程池部分代码，可考虑采用多线、多进程、MPI等方式实现*******************
                if False:
                    perdealdict[name]=perdealdict[name]+1 
                    #合约name的tick计数+1
                    if perdealdict[name]>5: #每5次Tick计算一次策略，具体根据策略需要和CPU负荷确定多少次Tick计算一次策略
                        perdealdict[name]=0 #置0后下次从0开始计数
                        #多进程，进程池
                        for tid in xrange(ProcessNum):
                            #msg = "hello %d" %(i)
                            print u"将数据发送给进程池中的一个线程进行策略计算:%s\n"%name
                            #将数据发送给进程池中的一个线程进行策略计算
                            #pool.apply_async(StrategyProcess, (market.InstrumentID(name),))   #维持执行的进程总数为processes，当一个进程执行完毕后会添加新的进程进去
                            #msg = "@@@@@hello: %s\n" %(name)
                            pool.apply_async(StrategyProcess, (name, market.LastPrice(name) ))   #维持执行的进程总数为processes，当一个进程执行完毕后会添加新的进程进去     
            #************************************************************************************************
        """
        #result = pool.apply_async(StrategyProcess, (i,))
            #pool.apply_async(StrategyProcess, (msg, ))   #维持执行的进程总数为processes，当一个进程执行完毕后会添加新的进程进去
        #time.sleep(0.1)  #系统休眠0.1秒
        #判断当前时间是否在交易时间内，如果在返回真，则开始执行
        #if (IsStockTrade()): 
       
        #if True:
           #print market.LastPrice('zn1610')     #打印该品种在行情接口的变量LastPrice (最新价)
           #print market.BidPrice1('zn1610')     #打印该品种在行情接口的变量BidPrice
           
           #                       0是当前周期 
           # 合约  周期类型  价格类型 多少日前 周期数           
 
           #打印显示 该品种的1分钟 收盘价
           #print u'1分钟周期,上1个周期的收盘价:'
           #                     品种   周期    价格类型  1天前的数据 
           #print u'%f'%market.GetPeriodData('zn1610',YT_M1,YT_CLOSE,0)
           
           #for i in range(0, 5):
               #print u'%f'%market.GetPeriodData('zn1610',YT_M1,YT_CLOSE,i)
               
        #打印自动生成的1分钟周期的数据
        
        print u'最近5个1分钟周期值'
        print u'-----------begin--------------'
        #打印该品种显示3分钟周期最近5个周期的收盘价格，若价格>0表示已接收到数据，否则还未接收到足够的Tick生成周期K线的数据
    
        for i in range(0, 5):
            tempclose=market.GetPeriodData('ag1706',YT_M1,YT_CLOSE,i)
            if tempclose>0:
                print tempclose
        print u'-----------end----------------'
        time.sleep(5)

        '''          
        #market.BeginStrategyID(1)
        #合约zn1607的1分钟收盘价，5周期上穿20周期，则下多单
        if market.CrossUp('zn1610',YT_M1,YT_CLOSE,5,20):
              #                                品种代码    多空方向    开仓还是平仓  市价或现价   价格  下单数量
              #下单函数原型 InsertOrder(self, instrumentID, direction,  offsetFlag, priceType,  price,   num):              
             OrderRef = trader.InsertOrder('zn1610', YT_D_Buy, YT_OF_Open, YT_OPT_LimitPrice, market.LastPrice('zn1610')+10, 1)
             #交易记录写日志文件
             #market.LogFile(u'traderecord.csv',u'交易下单  zn1610  YT_D_Buy')
             time.sleep(1)
             #撤销所有未成交的委托单
             ret = trader.DeleteOrder('zn1610', OrderRef) 
             
             #对该单号成交的品种设置动态止损，AddStopMonitor未演示，等待封装完成
                       #品种    #单号  #止损方式(动态止损YT_Dynamic,固定价格止损YT_Static ) #止损阈值百分比 3表示离上一次最高点或最低点反向绝对值为3%止损             
             market.AddStopMonitor('zn1610', OrderRef,YT_Dynamic,3)   
             
        #合约zn1607的1分钟收盘价，5周期上穿20周期，则下空单
        if market.CrossDown('zn1610',YT_M1,YT_CLOSE,5,20):
              #                                品种代码    多空方向    开仓还是平仓  市价或现价   价格  下单数量
              #下单函数原型 InsertOrder(self, instrumentID, direction,  offsetFlag, priceType,  price,   num):              
             OrderRef2 = trader.InsertOrder('zn1610', YT_D_Sell, YT_OF_Open, YT_OPT_LimitPrice, market.LastPrice('zn1610')-10, 1)    
             #交易记录写日志文件
             #market.LogFile(u'traderecord.csv',u'交易下单  zn1610  YT_D_Sell')
             time.sleep(1)
             #撤销所有未成交的委托单
             ret = trader.DeleteOrder('zn1610', OrderRef)
          
        '''
        #market.EndStrategyID(1)
        #while(datetime.datetime.now() < gExitTime):
        #时间大于退出时间，退出程序。实际操盘中，应考虑夜盘交易时间的影响
        #print (u'未到开盘时间')
        #time.sleep(60)
           

if __name__ == '__main__':
    main()
    

     

    

  
    
