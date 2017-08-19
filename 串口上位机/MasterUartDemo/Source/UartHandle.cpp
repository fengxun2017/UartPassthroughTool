#include <string.h>
#include"stdafx.h"
#include "UartHandle.h"
#include "auxiliary.h"

CMyUart::CMyUart(void)
{
	m_hComHandle = INVALID_HANDLE_VALUE;
	m_isDevList = FALSE;
	m_lFrameLen = 0;
	m_lFrameIndex = 0;
	m_isNewFrame = FALSE;
	m_isStartRecv = FALSE;
	m_nUartState = FALSE;
	m_nMasterState = MASTER_UNCONN;
}

void CMyUart::SetUartComNum(int num)
{
	m_nSelectedCom = num;
}

void CMyUart::SetUartComBaud(DWORD baud)
{
	m_dwBaud = baud;
}

BOOL CMyUart::CloseUart()
{
	return CloseHandle(m_hComHandle);
}
// 成功返回1 ，失败返回0
int CMyUart::OpenUart()
{
	int				nSelecetedCom;
	BOOL			byRet;
	DWORD			dwBaud;
	CString			strCom;
	DCB				comDcb;
	COMMTIMEOUTS	comTimeouts;
	DWORD			lastError;
	nSelecetedCom = m_nSelectedCom;
	dwBaud = m_dwBaud;
	strCom.Format(_T("\\\\.\\COM%d"), nSelecetedCom);
	
	m_hComHandle = CreateFile(strCom, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (m_hComHandle == INVALID_HANDLE_VALUE)
	{
		DWORD dwError = GetLastError();
		
		if (dwError == ERROR_ACCESS_DENIED)
		{
			AfxMessageBox("串口被占用！");
			return 0;
		}
		else
		{
			AfxMessageBox("串口打开失败！");
			return 0;
		}
	}
	else
	{
		comDcb.DCBlength = sizeof(comDcb);
		byRet = GetCommState(m_hComHandle, &comDcb);
		if(!byRet)
		{
			return 0;
		}
		comDcb.BaudRate  = dwBaud;
		comDcb.ByteSize = 8;
		comDcb.StopBits = 0;
		comDcb.Parity = NOPARITY;
		comDcb.fBinary = TRUE;
		byRet = SetCommState(m_hComHandle, &comDcb);
		if ( !byRet )
		{
			lastError = GetLastError();
			return 0;
		}
		comTimeouts.ReadIntervalTimeout = MAXDWORD;
		comTimeouts.ReadTotalTimeoutMultiplier = 0;
		comTimeouts.ReadTotalTimeoutConstant = 0;
		comTimeouts.WriteTotalTimeoutConstant = 0;
		comTimeouts.WriteTotalTimeoutMultiplier = 0;
		byRet = SetCommTimeouts(m_hComHandle, &comTimeouts);
		if(!byRet) return 0;
		byRet = SetupComm(m_hComHandle, 4096,4096);
		if(!byRet)
		{
			return 0;
		}
		byRet = PurgeComm(m_hComHandle,PURGE_TXCLEAR|PURGE_RXCLEAR);
	}
	return 1;
}

//	注册表打开失败返回-1，有大于一个存在的串口则返回1，否则返回0
int CMyUart::QuickEnumCom(CComboBox &comList, BYTE *AvailableComs)
{
	HKEY		hKey = 0x00;
	DWORD		dwRet;
	char		szClass[MAX_PATH] = {0x00};
	DWORD		dwClassSize = MAX_PATH;
	DWORD		dwSubKeys = 0x00;
	DWORD		dwLongestSubkeySize;
	DWORD		dwLongestSubClassString;
	DWORD		dwValueSize;
	DWORD		dwLongestValueName;
	DWORD		dwLongestMaxValueData;
	DWORD		dwSecurityDescriptor;
	FILETIME	ftLastWriteTime;
	int			nCurSel = 0x00;
	
	comList.ResetContent();
	if ( ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0x00, KEY_READ, &hKey) )
	{
		RegCloseKey(hKey);	
		return -1;
	}
	
	dwRet = RegQueryInfoKey(
		hKey,                   // key handle
		szClass,               // buffer for class name
		&dwClassSize,          // size of class string
		NULL,                   // reserved
		&dwSubKeys,              // number of subkeys
		&dwLongestSubkeySize,           // longest subkey size
		&dwLongestSubClassString,           // longest class string
		&dwValueSize,               // number of values for this key
		&dwLongestValueName,           // longest value name
		&dwLongestMaxValueData,        // longest value data
		&dwSecurityDescriptor,  // security descriptor
		&ftLastWriteTime);      // last write time
	if ( dwValueSize > 0x00 )
	{
		DWORD		i;
		char		szValue[MAX_PATH] = {0x00};
		DWORD		dwSize = MAX_PATH;
		CString		strName;
		BYTE		szDSName[100] = {0x00};
		DWORD		dwValueType = 0;
		DWORD		dwDSNNameSize = 100;
		for ( i = 0x00, dwRet = ERROR_SUCCESS; i < dwValueSize; i++ )
		{
			dwSize = sizeof(szValue);
			memset(szValue, 0x00, dwSize);
			if ( ERROR_SUCCESS == RegEnumValue(hKey, i, szValue, &dwSize, NULL, NULL, NULL, NULL) )
			{
			
				dwDSNNameSize = 10;
				memset(szDSName, 0x00, dwDSNNameSize);
				dwValueType = 0x00; 
				if (ERROR_SUCCESS == RegQueryValueEx(hKey, (LPCTSTR)szValue, NULL, &dwValueType, szDSName, &dwDSNNameSize) )
				{
					comList.InsertString(nCurSel, (LPCTSTR)szDSName);
					AvailableComs[nCurSel] = atoi((const char *)(szDSName+3));
					nCurSel++;
				}
				
			}
		}
	}
	
	if( nCurSel>0 )
	{
		return 1;
	}
	return 0;
}

