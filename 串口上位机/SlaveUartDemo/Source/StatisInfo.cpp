#include"stdafx.h"
#include "StatisInfo.h"
#include "auxiliary.h"

int CStatisInfo::GetIndex(WORD connId)
{
	for (int i = 0; i < MAX_CONN_COUNT; i++ )
	{
		if ( m_isValidFlag[i] )
		{
			if ( connId == m_wConnId[i] )
			{
				return i;
			}
		}
	}
	return 0xff;
} 

WORD CStatisInfo::GetConnId(int index)
{
	if( m_isValidFlag[index] == 1 )
	{
		return  m_wConnId[index];
	}
	return 0xff;
} 

CStatisInfo::CStatisInfo(void)
{
	int i;
	memset(m_isValidFlag, 0x00, sizeof(m_isValidFlag) );
	memset(m_lRxCount, 0x00, sizeof(m_lRxCount));
	memset(m_lTxCount, 0x00, sizeof(m_lTxCount));
	for(i = 0; i < MAX_CONN_COUNT; i++ )
	{
		m_wConnId[i] = 0xFFFF;
	}
	for(i = 0; i < MAX_CONN_COUNT; i++ )
	{
		m_lTxCount[i] = 0;
	}
	for(i = 0; i < MAX_CONN_COUNT; i++ )
	{
		m_lRxCount[i] = 0;
	}
}


void CStatisInfo::AddRxCount(WORD wConnId)
{
	for(int i = 0; i < MAX_CONN_COUNT; i++ )
	{
		if( m_wConnId[i] == wConnId && m_isValidFlag[i] == 1)
		{
			m_lRxCount[i]++;
			return ;
		}
		
	}
}

void CStatisInfo::AddTxCount(WORD wConnId)
{
	for(int i = 0; i < MAX_CONN_COUNT; i++ )
	{
		if( m_wConnId[i] == wConnId && m_isValidFlag[i] == 1)
		{
			m_lTxCount[i]++;
			return ;
		}
	}	
}

void CStatisInfo::SetLastBleAddr(BYTE *addr)
{
	memcpy(m_byLastBleAddr, addr, BLE_ADDR_SIZE);
}

void CStatisInfo::SetLastBleName(BYTE *name, long nameLen)
{
	memcpy(m_byLastBleName, name, nameLen);
}

void CStatisInfo::UpdateConnInfo(WORD connId, CListBox &disp)
{
	int			i;
	CString		strConnInfo="";
	BYTE		szAscAddr[50];
	BYTE		szAscConnid[10];
	BYTE		szconnId[2];
	for ( i = 0 ; i < MAX_CONN_COUNT; i++ )
	{
		if( m_isValidFlag[i] )
		{
			continue;
		}
		break;
	}
	m_isValidFlag[i] = 1;	// 设置数据有效

	m_wConnId[i] = connId;
	memcpy(m_byBleAddr[i], m_byLastBleAddr, BLE_ADDR_SIZE);
	memcpy(m_byBleName[i], m_byLastBleName, MAX_NAME_SIZE);
	Hex2Asc(m_byLastBleAddr, szAscAddr, BLE_ADDR_SIZE);
	szAscAddr[BLE_ADDR_SIZE*2] = 0;
	szconnId[0] = (connId>>8)&0xff;
	szconnId[1] = connId&0xff;
	Hex2Asc(szconnId, szAscConnid, 2);
	szAscConnid[4]=0;
	strConnInfo = strConnInfo+CONN_ID+szAscConnid+CONN_NAME+m_byBleName[i]+ BLANK_SPACE+CONN_ADDR+szAscAddr +BLANK_SPACE+ TX_COUNT+":0"+BLANK_SPACE + RX_COUNT+":0";
	disp.AddString(strConnInfo);
}


void CStatisInfo::UpdateDeleteInfo(WORD connid, CListBox &Disp)
{
	BYTE		szAscConnid[4];
	BYTE		szHexConnid[2];
	int			itemCount;
	CString		content;
	int			index;
	LPCTSTR		pStr;
	char		szAscCount[50];
	CString		strStatisInfo;
	
	szHexConnid[0] = (connid>>8)&0xff;
	szHexConnid[1] = (connid)&0xff;
	Hex2Asc(szHexConnid, szAscConnid, 2);
	memset(szAscCount, 0x00, sizeof(szAscCount));
	
	itemCount = Disp.GetCount();
	strStatisInfo = "";
	for( int i = 0 ; i <itemCount; i++ )
	{
		Disp.GetDlgItemText(i, content);
		index = content.Find(CONN_ID);	
		pStr = content;
		pStr = pStr + index +strlen(CONN_ID);
		if ( memcmp(pStr, szAscConnid, 4)==0 )
		{	
			Disp.DeleteString(i);
			m_isValidFlag[GetIndex(connid)] = 0; // 重置有效标志
		}
	}
}

void CStatisInfo::UpdateCountInfo( WORD connid, CListBox &Disp)
{
	BYTE		szAscConnid[4];
	BYTE		szHexConnid[2];
	int			itemCount;
	CString		content;
	int			index;
	LPCTSTR		pStr;
	char		szAscCount[50];
	CString		strStatisInfo;
	char		tmpBuff[100];
	LPCTSTR		tmp;

	szHexConnid[0] = (connid>>8)&0xff;
	szHexConnid[1] = (connid)&0xff;
	Hex2Asc(szHexConnid, szAscConnid, 2);
	memset(szAscCount, 0x00, sizeof(szAscCount));

	itemCount = Disp.GetCount();
	strStatisInfo = "";
	for( int i = 0 ; i <itemCount; i++ )
	{
		Disp.GetText(i, content);
		index = content.Find(CONN_ID);	
		pStr = content;
		pStr = pStr + index +strlen(CONN_ID);
		if ( memcmp(pStr, szAscConnid, 4)==0 )
		{	
			sprintf(szAscCount, "TxCount:%d   RxCount:%d ",m_lTxCount[GetIndex(connid)], m_lRxCount[GetIndex(connid)]);
			index = content.Find(TX_COUNT);
			memcpy(tmpBuff, (LPCTSTR)content, index);
			tmpBuff[index] = 0;
			tmp = tmpBuff;
			strStatisInfo = strStatisInfo+ tmp + szAscCount;
			Disp.DeleteString(i);
			Disp.InsertString(i, strStatisInfo);
			return ;
		}
	}
	
}
