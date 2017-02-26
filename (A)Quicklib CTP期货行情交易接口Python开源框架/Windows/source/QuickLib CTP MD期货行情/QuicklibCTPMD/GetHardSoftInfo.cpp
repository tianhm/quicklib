/*
1.本文件为Quicklib 期货行情库底层代码
2.本文件及调用的库文件Quicklib CTP期货行情库和交易库遵循 开源协议GPL v3
简单的说：对基于GPL v3协议的源代码，若个人或机构仅仅是自己使用，则可以闭源。
若基于该开源代码，开发出程序或衍生产品用于商业行为则也必须开源。

Quciklib Python框架和工具遵循GPL v3协议包括：
（1）Quicklib CTP   期货行情库
（2）Quicklib CTP   期货交易库
（3）Quicklib CTP2  A股行情库
（4）Quicklib MOM模式  博易资管交易库
（用于接入资管投顾系统，MOM模式可实现私募进行投顾的选拔考核，并通过自己的风控系统接入实盘）

Quciklib Python框架和工具暂不遵循开源协议包括：
（5）Quicklib 监控器库（预警、监控、交易信号数据复制、跟单）（可免费试用）

对Quciklib开源库做出贡献的，并得到原始作者肯定的，将公布在http://www.quciklib.cn网站上，
并添加在《开源说明和感谢.txt》，并将该文件不断更新放入每一个新版本的Quicklib库里。

原始作者：QQ 147423661 林(王登高)
官方网站：http://www.quicklib.cn
官方QQ群：5172183(1群)、25884087(2群)
*/
#include "stdafx.h"
#include "GetHardSoftInfo.h"

CGetMachineInfo::CGetMachineInfo(void)
{
	OSVERSIONINFO version;
	memset (&version, 0, sizeof (version));
	version.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);

	//GetVersionEx (&version);
	//if (version.dwPlatformId == VER_PLATFORM_WIN32_NT)//nt
	//{
	//	ReadPhysicalDriveInNT();
	//}
	if(version.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)//9x
	{
		ReadDrivePortsInWin9X();
	}
	else
	{
		ReadPhysicalDriveInNT();
	
	}
}

BOOL CGetMachineInfo::ReturnInfo(int drive, DWORD diskdata [])
{
	char string1 [1024];
	__int64 sectors = 0;
	__int64 bytes = 0;
	
	//  copy the hard drive serial number to the buffer
	strcpy_s (string1,sizeof(string1), ConvertToString (diskdata, 10, 19));
	if (0 == HardDriveSerialNumber [0] &&
		//  serial number must be alphanumeric
		//  (but there can be leading spaces on IBM drives)
		(isalnum (string1 [0]) || isalnum (string1 [19])))
		strcpy_s (HardDriveSerialNumber,sizeof(HardDriveSerialNumber), string1);
	
	//#ifdef PRINTING_TO_CONSOLE_ALLOWED
	
	switch (drive / 2)
	{
	case 0: str_HardDesk_Form ="Primary Controller";
		break;
	case 1: str_HardDesk_Form ="Secondary Controller";
		break;
	case 2: str_HardDesk_Form ="Tertiary Controller";
		break;
	case 3: str_HardDesk_Form ="Quaternary Controller";
		break;
	}
	//MessageBox(NULL,str_HardDesk_Form,NULL,NULL);
	switch (drive % 2)
	{
	case 0: str_Controller ="Master drive";
		break;
	case 1: str_Controller ="Slave drive";
		break;
	}
	
	str_DN_Modol = string(ConvertToString (diskdata, 27, 46));  //改
	
	str_DN_Serial = string(ConvertToString (diskdata, 10, 19));  //改
	
	str_DN_ControllerRevision = string(ConvertToString (diskdata, 23, 26)); //改


	//printf("harddisk %s %s %s\n------------------------------\n\n", str_DN_Modol.c_str(), str_DN_Serial.c_str(), str_DN_ControllerRevision.c_str());

	

	char temp[200] = {0};
	_snprintf_s(temp, sizeof(temp), sizeof(temp), "%u", diskdata[21] * 512);
	//str_HardDeskBufferSize.Format();
	str_HardDeskBufferSize = string(temp);
	
	//printf ("Drive Type________________________: ");
	if (diskdata [0] & 0x0080)
		str_HardDeskType ="Removable";
	else if (diskdata [0] & 0x0040)
		str_HardDeskType ="Fixed";
	else str_HardDeskType ="Unknown";
	
	//  calculate size based on 28 bit or 48 bit addressing
	//  48 bit addressing is reflected by bit 10 of word 83
	if (diskdata [83] & 0x400) 
		sectors = diskdata [103] * 65536I64 * 65536I64 * 65536I64 + 
		diskdata [102] * 65536I64 * 65536I64 + 
		diskdata [101] * 65536I64 + 
		diskdata [100];
	else
		sectors = diskdata [61] * 65536 + diskdata [60];
	//  there are 512 bytes in a sector
	bytes = sectors * 512;

	char temp2[200] = { 0 };
	_snprintf_s(temp2, sizeof(temp2), sizeof(temp2), "%I64d", bytes);
	str_HardDeskSize = string(temp2);
	//str_HardDeskSize.Format("%I64d",bytes);
	return 1;
	
}