//	有大于一个存在的串口则返回1，否则返回0
int CMyUart::GetAvailableCom(CComboBox &comList, BYTE *AvailableComs)
{	

	int ret;

	ret = QuickEnumCom(comList, AvailableComs);
	if( ret == 1 )
	{
		// 通过注册表枚举的方式成功了，直接返回
		return ret;
	}
	// 否则一个个遍历枚举

	BOOL bSuccess = FALSE;
	int count = 0;
	//因为至多有255个串口，所以依次检查各串口是否存在
	//如果能打开某一串口，或打开串口不成功，但返回的是 ERROR_ACCESS_DENIED错误信息，
	//都认为串口存在，只不过后者表明串口已经被占用
	//否则串口不存在
	comList.ResetContent();
	for (int i=1; i<100; i++)
	{
		//Form the Raw device name
		CString sPort;
		sPort.Format(_T("\\\\.\\COM%d"), i);
		bSuccess = FALSE;
		//Try to open the port
		HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if (hPort == INVALID_HANDLE_VALUE)
		{
			DWORD dwError = GetLastError();
			
            if (dwError == ERROR_ACCESS_DENIED)
			{
				bSuccess = TRUE;
			}
		}
		else
		{
			//The port was opened successfully
			bSuccess = TRUE;
			CloseHandle(hPort);
		}
		
		//Add the port number to the array which will be returned
		if (bSuccess)
		{
			sPort = sPort.Mid(4);
			comList.AddString(sPort);   //所有存在的串口
			AvailableComs[count] = i;
			count++;
		}
	}
	if ( 0 == count )
    {//若找不到可用串口则禁用“打开串口”功能
		return 0;
    }
    return 1;
}

long CMyUart::PacketFrameData(BYTE opcode, BYTE *src, BYTE *packet, long srcLen)
{
	long i = 0; 
	if ( NULL != packet )
	{
		packet[i++] = 0xFF;
		packet[i++] = 0xAA;
		packet[i++] = 0x00;
		packet[i++] = opcode;
		packet[i++] = (srcLen>>8)&0xff;
		packet[i++] = srcLen&0xff;
		for ( long j = 0; j < srcLen; j++ )
		{
			packet[i++] = src[j];
		}
	}
	return i;
}

void CMyUart::SendUartData( BYTE *szData, LONG len)
{
	if ( INVALID_HANDLE_VALUE == m_hComHandle )
	{
		return ;
	}
	DWORD			dwNumWrite;
	OVERLAPPED		ov;
	LOGI("Send :");
	LOG_DATA(szData,len);
	ov.Internal = 0;
	ov.InternalHigh = 0;
	ov.Offset = 0;
	ov.OffsetHigh = 0;
	ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL );
	if ( !WriteFile(m_hComHandle, szData, len, &dwNumWrite, &ov) )
	{
		if ( GetLastError() == ERROR_IO_PENDING )
		{
			while ( !GetOverlappedResult(m_hComHandle, &ov, &dwNumWrite, FALSE) )
			{
				if ( GetLastError() == ERROR_IO_INCOMPLETE )
				{
					continue;
				}
			}
		}
	}
	ResetEvent(ov.hEvent);

}

