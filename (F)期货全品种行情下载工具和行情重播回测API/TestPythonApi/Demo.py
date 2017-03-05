#导入A股 API交易库
from TestMD import *
#导入多进程库
import multiprocessing
test = TestMD()   #交易接口类赋值给变量 

#python默认的递归深度是很有限的，大概是900多的样子，当递归深度超过这个值的时候，就会引发这样的一个异常
#解决的方式是手工设置递归调用深度，方式为
import sys   
sys.setrecursionlimit(1000000) #例如这里设置为一百万  


num=0    

#回调类型
SYSTEM_SYSTEM_NONE              = 8000 #登录成功
SYSTEM_LOGIN_SCUESS             = 8001 #登录成功
SYSTEM_LOGIN_DENIED             = 8002 #登录被拒绝
SYSTEM_LOGIN_ERRORPASSWORD      = 8003 #密码错误
SYSTEM_LOGINOUT_SCUESS          = 8004 #登出成功
SYSTEM_NETCONNECT_SCUESS        = 8005 #连接成功
SYSTEM_NETCONNECT_BREAK         = 8006 #断开连接
SYSTEM_NETCONNECT_FAILER        = 8007 #连接失败
#SYSTEM_SUBCRIBE_SCUESS          = 8008 #订阅成功
#SYSTEM_UNSUBCRIBE_SCUESS        = 8009 #取消订阅成功 
SYSTEM_NEWTICK                  = 8010 #新Tick到来 
SYSTEM_SYSTEM_ERROR             = 8011 #错误应答 

SYSTEM_ORDER_INSERT             = 8012 #下单成功
SYSTEM_ORDER_DELETE      	= 8013 #撤单成功
SYSTEM_ORDER_NOMONIEY     	= 8014 #下单资金不足
SYSTEM_ACCOUNT_AVAILABLE    	= 8015 #可用资金
SYSTEM_ACCOUNT_BALANCE   	= 8016 #权益
 
API_CMD_CONNECT                 = 8017   #8000
API_CMD_LOGIN_SUCESS            = 8018   #8001
API_CMD_LOGIN_NETBREAK          = 8019   #8002
API_CMD_LOGIN_ERRORPASSWORD     = 8020   #8003
API_CMD_LOGIN_ACCESSDENIED      = 8021   #8004
SERVER_ORDER_ACCEPT             = 8022   #8006


def OnNoneCmd():
    #回调指令缓冲区已为空（因为短时间获得多个指令，时间间隔态度，在下面的for i in range(market.GetUnGetCmdSize()):循环执行了多次已经完成了）
    print "OnNoneCmd"
    
def OnRspUserLogin():
    #登录成功
    print "OnRspUserLogin"
    
def OnRspUserLoginDenied():
    #登录被拒绝
    print "OnRspUserLoginDenied"  
    
def OnRspUserLoginErrPassword():
    #登录密码错误
    print "OnRspUserLoginErrPassword"
    
def OnRspUserLogout():
    #登出成功
    print "OnRspUserLogout"
    
def OnFrontConnected():
    #连接成功
    print "OnFrontConnected"
    #连接成功，登录账号
    if True:
        #登录方式1(自动读取配置文件信息登录)
        test.ReqUserLogin()
    else:
        #登录方式2(账户、密码、brokeid通过参数提交登录)
        test.ReqUserLogin()
        
def OnFrontDisconnected():
    #断开连接
    print "OnFrontDisconnected"
    #每隔5s断线从连    
    time.sleep(5)
    test.ReqConnect()
    
def OnFrontConnectedFailer():
    #连接失败
    print "OnFrontConnectedFailer"
    
#def OnRspSubMarketData(content):
#订阅成功
#    print "OnRspSubMarketData[%s]"%content
    
#def OnRspUnSubMarketData(content):
#取消订阅行情成功
#    print "OnRspUnSubMarketData[%s]"%content  
"""    
def OnRspTick(content):
    global num
    #新的一笔Tick数据驱动
    print "OnRspTick[%s]"%content
    if content!="":
        num=num+1
        #以下增加交易策略逻辑的计算
        print u"(%d)%s %s [%0.02f]"%(num,content,market.InstrumentID(content), market.LastPrice(content)) #打印该合约数据
"""
def OnRspError():
    print u"OnRspError(错误应答)"
    
