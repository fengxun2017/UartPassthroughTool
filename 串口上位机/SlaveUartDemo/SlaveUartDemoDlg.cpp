// SlaveUartDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SlaveUartDemo.h"
#include "SlaveUartDemoDlg.h"
#include "UartHandle.h"
#include "auxiliary.h"
#include "HandleAllEvent.h"
#include <Dbt.h>  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlaveUartDemoDlg dialog

CSlaveUartDemoDlg::CSlaveUartDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSlaveUartDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSlaveUartDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSlaveUartDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSlaveUartDemoDlg)
	DDX_Control(pDX, IDC_CHECK_ISPERIODSEND0, m_CCheckIsPeriod[0]);
	DDX_Control(pDX, IDC_CHECK_ISPERIODSEND1, m_CCheckIsPeriod[1]);
	DDX_Control(pDX, IDC_CHECK_ISPERIODSEND2, m_CCheckIsPeriod[2]);
	DDX_Control(pDX, IDC_CHECK_ISPERIODSEND3, m_CCheckIsPeriod[3]);
	DDX_Control(pDX, IDC_CHECK_ISPERIODSEND4, m_CCheckIsPeriod[4]);
	DDX_Control(pDX, IDC_CHECK_ISPERIODSEND5, m_CCheckIsPeriod[5]);
	DDX_Control(pDX, IDC_CHECK_ISPERIODSEND6, m_CCheckIsPeriod[6]);
	DDX_Control(pDX, IDC_CHECK_ISPERIODSEND7, m_CCheckIsPeriod[7]);

	DDX_Control(pDX, IDC_RICHEDIT_RXDATA0, m_CRicheditRxData[0]);
	DDX_Control(pDX, IDC_RICHEDIT_RXDATA1, m_CRicheditRxData[1]);
	DDX_Control(pDX, IDC_RICHEDIT_RXDATA2, m_CRicheditRxData[2]);
	DDX_Control(pDX, IDC_RICHEDIT_RXDATA3, m_CRicheditRxData[3]);
	DDX_Control(pDX, IDC_RICHEDIT_RXDATA4, m_CRicheditRxData[4]);
	DDX_Control(pDX, IDC_RICHEDIT_RXDATA5, m_CRicheditRxData[5]);
	DDX_Control(pDX, IDC_RICHEDIT_RXDATA6, m_CRicheditRxData[6]);
	DDX_Control(pDX, IDC_RICHEDIT_RXDATA7, m_CRicheditRxData[7]);

	DDX_Control(pDX, IDC_EDIT_TXPERIOD0, m_CEditTxPeriod[0]);
	DDX_Control(pDX, IDC_EDIT_TXPERIOD1, m_CEditTxPeriod[1]);
	DDX_Control(pDX, IDC_EDIT_TXPERIOD2, m_CEditTxPeriod[2]);
	DDX_Control(pDX, IDC_EDIT_TXPERIOD3, m_CEditTxPeriod[3]);
	DDX_Control(pDX, IDC_EDIT_TXPERIOD4, m_CEditTxPeriod[4]);
	DDX_Control(pDX, IDC_EDIT_TXPERIOD5, m_CEditTxPeriod[5]);
	DDX_Control(pDX, IDC_EDIT_TXPERIOD6, m_CEditTxPeriod[6]);
	DDX_Control(pDX, IDC_EDIT_TXPERIOD7, m_CEditTxPeriod[7]);

	DDX_Control(pDX, IDC_EDIT_TXDATA0, m_CEditTxData[0]);
	DDX_Control(pDX, IDC_EDIT_TXDATA1, m_CEditTxData[1]);
	DDX_Control(pDX, IDC_EDIT_TXDATA2, m_CEditTxData[2]);
	DDX_Control(pDX, IDC_EDIT_TXDATA3, m_CEditTxData[3]);
	DDX_Control(pDX, IDC_EDIT_TXDATA4, m_CEditTxData[4]);
	DDX_Control(pDX, IDC_EDIT_TXDATA5, m_CEditTxData[5]);
	DDX_Control(pDX, IDC_EDIT_TXDATA6, m_CEditTxData[6]);
	DDX_Control(pDX, IDC_EDIT_TXDATA7, m_CEditTxData[7]);

	DDX_Control(pDX, IDC_EDIT_TXCOUNT0, m_CEditTxCount[0]);
	DDX_Control(pDX, IDC_EDIT_TXCOUNT1, m_CEditTxCount[1]);
	DDX_Control(pDX, IDC_EDIT_TXCOUNT2, m_CEditTxCount[2]);
	DDX_Control(pDX, IDC_EDIT_TXCOUNT3, m_CEditTxCount[3]);
	DDX_Control(pDX, IDC_EDIT_TXCOUNT4, m_CEditTxCount[4]);
	DDX_Control(pDX, IDC_EDIT_TXCOUNT5, m_CEditTxCount[5]);
	DDX_Control(pDX, IDC_EDIT_TXCOUNT6, m_CEditTxCount[6]);
	DDX_Control(pDX, IDC_EDIT_TXCOUNT7, m_CEditTxCount[7]);

	DDX_Control(pDX, IDC_EDIT_RXCOUNT0, m_CEditRxCount[0]);
	DDX_Control(pDX, IDC_EDIT_RXCOUNT1, m_CEditRxCount[1]);
	DDX_Control(pDX, IDC_EDIT_RXCOUNT2, m_CEditRxCount[2]);
	DDX_Control(pDX, IDC_EDIT_RXCOUNT3, m_CEditRxCount[3]);
	DDX_Control(pDX, IDC_EDIT_RXCOUNT4, m_CEditRxCount[4]);
	DDX_Control(pDX, IDC_EDIT_RXCOUNT5, m_CEditRxCount[5]);
	DDX_Control(pDX, IDC_EDIT_RXCOUNT6, m_CEditRxCount[6]);
	DDX_Control(pDX, IDC_EDIT_RXCOUNT7, m_CEditRxCount[7]);

	DDX_Control(pDX, IDC_COMBO_COMLIST0, m_CComboComList[0]);
	DDX_Control(pDX, IDC_COMBO_COMLIST1, m_CComboComList[1]);
	DDX_Control(pDX, IDC_COMBO_COMLIST2, m_CComboComList[2]);
	DDX_Control(pDX, IDC_COMBO_COMLIST3, m_CComboComList[3]);
	DDX_Control(pDX, IDC_COMBO_COMLIST4, m_CComboComList[4]);
	DDX_Control(pDX, IDC_COMBO_COMLIST5, m_CComboComList[5]);
	DDX_Control(pDX, IDC_COMBO_COMLIST6, m_CComboComList[6]);
	DDX_Control(pDX, IDC_COMBO_COMLIST7, m_CComboComList[7]);

	DDX_Control(pDX, IDC_COMBO_BAUDLIST0, m_CComboBuadList[0]);
	DDX_Control(pDX, IDC_COMBO_BAUDLIST1, m_CComboBuadList[1]);
	DDX_Control(pDX, IDC_COMBO_BAUDLIST2, m_CComboBuadList[2]);
	DDX_Control(pDX, IDC_COMBO_BAUDLIST3, m_CComboBuadList[3]);
	DDX_Control(pDX, IDC_COMBO_BAUDLIST4, m_CComboBuadList[4]);
	DDX_Control(pDX, IDC_COMBO_BAUDLIST5, m_CComboBuadList[5]);
	DDX_Control(pDX, IDC_COMBO_BAUDLIST6, m_CComboBuadList[6]);
	DDX_Control(pDX, IDC_COMBO_BAUDLIST7, m_CComboBuadList[7]);

	DDX_Control(pDX, IDC_BUTTON_COMOPEN0, m_CButtonOpenCom[0]);
	DDX_Control(pDX, IDC_BUTTON_COMOPEN1, m_CButtonOpenCom[1]);
	DDX_Control(pDX, IDC_BUTTON_COMOPEN2, m_CButtonOpenCom[2]);
	DDX_Control(pDX, IDC_BUTTON_COMOPEN3, m_CButtonOpenCom[3]);
	DDX_Control(pDX, IDC_BUTTON_COMOPEN4, m_CButtonOpenCom[4]);
	DDX_Control(pDX, IDC_BUTTON_COMOPEN5, m_CButtonOpenCom[5]);
	DDX_Control(pDX, IDC_BUTTON_COMOPEN6, m_CButtonOpenCom[6]);
	DDX_Control(pDX, IDC_BUTTON_COMOPEN7, m_CButtonOpenCom[7]);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSlaveUartDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSlaveUartDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_COMOPEN0, OnButtonComopen0)
	ON_BN_CLICKED(IDC_BUTTON_SENDDATA0, OnButtonSenddata0)
	ON_BN_CLICKED(IDC_BUTTON_CLEARRX0, OnButtonClearrx0)
	ON_BN_CLICKED(IDC_CHECK_ISPERIODSEND0, OnCheckIsperiodsend0)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUDLIST0, OnSelchangeComboBaudlist0)
	ON_CBN_SELCHANGE(IDC_COMBO_COMLIST0, OnSelchangeComboComlist0)
	ON_EN_CHANGE(IDC_EDIT_TXPERIOD0, OnChangeEditTxperiod0)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





