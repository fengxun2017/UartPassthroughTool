#ifndef __UARTHANDLE_H__
#define __UARTHANDLE_H__


#define CMD_UART_ERR                        0xff

#define CMD_QUERY_DEV_LIST                  0x01
#define CMD_CONN_DEV                        0x02
#define CMD_DISCONN_DEV                     0x03
#define CMD_SEND_DATA                       0x04
#define CMD_CFG_UUIDS						0x05

#define CMD_ACK								0x80
#define CMD_DEVLIST_RSP						0x81
#define CMD_CONN_RSP						0x82
#define CMD_DISCONN_RSP						0x83
#define CMD_SEND_RSP						0x84
#define CMD_CFG_UUIDS_RSP					0x85

#define CMD_BLE_RECV_DATA					0x86


#define CMD_PARAM_LEN_POS       	(4)
#define CMD_TYPE_POS            	(2)	
#define CMD_ID_POS              	(3)
#define CMD_PARAMS_START_POS    	(6)

#define CMD_HEAD_LEN            	(6)//0xff  0xaa  CMD_TYPE  CMD_ID  PAR_LEN(H) PAR_LEN(L)

#define DISP_NAME					"   Name: "
#define DISP_ADDR					"Addr: "

#define UART_OPENED					1
#define UART_CLOSED					0

#define MASTER_UNCONN					0				
#define	MASTER_CFG_UUID					1
#define MASTER_CONNED					2
 

#define INVALID_CONNID				0xff
class CMyUart
{
private:
	int			m_nSelectedCom;
	DWORD		m_dwBaud;	
	HANDLE		m_hComHandle;
	long		m_lFrameIndex;		// 指示当前一帧数据的接收偏移。
	BYTE		m_szFrameData[1024];// FF AA type cmd lH ll
	long		m_lFrameLen;		// 收到的一帧长度
	BOOL		m_isDevList;		// 是否要获取广播设备列表
	BOOL		m_isNewFrame;		// 是否收到一个完整帧
	BOOL		m_isStartRecv;		// 是否开始接收帧，收到FFAA有效头才开始
	int			m_nUartState;
	int			m_nMasterState;		// 主机状态
public :
	CMyUart(void);
	
	HANDLE GetUartHandle(void);
	void SetUartComNum(int num);
	void SetUartComBaud(DWORD baud);
	void SendUartData( BYTE *szData, LONG len);
	int OpenUart();
	BOOL CloseUart();
	int QuickEnumCom(CComboBox &comList, BYTE *AvailableComs);
	int GetAvailableCom(CComboBox &comList, BYTE *AvailableComs);	
	long PacketFrameData(BYTE opcode, BYTE *src, BYTE *packet, long srcLen);
	void HandleRecvByte( BYTE data);
	void GetFrameData(BYTE *buff, long *len);
	BOOL IsDevListRsp(void);
	BOOL IsNewConnRsp(void);
	BOOL IsDisConnRsp(void);
	BOOL IsNewRecvData(void);
	BOOL IsSendDone(void);

	WORD GetConnid(void);
	void ClearFrameFlag(void);
	BOOL IsUartOpen(void);
	void SetUartStat(int state);
	void SetMasterState(int state);
	int IsMasterCfgedUUID(void);
	int IsMasterConnected(void);
};




#endif /* __UARTHANDLE_H__ */
