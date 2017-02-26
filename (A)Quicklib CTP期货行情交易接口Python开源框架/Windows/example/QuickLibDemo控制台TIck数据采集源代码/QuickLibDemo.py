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
market = CTPMarket()   #行情接口类赋值给变量

# main()为程序入口函数，所有的行情、交易订阅、指标调用、下单的逻辑均写在此函数内执行
def main():
    #打印交易日    
    #print today
    #设置程序标题
    market.SetTitle(u"QucikLib CTP接口期货Tick数据采集器，保存csv格式 QQ群 5172183")
    #打印信息到控制台窗口
    print(u"官方QQ群 5172183 \n");
    
    #设置拒绝接收行情服务器数据的时间，有时候（特别是模拟盘）在早晨6-8点会发送前一天的行情数据，若不拒收的话，会导致历史数据错误，本方法最多可以设置4个时间段进行拒收数据
    #market.SetRejectdataTime(0.0400, 0.0840, 0.1530, 0.2030, NULL, NULL, NULL, NULL); 
    market.Subcribe('zn1705')
    market.Subcribe('ag1706')
    
    #从配置文件Instrument.ini  读取订阅的合约，每行写一个要订阅行情的合约，用调用ReadInstrument()的方式就无需通过调用Subcribe系列函数方式来订阅合约了，编译成exe后，也方便通过更改配置文件来更改合约
    #market.ReadInstrumentIni()
    
    market.SaveTick(2)
    
    print ('number:',  market.InstrumentNum)
 
    #每次循环sleep休眠 10秒死循环导致CPU占有率过高,死循环，防止程序退出
    while(1):
        time.sleep(1000)

if __name__ == '__main__':
    main()
    

    
 
    
    
    