HANDLE CMyUart::GetUartHandle(void)
{
	return m_hComHandle;
}

BOOL CMyUart::IsDevListRsp(void)
{
	if( m_isNewFrame )
	{
		if(m_szFrameData[3] == CMD_DEVLIST_RSP )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMyUart::IsNewConnRsp(void)
{
	if( m_isNewFrame )
	{
		if(m_szFrameData[3] == CMD_CONN_RSP )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMyUart::IsSendDone(void)
{
	if( m_isNewFrame )
	{
		if(m_szFrameData[3] == CMD_SEND_RSP )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMyUart::IsNewRecvData(void)
{
	if( m_isNewFrame )
	{
		if(m_szFrameData[3] == CMD_BLE_RECV_DATA )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMyUart::IsDisConnRsp(void)
{
	if( m_isNewFrame )
	{
		if(m_szFrameData[3] == CMD_DISCONN_RSP )
		{
			return TRUE;
		}
	}
	return FALSE;
}

WORD CMyUart::GetConnid(void)
{
	WORD connid;

	if( m_isNewFrame )
	{
			connid = (WORD)((m_szFrameData[6]<<8)& 0xff00) + m_szFrameData[7];		
	}
	return connid;
}

// buffLen为数组大小，返回实际获取的大小
void CMyUart::GetFrameData(BYTE *buff, long *buffLen)
{
	long retLen;

	
	if ( (NULL != buff) && (NULL != buffLen) )
	{
		if( m_lFrameLen > 0 && m_isNewFrame)
		{
			retLen = m_lFrameLen>*buffLen?*buffLen:m_lFrameLen;
			for( long i = 0; i < retLen; i++ )
			{
				buff[i] = m_szFrameData[i];
			}
			*buffLen = retLen;
		}
		else
		{
			*buffLen = 0;
		}
	}
}

// windows上层的串口数据都是Buff中的，所以传进来的数组中可能不只一帧数据，
// 所以该函数会返回处理掉的数据，上层需要对剩余数据继续调用该函数。
void CMyUart::HandleRecvByte(BYTE uartData)
{

		if ( FALSE == m_isStartRecv )
		{
			if ( ( 0xff == uartData ) && ( 0 == m_lFrameIndex) )
			{
				m_szFrameData[m_lFrameIndex++] = uartData;
			}
			else if( (0xff == uartData) && (1 == m_lFrameIndex) )
			{		
				m_lFrameIndex = 0;
				m_szFrameData[m_lFrameIndex++] = uartData;
			}		
			else if ( ( 1 == m_lFrameIndex ) && ( 0xaa == uartData) && ( 0xff == m_szFrameData[0]) )
			{
				m_isStartRecv = TRUE;
				m_szFrameData[m_lFrameIndex++] = uartData;
				
			}
			else
			{
				m_lFrameIndex = 0;
			}
		}
		else
		{	
			
			if ( CMD_PARAM_LEN_POS == m_lFrameIndex )
			{
				m_lFrameLen = uartData<<8;
				
			}
			if ( (CMD_PARAM_LEN_POS+1) == m_lFrameIndex )
			{
				m_lFrameLen += uartData;
			}
			
			m_szFrameData[m_lFrameIndex++] = uartData;
			
			if ( (m_lFrameLen+CMD_HEAD_LEN) == m_lFrameIndex )
			{
				m_lFrameLen = m_lFrameIndex;
				m_lFrameIndex = 0;
				m_isStartRecv = FALSE;
				m_isNewFrame = TRUE;
				
				return ;
			}
		}	
}

void CMyUart::ClearFrameFlag(void)
{
	m_isNewFrame = FALSE;
}

BOOL CMyUart::IsUartOpen(void)
{
	if( m_nUartState == UART_OPENED )
	{
		return TRUE;
	}
	return FALSE;
}

void CMyUart::SetUartStat(int state)
{
	m_nUartState = state;
}


void CMyUart::SetMasterState(int state)
{
	m_nMasterState = state;
}
int CMyUart::IsMasterCfgedUUID()
{
	if ( m_nMasterState >= MASTER_CFG_UUID)
	{
		return 1;
	}
	return 0;
}

int CMyUart::IsMasterConnected()
{
	if ( m_nMasterState >= MASTER_CONNED )
	{
		return 1;
	}
	return 0;
}