//conversion to char 
char *CGetMachineInfo::ConvertToString(DWORD diskdata [256], int firstIndex, int lastIndex)
{
	static char string [1024];
	int index = 0;
	int position = 0;
	
	//  each integer has two characters stored in it backwards
	for (index = firstIndex; index <= lastIndex; index++)
	{
		//  get high byte for 1st character
		string [position] = (char) (diskdata [index] / 256);
		position++;
		
		//  get low byte for 2nd character
		string [position] = (char) (diskdata [index] % 256);
		position++;
	}
	//  end the string 
	string [position] = '\0';
	
	//  cut off the trailing blanks
	for (index = position - 1; index > 0 && ' ' == string [index]; index--)
		string [index] = '\0';
	return string;
}

//
int CGetMachineInfo::DoIDENTIFY(HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
							PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
							PDWORD lpcbBytesReturned)
{
	// Set up data structures for IDENTIFY command.
	pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;
	pSCIP -> irDriveRegs.bFeaturesReg = 0;
	pSCIP -> irDriveRegs.bSectorCountReg = 1;
	pSCIP -> irDriveRegs.bSectorNumberReg = 1;
	pSCIP -> irDriveRegs.bCylLowReg = 0;
	pSCIP -> irDriveRegs.bCylHighReg = 0;
	
	// Compute the drive number.
	pSCIP -> irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);
	
	// The command can either be IDE identify or ATAPI identify.
	pSCIP -> irDriveRegs.bCommandReg = bIDCmd;
	pSCIP -> bDriveNumber = bDriveNum;
	pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;
	
	return( DeviceIoControl (hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
		(LPVOID) pSCIP,
		sizeof(SENDCMDINPARAMS) - 1,
		(LPVOID) pSCOP,
		sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
		lpcbBytesReturned, NULL) );
}

