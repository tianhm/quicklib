#导入CTP行情库
from CTPMarket import *
#导入时间库
import time, datetime
market = CTPMarket()   #行情接口类赋值给变量
#trader = CTPTrader()   #交易接口类赋值给变量 

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
#------------------------------------------MD回调代码段开始----------------------------------------------
num=0    
#回调类型
MD_EMPTY                    = 8000 #无消息
MD_LOGIN_SCUESS             = 8001 #登录成功
MD_LOGIN_DENIED             = 8002 #登录被拒绝
MD_LOGIN_ERRORPASSWORD      = 8003 #密码错误
MD_LOGINOUT_SCUESS          = 8004 #登出成功
MD_NETCONNECT_SCUESS        = 8005 #连接成功
MD_NETCONNECT_BREAK         = 8006 #断开连接
MD_NETCONNECT_FAILER        = 8007 #连接失败
MD_SUBCRIBE_SCUESS          = 8008 #订阅成功
MD_UNSUBCRIBE_SCUESS        = 8009 #取消订阅成功 
MD_NEWTICK                  = 8010 #新Tick到来 
MD_SYSTEM_ERROR             = 8011 #错误应答 

def MD_OnEmptyCmd():
    #回调指令缓冲区已为空（因为短时间获得多个指令，时间间隔态度，在下面的for i in range(market.GetUnGetCmdSize()):循环执行了多次已经完成了）
    print "---------------MD_OnEmptyCmd---------------"    
def MD_OnRspUserLogin():
    #登录成功
    print "---------------MD_OnRspUserLogin---------------"
def MD_OnRspUserLoginDenied():
    #登录被拒绝
    print "---------------MD_OnRspUserLoginDenied---------------"
def MD_OnRspUserLoginErrPassword():
    #登录密码错误
    print "---------------MD_OnRspUserLoginErrPassword---------------"
def MD_OnRspUserLogout():
    #登出成功
    print "---------------MD_OnRspUserLogout---------------"
def MD_OnFrontConnected():
    #连接成功
    print "---------------MD_OnFrontConnected---------------"
def MD_OnFrontDisconnected():
    #断开连接
    print "---------------MD_OnFrontDisconnected---------------"    
def MD_OnFrontConnectedFailer():
    #连接失败
    print "---------------MD_OnFrontConnectedFailer---------------"
def MD_OnRspSubMarketData():
    #订阅成功
    print "---------------MD_OnRspSubMarketData---------------"
def MD_OnRspUnSubMarketData():
    #取消订阅行情成功
    print "---------------MD_OnRspUnSubMarketData---------------"
def MD_OnRspTick():
    #新的一笔Tick数据驱动
    #print "---------------MD_OnTick---------------"       
    global num
    num=num+1
    #取得新TICK的合约代码
    Instrument =market.GetCmdContent_Tick() 
    #print "Instrument %s"%Instrument
    #打印该合约数据, 可增加交易策略逻辑计算，计算进程放入其它线程或进程中，以免耗时计算阻塞行情接收和其它回调
    print u"(%d)%s %s [%0.02f][%0.00f]"%(num,Instrument,market.InstrumentID(Instrument), market.LastPrice(Instrument), market.Volume(Instrument))
def MD_OnRspError():
    print u"OnRspError(错误应答)"
    
mddict={
          MD_EMPTY:MD_OnEmptyCmd,
          MD_LOGIN_SCUESS:MD_OnRspUserLogin,
          MD_LOGIN_DENIED:MD_OnRspUserLoginDenied,
          MD_LOGIN_ERRORPASSWORD:MD_OnRspUserLoginErrPassword,
          MD_LOGINOUT_SCUESS:MD_OnRspUserLogout,
          MD_NETCONNECT_SCUESS:MD_OnFrontConnected,
          MD_NETCONNECT_BREAK:MD_OnFrontDisconnected,
          MD_NETCONNECT_FAILER:MD_OnFrontConnectedFailer,
          MD_SUBCRIBE_SCUESS:MD_OnRspSubMarketData,
          MD_UNSUBCRIBE_SCUESS:MD_OnRspUnSubMarketData,
          MD_NEWTICK:MD_OnRspTick,
          MD_SYSTEM_ERROR:MD_OnRspError
        }