def OnRtnOrder(content):
    print u"下单成功"
def OnRspOrderAction(content):
    print u"撤单成功"
def OnRspOrderNomoney(content):
    print u"资金不足，下单失败"   
def OnRspQryTradingAvailable(content):
    print u"可用资金"        
def OnRspQryTradingBalance(content):
    print u"权益"        
    

cmddict={
    SYSTEM_SYSTEM_NONE:OnNoneCmd,
    SYSTEM_LOGIN_SCUESS:OnRspUserLogin,
    SYSTEM_LOGIN_DENIED:OnRspUserLoginDenied,
    SYSTEM_LOGIN_ERRORPASSWORD:OnRspUserLoginErrPassword,
    SYSTEM_LOGINOUT_SCUESS:OnRspUserLogout,
    SYSTEM_NETCONNECT_SCUESS:OnFrontConnected,
    SYSTEM_NETCONNECT_BREAK:OnFrontDisconnected,
    SYSTEM_NETCONNECT_FAILER:OnFrontConnectedFailer,
    #SYSTEM_SUBCRIBE_SCUESS:OnRspSubMarketData,
    #SYSTEM_UNSUBCRIBE_SCUESS:OnRspUnSubMarketData,
    #SYSTEM_NEWTICK:OnRspTick,
    SYSTEM_SYSTEM_ERROR:OnRspError,
    SYSTEM_ORDER_INSERT:OnRtnOrder,
    SYSTEM_ORDER_DELETE:OnRspOrderAction,
    SYSTEM_ORDER_NOMONIEY:OnRspOrderNomoney,    
    SYSTEM_ACCOUNT_AVAILABLE:OnRspQryTradingAvailable,
    SYSTEM_ACCOUNT_BALANCE:OnRspQryTradingBalance    
}
#-----------------------------------------------------------------------------------------
#回调函数
def OnCmd():
    while (1):
        #if trader.OnCmd():  #接受到的指令回调
        #获得缓冲区指令个数，遍历执行，大多数情况下只有1条指令，立即被处理完成
        #     for i in range(trader.GetCmdSize()):
        #                cmddict[trader.GetCmd()]()
        print(u"Wait for a New Cmd\n");
        cmddict[OnCmd()]()
        print(u"A New cmd\n")        
        '''        
        if trader.OnCmd():  #判断是否有新Tick数据，while循环不需要Sleep,当没有新Tick时，会处在阻塞状态
            print(u"A New cmd\n");
            for i in range(trader.GetUnGetCmdSize()):
                tup=trader.GetCmd()
                #print u"-----begin-----"
                #print tup[0]
                #print tup[1]
                #print u"-----end-----"
                cmddict[tup[0]](tup[1])
         '''

# main()为程序入口函数，所有的行情、交易订阅、指标调用、下单的逻辑均写在此函数内执行
def main():

    #读配置文件账号信息，自动傻瓜式初始化连接服务器并登录，自动断线重连
    #test.SetAutoMode()
    #while(1):  #死循环
    #        OnCmd()
    #print(u"官方QQ群 5172183 \n");
    #初始化线程池，只建立一次进程池，预设进程池的进程最大数量为1
    '''    
    pool = multiprocessing.Pool(processes = 1)
    #开启多进程来进行回调函数，维持执行的进程总数为1
    pool.apply_async(OnCmd, (1,))
    num=0
    '''
                
    OrderRef2 = test.GetTestData('ag1706','20170201', '20170401', 100)    
    while(1):  #死循环，反复执行
        #time.sleep(0.1)  #系统休眠0.1秒
        #num=num+1
        #time.sleep(10)
        #OrderRef2 = test.InsertOrder('600200', YT_D_Sell, YT_OF_Open, YT_OPT_LimitPrice, market.LastPrice('600200')-10, 1)   
        #print ('<%d>'%num)       
  
        print(u"Wait for a New Cmd\n");
        cmddict[OnCmd()]()
        print(u"A New cmd\n")     
        #time.sleep(1)
        #撤销所有未成交的委托单
        #ret = test.DeleteOrder('zn1610', OrderRef)        
        #time.sleep(5)  #sleep1秒，防止死循环导致CPU占有率过高，1即可，不宜过大，若过大会导致程序进程长时间无响应，丢失行情数据
if __name__ == '__main__':
    main()
    

    
 
    
    
    