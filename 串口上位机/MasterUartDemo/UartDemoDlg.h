// UartDemoDlg.h : header file
//

#if !defined(AFX_UARTDEMODLG_H__D50E4649_2DFB_4FF8_A3AB_1E4A3A5CCE5F__INCLUDED_)
#define AFX_UARTDEMODLG_H__D50E4649_2DFB_4FF8_A3AB_1E4A3A5CCE5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "UartHandle.h"
#include "StatisInfo.h"
#include "HListBox.h"
#include "MyEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CUartDemoDlg dialog

#define PERIOD_SEND_TIMER		1

class CUartDemoDlg : public CDialog
{
// Construction
public:
	BYTE		m_byAvailableCom[50];
	FILE		*m_fpLog;
	int			m_nPeriodSendTimer;
	HANDLE		m_hTerminateSignal;
	HANDLE		m_hCommRecvSignal;
	int			m_nExitCommWaitThread;
	void InitDlg(void);
	void DispDevList(BYTE *frameBuff, long len);
	void SendTxEditData(void);
public:
	CUartDemoDlg(CWnd* pParent = NULL);	// standard constructor
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);  

// Dialog Data
	//{{AFX_DATA(CUartDemoDlg)
	enum { IDD = IDD_UARTDEMO_DIALOG };
	CButton	m_CCheckOk;
	CMyEdit	m_CEditSendPeriod;
	CListBox	m_connList;
	CButton	m_openUart;
	CEdit	m_srvUUID;
	CEdit	m_txUUID;
	CEdit	m_rxUUID;
	CRichEditCtrl	m_RxData;
	CEdit	m_CEditTxData;
	CComboBox	m_CBaudList;
	CComboBox	m_CComList;
	CMyUart		m_CUartControl;
	CStatisInfo	m_CStatisInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUartDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUartDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpencom();
	afx_msg void OnButtonSend();
	afx_msg void OnSelchangeCOMBOComList();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonSearchDev();
	afx_msg void OnSelchangeCOMBOBaudList();
	afx_msg void OnButtonCfgUuid();
	afx_msg void OnBUTTONRXClear();
	afx_msg void OnDblclkListConnlist();
	afx_msg void OnCheckIssendperiod();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChangeEditSendPeriod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UARTDEMODLG_H__D50E4649_2DFB_4FF8_A3AB_1E4A3A5CCE5F__INCLUDED_)
