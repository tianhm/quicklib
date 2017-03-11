# -*- coding=utf-8 -*-
from ctypes import *
from TestMDType import *
import time


class TestMD(object):
	def __init__(self):

		self.d2 = CDLL('QuickLibTestMD.dll')
 


		self.fLogin = self.d2.Login
		self.fLogin.argtypes = []
		self.fLogin.restype = c_int32
		
		self.fGetTestData = self.d2.GetTestData
		self.fGetTestData.argtypes = [c_char_p, c_char_p, c_char_p, c_int32]
		self.fGetTestData.restype = c_int32

 
		
 
		
		self.fSetShowPosition = self.d2.SetShowPosition
		self.fSetShowPosition.argtypes = [c_bool]
		self.fSetShowPosition.restype = c_void_p			
		 	
		self.fGetUnGetCmdSize = self.d2.GetUnGetCmdSize
		self.fGetUnGetCmdSize.argtypes = []
		self.fGetUnGetCmdSize.restype = c_int32		
	
		self.fGetCmdContent = self.d2.GetCmdContent
		self.fGetCmdContent.argtypes = []
		self.fGetCmdContent.restype = c_char_p	
		
		self.fGetMD_Tick = self.d2.GetMD_Tick
		self.fGetMD_Tick.argtypes = []
		self.fGetMD_Tick.restype = c_void_p	
		
		                
		self.fDeleteMD_Tick = self.d2.DeleteMD_Tick
		self.fDeleteMD_Tick.argtypes = []
 	                
	
		self.fGetCmd = self.d2.GetCmd
		self.fGetCmd.argtypes = []
		self.fGetCmd.restype = c_void_p	
		
		self.fOnCmd = self.d2.OnCmd
		self.fOnCmd.argtypes = []
		self.fOnCmd.restype = c_int32	
		
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
		
 	
		
		
 	
	def Login(self):
		return self.fLogin()

	def GetTestData(self, instrumentID, begintime, endtime, priceType):
		return self.fGetTestData(instrumentID, begintime , endtime , priceType   )
 
			
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
	
	# 
	def GetMD_Tick(self):
		return self.fGetMD_Tick()
	
	
	def DeleteMD_Tick(self):
	        self.fDeleteMD_Tick()
	
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
	
	
 