//
int CGetMachineInfo::ReadPhysicalDriveInNT(void)
{
	int done = FALSE;
	int drive = 0;
	
	for (drive = 0; drive < MAX_IDE_DRIVES; drive++)
	{
		HANDLE hPhysicalDriveIOCTL = 0;
		
		//  Try to get a handle to PhysicalDrive IOCTL, report failure
		//  and exit if can't.
		 //char driveName [256];
		TCHAR driveName [256];
		
		_snprintf_s(driveName, sizeof(driveName), sizeof(driveName), "\\\\.\\PhysicalDrive%d", drive);
		//swprintf_s (driveName, "\\\\.\\PhysicalDrive%d", drive);
 
	//	printf("A1\n");
		
		//  Windows NT, Windows 2000, must have admin rights
		hPhysicalDriveIOCTL = CreateFile (driveName,
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL);
		// if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
		//    printf ("Unable to open physical drive %d, error code: 0x%lX\n",
		//            drive, GetLastError ());
		//printf("A2 [%d][%d]\n", hPhysicalDriveIOCTL, INVALID_HANDLE_VALUE);
		if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
		//if(true)
		{
			GETVERSIONOUTPARAMS VersionParams;
			DWORD               cbBytesReturned = 0;
			//printf("A3\n");
			// Get the version, etc of PhysicalDrive IOCTL
			memset ((void*) &VersionParams, 0, sizeof(VersionParams));
			
			if ( ! DeviceIoControl (hPhysicalDriveIOCTL, DFP_GET_VERSION,
				NULL, 
				0,
				&VersionParams,
				sizeof(VersionParams),
				&cbBytesReturned, NULL) )
			{
				//printf("A4\n");
				// printf ("DFP_GET_VERSION failed for drive %d\n", i);
				// continue;
			}
			//printf("A5\n");
			// If there is a IDE device at number "i" issue commands
			// to the device
			//if (VersionParams.bIDEDeviceMap > 0)
			if(true)
			{
				//printf("A6\n");
				BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
				SENDCMDINPARAMS  scip;
				//SENDCMDOUTPARAMS OutCmd;
				BYTE IdOutCmd [sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
				// Now, get the ID sector for all IDE devices in the system.
				// If the device is ATAPI use the IDE_ATAPI_IDENTIFY command,
				// otherwise use the IDE_ATA_IDENTIFY command
				bIDCmd = (VersionParams.bIDEDeviceMap >> drive & 0x10) ? \
IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;
				
				memset (&scip, 0, sizeof(scip));
				memset (IdOutCmd, 0, sizeof(IdOutCmd));
				//printf("A7\n");
				if ( DoIDENTIFY (hPhysicalDriveIOCTL, 
					&scip, 
					(PSENDCMDOUTPARAMS)&IdOutCmd, 
					(BYTE) bIDCmd,
					(BYTE) drive,
					&cbBytesReturned))
				{
					DWORD diskdata [256];
					int ijk = 0;
					USHORT *pIdSector = (USHORT *)((PSENDCMDOUTPARAMS) IdOutCmd) -> bBuffer;
					//printf("A8\n");
					for (ijk = 0; ijk < 256; ijk++)
						diskdata [ijk] = pIdSector [ijk];
					
					ReturnInfo (drive, diskdata);
					
					done = TRUE;
				}	//printf("A9\n");
			}
			//printf("A10\n");
			CloseHandle (hPhysicalDriveIOCTL);
		}
	}
	//printf("A11\n");
	return done;
}

//
int CGetMachineInfo::ReadDrivePortsInWin9X(void)
{
	int         done            = FALSE;
	HANDLE      VxDHandle       = 0;
	pt_IdeDInfo pOutBufVxD      = 0;
	DWORD       lpBytesReturned = 0;
	
	//  set the thread priority high so that we get exclusive access to the disk
	SetPriorityClass (GetCurrentProcess (), REALTIME_PRIORITY_CLASS);
	
	// 1. Make an output buffer for the VxD
	rt_IdeDInfo info;
	pOutBufVxD = &info;
	
	// *****************
	// KLUDGE WARNING!!!
	// HAVE to zero out the buffer space for the IDE information!
	// If this is NOT done then garbage could be in the memory
	// locations indicating if a disk exists or not.
	ZeroMemory (&info, sizeof(info));
	
	/*
	// 1. Try to load the VxD
	// must use the short file name path to open a VXD file
	char  StartupDirectory [256]  = "";
	char  shortFileNamePath [256] = "";
	char  vxd [256]               = "";
	char* p                       = NULL;
	// get the directory that the exe was started from
	HINSTANCE hInst = AfxGetInstanceHandle(); //WinMain()第一个参数就是hInstance
	GetModuleFileName (hInst, (LPSTR) StartupDirectory, sizeof (StartupDirectory));
	// cut the exe name from string
	p = &(StartupDirectory [strlen (StartupDirectory) - 1]);
	while (p >= StartupDirectory && *p && '\\' != *p) p--;
	*p = '\0';   
	GetShortPathName (StartupDirectory, shortFileNamePath, 2048);
	sprintf (vxd, "\\\\.\\%s\\IDE21201.VXD", shortFileNamePath);
	VxDHandle = CreateFile (vxd, 0, 0, 0,0, FILE_FLAG_DELETE_ON_CLOSE, 0);
	*/

	VxDHandle = CreateFile ("\\\\.\\IDE21201.VXD", 0, 0, 0,0, FILE_FLAG_DELETE_ON_CLOSE, 0);
	if (VxDHandle != INVALID_HANDLE_VALUE)
	{
		// 2. Run VxD function
		DeviceIoControl (VxDHandle, m_cVxDFunctionIdesDInfo,
			0, 0, pOutBufVxD, sizeof(pt_IdeDInfo), &lpBytesReturned, 0);
		
		// 3. Unload VxD
		CloseHandle (VxDHandle);
	}
	else
	{
		//MessageBox (NULL, L"ERROR: Could not open IDE21201.VXD file", TITLE, MB_ICONSTOP);
		//AfxMessageBox("ERROR: Could not open IDE21201.VXD file");
		printf("ERROR: Could not open IDE21201.VXD file");
	}
	
	// 4. Translate and store data
	int i = 0;
	for (i=0; i<8; i++)
	{
		if((pOutBufVxD->DiskExists[i]) && (pOutBufVxD->IDEExists[i/2]))
		{
			DWORD diskinfo [256];
			for (int j = 0; j < 256; j++) 
				diskinfo [j] = pOutBufVxD -> DisksRawInfo [i * 256 + j];
            // process the information for this buffer
			ReturnInfo (i, diskinfo);
			done = TRUE;
		}
	}
	
	//  reset the thread priority back to normal
	// SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_NORMAL);
	SetPriorityClass (GetCurrentProcess (), NORMAL_PRIORITY_CLASS);
	
	return done;
}

//
int CGetMachineInfo::ReadIdeDriveAsScsiDriveInNT(void)
{
	int done = FALSE;
	int controller = 0;
	
	for (controller = 0; controller < 2; controller++)
	{
		HANDLE hScsiDriveIOCTL = 0;
		//char   driveName [256];
		TCHAR   driveName [256];
		
		//  Try to get a handle to PhysicalDrive IOCTL, report failure
		//  and exit if can't.
		_snprintf_s(driveName, sizeof(driveName), sizeof(driveName), "\\\\.\\Scsi%d:", controller);
		//swprintf_s(driveName, L"\\\\.\\Scsi%d:", controller);
		//  Windows NT, Windows 2000, any rights should do
		hScsiDriveIOCTL = CreateFile (driveName,
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL);
		// if (hScsiDriveIOCTL == INVALID_HANDLE_VALUE)
		//    printf ("Unable to open SCSI controller %d, error code: 0x%lX\n",
		//            controller, GetLastError ());
		

		if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
		{
			int drive = 0;
			
			for (drive = 0; drive < 2; drive++)
			{
				char buffer [sizeof (SRB_IO_CONTROL) + SENDIDLENGTH];
				SRB_IO_CONTROL *p = (SRB_IO_CONTROL *) buffer;
				SENDCMDINPARAMS *pin =
					(SENDCMDINPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
				DWORD dummy;
				
				memset (buffer, 0, sizeof (buffer));
				p -> HeaderLength = sizeof (SRB_IO_CONTROL);
				p -> Timeout = 10000;
				p -> Length = SENDIDLENGTH;
				p -> ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
				strncpy_s ((char *) p -> Signature,sizeof((char *)p->Signature), "SCSIDISK", 8); //加了_s
				
				pin -> irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
				pin -> bDriveNumber = drive;
				
				if (DeviceIoControl (hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT, 
					buffer,
					sizeof (SRB_IO_CONTROL) +
					sizeof (SENDCMDINPARAMS) - 1,
					buffer,
					sizeof (SRB_IO_CONTROL) + SENDIDLENGTH,
					&dummy, NULL))
				{
					SENDCMDOUTPARAMS *pOut =
						(SENDCMDOUTPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
					IDSECTOR *pId = (IDSECTOR *) (pOut -> bBuffer);
					if (pId -> sModelNumber [0])
					{
						DWORD diskdata [256];
						int ijk = 0;
						USHORT *pIdSector = (USHORT *) pId;
						
						for (ijk = 0; ijk < 256; ijk++)
							diskdata [ijk] = pIdSector [ijk];
						
						ReturnInfo (controller * 2 + drive, diskdata);
						
						done = TRUE;
					}
				}
			}
			CloseHandle (hScsiDriveIOCTL);
		}
	}
	
	return done;
}
