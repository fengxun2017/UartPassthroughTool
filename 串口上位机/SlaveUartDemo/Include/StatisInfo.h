#ifndef __STATISINFO_H__
#define __STATISINFO_H__

#include "HListBox.h"
#define MAX_CONN_COUNT		8
#define BLE_ADDR_SIZE		6
#define MAX_NAME_SIZE		20


#define UPDATE_TX_COUNT			1
#define UPDATE_RX_COUNT			2
	
#define BLANK_SPACE			"  "
#define CONN_NAME			"  Name: "
#define CONN_ADDR			"Addr: "
#define CONN_ID				"Connid: "
#define RX_COUNT			"RxCount:"
#define TX_COUNT			"TxCount:"
class CStatisInfo
{
private:
	int		m_isValidFlag[MAX_CONN_COUNT];					/**< �������Ƿ���� */
	BYTE	m_byBleAddr[MAX_CONN_COUNT][BLE_ADDR_SIZE];
	BYTE	m_byBleName[MAX_CONN_COUNT][MAX_NAME_SIZE];
	long	m_lRxCount[MAX_CONN_COUNT];						/**< ͳ�Ƹ����ӽ����˶��ٰ� */
	long	m_lTxCount[MAX_CONN_COUNT];						/**< ͳ�Ƹ����ӷ����˶��ٰ� */
	WORD	m_wConnId[MAX_CONN_COUNT];
	
	BYTE	m_byLastBleAddr[BLE_ADDR_SIZE];					/**< ���һ�������豸�ĵ�ַ */
	BYTE	m_byLastBleName[MAX_NAME_SIZE];					/**< ���һ�������豸������ */
	int		m_nLastDeleteIndex;								/**< ѡ�е�Ҫɾ�������� */
public:
	CStatisInfo(void);
	void UpdateConnInfo( WORD connId, CListBox &disp);
	void AddRxCount(WORD wConnId);
	void AddTxCount(WORD wConnId);
	void SetLastBleAddr(BYTE *addr);
	void SetLastBleName(BYTE *name, long nameLen);
	void UpdateCountInfo( WORD connid, CListBox &Disp);
	void UpdateDeleteInfo(WORD connid, CListBox &Disp);
	int GetIndex(WORD connId);
	WORD GetConnId(int index);
};


#endif	/* __STATISINFO_H__ */