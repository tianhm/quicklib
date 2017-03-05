# -*- coding=utf-8 -*-
from ctypes import *
from TestMDType import *
import time


class TestMD(object):
	def __init__(self):

		self.d2 = CDLL('QuickLibTestMD.dll')
		
		'''
		i = 0
		while (i < 5):
			time.sleep(1)
			if (self.d2.IsInitOK() == 0):
					i += 1
			else:
				break
		else:
			print('market init error')
			return		
		

		self.Index = dict()
		for i in range(self.InstrumentNum):
			data = self.fGetData(i)
			data = cast(data, POINTER(sDepMarketData))
			self.Index[str(data[0].InstrumentID)] = data
		pass

                '''


		self.fLogin = self.d2.Login
		self.fLogin.argtypes = []
		self.fLogin.restype = c_int32
		
		self.fGetTestData = self.d2.GetTestData
		self.fGetTestData.argtypes = [c_char_p, c_char_p, c_char_p, c_int32]
		self.fGetTestData.restype = c_int32

		self.fDeleteOrder = self.d2.DeleteOrder
		self.fDeleteOrder.argtypes = [c_char_p, c_int32]
		self.fDeleteOrder.restype = c_int32

		self.fQryTradedVol = self.d2.QryTradedVol
		self.fQryTradedVol.argtypes = [c_int32]
		self.fQryTradedVol.restype = c_int32
		
		self.fQryPosition = self.d2.QryPosition
		self.fQryPosition.argtypes = [c_char_p,c_int32]
		self.fQryPosition.restype = c_int32		
		
		self.fQryPositionList = self.d2.QryPositionList
		self.fQryPositionList.argtypes = [c_int32]
		self.fQryPositionList.restype = c_void_p
		
		self.fQryBalance = self.d2.QryBalance
		self.fQryBalance.argtypes = [c_bool]
		self.fQryBalance.restype = c_double	
		
		self.fQryAvailable = self.d2.QryAvailable
		self.fQryAvailable.argtypes = []
		self.fQryAvailable.restype = c_double
		
		self.fSetShowPosition = self.d2.SetShowPosition
		self.fSetShowPosition.argtypes = [c_bool]
		self.fSetShowPosition.restype = c_void_p			
		 	
		self.fGetUnGetCmdSize = self.d2.GetUnGetCmdSize
		self.fGetUnGetCmdSize.argtypes = []
		self.fGetUnGetCmdSize.restype = c_int32		
	
		self.fGetCmdContent = self.d2.GetCmdContent
		self.fGetCmdContent.argtypes = []
		self.fGetCmdContent.restype = c_char_p			
	
		self.fGetCmd = self.d2.GetCmd
		self.fGetCmd.argtypes = []
		self.fGetCmd.restype = c_void_p	
		
		self.fOnCmd = self.d2.OnCmd
		self.fOnCmd.argtypes = []
		self.fOnCmd.restype = c_bool	
		
	        #连接服务器		
		self.fReqConnect = self.d2.ReqConnect
		self.fReqConnect.argtypes = []
		
 		#断开连接服务器		
		self.fReqDisConnect = self.d2.ReqDisConnect
		self.fReqDisConnect.argtypes = []		
		
		#账户登录	
		self.fReqUserLogin = self.d2.ReqUserLogin
		self.fReqUserLogin.argtypes = []		
                
                #账户登出
		self.fReqUserLoginOut = self.d2.ReqUserLoginOut
		self.fReqUserLoginOut.argtypes = []	
		
		self.fSetAutoMode = self.d2.SetAutoMode
		self.fSetAutoMode.argtypes = []			
		
		
 	
	def Login(self):
		return self.fLogin()

	def GetTestData(self, instrumentID, begintime, endtime, priceType):
		return self.fGetTestData(instrumentID, begintime , endtime , priceType   )
								 

	def DeleteOrder(self, instrumentID, orderRef):
		return self.fDeleteOrder(instrumentID, orderRef)

	def QryTradedVol(self, orderRef):
		return self.fQryTradedVol(orderRef)
	
	#查询品种持仓
	def QryPosition(self, instrumentID,positiontype):
		return self.fQryPosition(instrumentID,positiontype)
	
	#查询持仓列表
	def QryPositionList(self, orderRef):
		return self.fQryPositionList(orderRef)


        #查询权益   BalanceType=True动态权益    BalanceType=False静态权益
	def QryBalance(self, BalanceType):
		return self.fQryBalance(BalanceType)
	
	#查询可用资金
	def QryAvailable(self):
		return self.fQryAvailable()
			
	#设置更新持仓数据时显示,仅对控制台有效
	def SetShowPosition(self,showstate):
		self.fSetShowPosition(showstate)
		
	#获取回调信息数量
	def GetUnGetCmdSize(self):
		return self.fGetUnGetCmdSize()

	#获取回调信息
	def GetCmd(self):
	        return (self.fGetCmd(),self.fGetCmdContent()) 
	#指令驱动函数
	def OnCmd(self):
		return self.fOnCmd()
	
	
	#连接服务器
	def ReqConnect(self):
		self.fReqConnect()
	
	#断开连接服务器
	def ReqDisConnect(self):
		self.fReqDisConnect()	
	
	#账户登录
	def ReqUserLogin(self):
		self.fReqUserLogin()
	
	#账户登出
	def ReqUserLoginOut(self):
		self.fReqUserLoginOut()		
	
	
	
	#读配置文件账号信息，自动傻瓜式初始化连接服务器并登录
	def SetAutoMode(self):
		self.fSetAutoMode()		
	