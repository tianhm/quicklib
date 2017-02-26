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

def main():
    from distutils.core import setup
    import py2exe
    #setup(windows = ['QuickLibSimple.pyw'])
    #setup(console = ['QuickLibSimple.py'])
    setup(
    console = [{"script":"QuickLibDemo.py" ,"icon_resources": [(1, "main.ico")]} ]
    ) 
    
    #setup(console = [{"script": "QuickLibDemo.py"}])

    #
    pass

if __name__ == '__main__':
    main()