#------------------------------------------MD回调代码段结束----------------------------------------------
# main()为程序入口函数，所有的行情、交易订阅、指标调用、下单的逻辑均写在此函数内执行
def main():
    market.SetTitle(u"程序标题")
    #已注册默认行情服务器地址   可用RegisterFront()方法添加注册服务器地址
    #market.RegisterFront(u"tcp://127.0.0.1:10031") #添加注册行情服务器地址
    
    print (u"CTP2 API版本%s"%market.GetApiVersion())   
    market.SetPrintState(False);
    print(u"官方QQ 一群 5172183 、QQ二群 180452598、QQ三群 210945480\n");
    #os.system("QucikLib CTP接口期货Tick数据采集器，保存csv格式 QQ群 5172183")    
    #retLogin = market.Login()  #调用交易接口元素，通过 “ 接口变量.元素（接口类内部定义的方法或变量） ” 形式调用
    # Login()，不需要参数，Login读取QuickLibTD.ini的配置信息，并登录
    # 返回0， 表示登录成功，
    # 返回1， FutureTDAccount.ini错误
    # 返回2， 登录超时
    #print ('login: ', retLogin)   
    #if retLogin==0:
    #   print u'登陆行情服务器成功'
    #else:
    #   print u'登陆行情服务器失败'

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
    # QL-M1    1分钟周期
    # QL-M3    3分钟周期
    # QL-M5    5分钟周期
    # QL-M10   10分钟周期 
    # QL-M15   15分钟周期
    # QL-M30   30分钟周期
    # QL-M60   60分钟周期
    # QL-M120  120分钟周期
    # QL-D1    日线周期
    # QL-ALL   包括了所有周期(QL-M1,QL-M3,QL-M5,QL-M10,QL-M15,QL-M30,QL-M60,QL-M120,QL-D1)  

    #Subcribe系列函数最后一个参数，true表示打印tick数据，false表示不打印
    #market.Subcribe('600200',True)                #订阅品种zn1610，接收Tick数据,不根据Tick生成其他周期价格数据,但可根据AddPeriod函数添加周期价格数据的设置
    #market.Subcribe('600119',True)              
    # main()函数内的以上部分代码只执行一次，以下while(1)循环内的代码，会一直循环执行，可在这个循环内需增加策略判断，达到下单条件即可下单
    #market.ReadInstrumentIni(True)

    FirstTick=True;
    market.SaveTick(2) #3保存所有数据，  2保存股票主要数据   1仅保存最新价格数据
    
    while(1):  #死循环，反复执行
        #判断当前时间是否在交易时间内，如果在返回真，则开始执行
        #if (IsStockTrade()): 
        #当新的Tick到来时，才继续处理，否则会阻塞等待，Tick事件驱动模式具备高性能不占用CPU。请注意本函数会阻塞本线程，对绝对止损等逻辑处理需要放在另一个线程或进程中处理。
        #非交易时间的第1比Tick数据，如果没有本段，收盘后只有1比数据将无法完整打印
        #if (IsStockTrade()): 
        '''        
        print(u"Wait for a New Cmd\n");
        if market.OnCmd():  #判断是否有新Tick数据，while循环不需要Sleep,当没有新Tick时，会处在阻塞状态
            print(u"A New cmd\n");
            for i in range(market.GetUnGetCmdSize()):
                tup=market.GetCmd();      
                cmddict[tup[0]](tup[1])
        '''
        print(u"Wait for a New Cmd(MD)\n");
        #判断是否有新Tick数据，while循环不需要Sleep,当没有新Tick时，会处在阻塞状态,while循环内无需再用Sleep 
        mddict[market.OnCmd()]()
        print(u"Get A New cmd(MD)\n");                
           #print("600321:%0.02f"%market.LastPrice('600321'))        
           #print(market.InstrumentID('600322'), market.LastPrice('600322'))
           #print("(B)600322:%0.02f"%market.LastPrice('600322'))
           #print(market.InstrumentID('600323'), market.LastPrice('600323'))
           #print("600323:%0.02f"%market.LastPrice('600323'))           
           #print market.LastPrice('1')     #打印该品种在行情接口的变量BidPrice
           #print market.LastPrice(1)     #打印该品种在行情接口的变量BidPrice
           #print market.ExchangeID('600119') 
           #print market.LastPrice('600200')
           #print market.LastPrice('600319')
           #合约zn1610-zn1613价差>300,卖zn1610买zn613
           #if market.LastPrice('zn1610')-market.LastPrice('zn1613')>300:
              #                                品种代码    多空方向    开仓还是平仓  市价或现价   价格  下单数量
              #下单函数原型 InsertOrder(self, instrumentID, direction,  offsetFlag, priceType,  price,   num):              
             #OrderRef1 = trader.InsertOrder('zn1610', QL-D_Sell, QL-OF_Open, QL-OPT_LimitPrice, market.LastPrice('zn1610')-10, 1)
             #time.sleep(0.5)
             #撤销所有未成交的委托单
             #ret = trader.DeleteOrder('zn1610', OrderRef) 
                        
             #OrderRef2 = trader.InsertOrder('zn1613', QL-D_Buy, QL-OF_Open, QL-OPT_LimitPrice, market.LastPrice('zn1610')+10, 1)        
             #time.sleep(1)
             #撤销所有未成交的委托单
             #ret = trader.DeleteOrder('zn1613', OrderRef)

           #while(datetime.datetime.now() < gExitTime):
           #时间大于退出时间，退出程序。实际操盘中，应考虑夜盘交易时间的影响
                #print (u'未到开盘时间')
 
        #time.sleep(3)  #sleep1秒，防止死循环导致CPU占有率过高，1即可，不宜过大，若过大会导致程序进程长时间无响应，丢失行情数据

if __name__ == '__main__':
    main()
    

    
 
    
    
    