#define BAUD_NUM	3
LPCTSTR strBaud[BAUD_NUM]={"57600","115200", "9600"};
int		nBaudArray[BAUD_NUM] = {CBR_57600, CBR_115200, CBR_9600 };
void CSlaveUartDemoDlg::InitDlg()
{
	int			ret;
	for ( int i = 0; i < 8; i++ ){
		ret = m_CUartControl[i].GetAvailableCom(m_CComboComList[i], m_byAvailableCom[i]);
		if( 1 == ret )
		{
			m_CComboComList[i].SetCurSel(0);
			m_CUartControl[i].SetUartComNum(m_byAvailableCom[i][m_CComboComList[i].GetCurSel()]);
		}
		
		m_CComboBuadList[i].ResetContent();
		for( int i = 0; i < BAUD_NUM; i++ )
		{
			m_CComboBuadList[i].AddString(strBaud[i]);
		}
		m_CComboBuadList[i].SetCurSel(0);
		m_CUartControl[i].SetUartComBaud(nBaudArray[m_CComboBuadList[i].GetCurSel()]);
		
		m_nPeriodSendTimer[i] = PERIOD_SEND_TIMER;
		m_CEditRxCount[i].SetWindowText("0");
		m_CEditTxCount[i].SetWindowText("0");
	}
}


