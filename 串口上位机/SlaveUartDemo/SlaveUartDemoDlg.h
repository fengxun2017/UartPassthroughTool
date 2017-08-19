// SlaveUartDemoDlg.h : header file
//

#if !defined(AFX_SLAVEUARTDEMODLG_H__65293F66_8A3D_440A_8CD7_492EAC8E7E8A__INCLUDED_)
#define AFX_SLAVEUARTDEMODLG_H__65293F66_8A3D_440A_8CD7_492EAC8E7E8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSlaveUartDemoDlg dialog
#include "UartHandle.h"

#define MAX_SLAVE_DEVICE		8
#define PERIOD_SEND_TIMER		1


class CSlaveUartDemoDlg : public CDialog
{
// Construction
public:
	BYTE		m_byAvailableCom[MAX_SLAVE_DEVICE][50];
	FILE		*m_fpLog[MAX_SLAVE_DEVICE];
	int			m_nPeriodSendTimer[MAX_SLAVE_DEVICE];
	CMyUart		m_CUartControl[MAX_SLAVE_DEVICE];


	void InitDlg(void);
public:
	CSlaveUartDemoDlg(CWnd* pParent = NULL);	// standard constructor
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);  

// Dialog Data
	//{{AFX_DATA(CSlaveUartDemoDlg)
	enum { IDD = IDD_SLAVEUARTDEMO_DIALOG };
	CButton	m_CCheckIsPeriod[MAX_SLAVE_DEVICE];
	CRichEditCtrl	m_CRicheditRxData[MAX_SLAVE_DEVICE];
	CEdit	m_CEditTxPeriod[MAX_SLAVE_DEVICE];
	CEdit	m_CEditTxData[MAX_SLAVE_DEVICE];
	CEdit	m_CEditTxCount[MAX_SLAVE_DEVICE];
	CEdit	m_CEditRxCount[MAX_SLAVE_DEVICE];
	CComboBox	m_CComboComList[MAX_SLAVE_DEVICE];
	CComboBox	m_CComboBuadList[MAX_SLAVE_DEVICE];
	CButton	m_CButtonOpenCom[MAX_SLAVE_DEVICE];
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlaveUartDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSlaveUartDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonComopen0();
	afx_msg void OnButtonSenddata0();
	afx_msg void OnButtonClearrx0();
	afx_msg void OnCheckIsperiodsend0();
	afx_msg void OnSelchangeComboBaudlist0();
	afx_msg void OnSelchangeComboComlist0();
	afx_msg void OnChangeEditTxperiod0();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLAVEUARTDEMODLG_H__65293F66_8A3D_440A_8CD7_492EAC8E7E8A__INCLUDED_)
