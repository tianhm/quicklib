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
 

# main()为程序入口函数，所有的行情、交易订阅、指标调用、下单的逻辑均写在此函数内执行
def main():
    test.GetTestData('ag1706','20170201', '20170401', 100)    
    while(1): 
        print(u"Wait for a New Cmd\n");
        cmddict[test.OnCmd()]()
        print(u"A New cmd\n")     
 
if __name__ == '__main__':
    main()
    

    
 
    
    
    