BOOL CSlaveUartDemoDlg::OnDeviceChange(UINT nEventType,DWORD dwData)
{
	int ret;
	int i;
	//DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;
	switch (nEventType)
	{
	case DBT_DEVICEREMOVECOMPLETE://移除设备
	case DBT_DEVICEARRIVAL://添加设备
		for(i = 0; i < MAX_SLAVE_DEVICE; i++ )
		{			
			ret = m_CUartControl[i].GetAvailableCom(m_CComboComList[i], m_byAvailableCom[i]);
			if( 1 == ret )
			{
				m_CComboComList[i].SetCurSel(0);
				m_CUartControl[i].SetUartComNum(m_byAvailableCom[i][m_CComboComList[i].GetCurSel()]);
			}	
		}
		break;
		
	default:
		break;
	}
	
	return TRUE;
	
}
/////////////////////////////////////////////////////////////////////////////
// CSlaveUartDemoDlg message handlers

BOOL CSlaveUartDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitDlg();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSlaveUartDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSlaveUartDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSlaveUartDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

typedef struct BlkThreadInfoTag
{
	unsigned char		m_u1UartIndex;
	CSlaveUartDemoDlg	*m_pThisDlg;
}BlkThreadInfo;

UINT ReadProc(LPVOID lpVoid)
{
	BlkThreadInfo	*pInfo;

	pInfo = (BlkThreadInfo *)lpVoid;
	UartReadProc(pInfo->m_u1UartIndex, pInfo->m_pThisDlg);	
	return 0;
}



void CSlaveUartDemoDlg::OnButtonComopen0() 
{
	// TODO: Add your control notification handler code here
	int					ret;
	BlkThreadInfo		threadInfo;
	WORD				id;
	int					index;
	
	id = LOWORD(GetCurrentMessage()->wParam);
	index = GetControlIndex(id);

	if ( !m_CUartControl[index].IsUartOpen() )
	{
		ret = m_CUartControl[index].OpenUart();
		if ( 0 != ret )
		{
			m_CButtonOpenCom[index].SetWindowText("Close");
			m_CUartControl[index].SetUartStat(UART_OPENED);
			threadInfo.m_u1UartIndex = index;
			threadInfo.m_pThisDlg = this;
			AfxBeginThread(ReadProc, &threadInfo);
		}
	}
	else
	{	
		m_CUartControl[index].CloseUart();
		m_CButtonOpenCom[index].SetWindowText("Open");
		m_CUartControl[index].SetUartStat(UART_CLOSED);
	}
	// TODO: Add your control notification handler code here
	
}

void CSlaveUartDemoDlg::OnButtonSenddata0() 
{
	// TODO: Add your control notification handler code here
	
}

void CSlaveUartDemoDlg::OnButtonClearrx0() 
{
	// TODO: Add your control notification handler code here
	
}

void CSlaveUartDemoDlg::OnCheckIsperiodsend0() 
{
	// TODO: Add your control notification handler code here
	
}

void CSlaveUartDemoDlg::OnSelchangeComboBaudlist0() 
{
	// TODO: Add your control notification handler code here
	
}

void CSlaveUartDemoDlg::OnSelchangeComboComlist0() 
{
	// TODO: Add your control notification handler code here
	
}

void CSlaveUartDemoDlg::OnChangeEditTxperiod0() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
