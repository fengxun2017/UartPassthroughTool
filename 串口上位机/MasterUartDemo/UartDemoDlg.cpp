// UartDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UartDemo.h"
#include "UartDemoDlg.h"
#include "UartHandle.h"
#include "auxiliary.h"
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
// CUartDemoDlg dialog

CUartDemoDlg::CUartDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUartDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUartDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUartDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUartDemoDlg)
	DDX_Control(pDX, IDC_CHECK_ISSENDPERIOD, m_CCheckOk);
	DDX_Control(pDX, IDC_EDIT_SEND_PERIOD, m_CEditSendPeriod);
	DDX_Control(pDX, IDC_LIST_CONNLIST, m_connList);
	DDX_Control(pDX, IDC_BUTTON_OPENCOM, m_openUart);
	DDX_Control(pDX, IDC_EDIT_SRVUUID, m_srvUUID);
	DDX_Control(pDX, IDC_EDIT_TXUUID, m_txUUID);
	DDX_Control(pDX, IDC_EDIT_RXUUID, m_rxUUID);
	DDX_Control(pDX, IDC_RICHEDIT_RXDARA, m_RxData);
	DDX_Control(pDX, IDC_EDIT_TXDATA, m_CEditTxData);
	DDX_Control(pDX, IDC_COMBO_BaudList, m_CBaudList);
	DDX_Control(pDX, IDC_COMBO_ComList, m_CComList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUartDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CUartDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM, OnButtonOpencom)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_CBN_SELCHANGE(IDC_COMBO_ComList, OnSelchangeCOMBOComList)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_DEV, OnButtonSearchDev)
	ON_CBN_SELCHANGE(IDC_COMBO_BaudList, OnSelchangeCOMBOBaudList)
	ON_BN_CLICKED(IDC_BUTTON_CFG_UUID, OnButtonCfgUuid)
	ON_BN_CLICKED(IDC_BUTTON_RXClear, OnBUTTONRXClear)
	ON_LBN_DBLCLK(IDC_LIST_CONNLIST, OnDblclkListConnlist)
	ON_BN_CLICKED(IDC_CHECK_ISSENDPERIOD, OnCheckIssendperiod)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_SEND_PERIOD, OnChangeEditSendPeriod)
	ON_WM_DEVICECHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUartDemoDlg message handlers

#define BAUD_NUM	3
LPCTSTR strBaud[BAUD_NUM]={"57600","115200", "9600"};
int		nBaudArray[BAUD_NUM] = {CBR_57600, CBR_115200, CBR_9600 };
void CUartDemoDlg::InitDlg()
{
	int			ret;
	ret = m_CUartControl.GetAvailableCom(m_CComList, m_byAvailableCom);
	if( 1 == ret )
	{
		m_CComList.SetCurSel(0);
		m_CUartControl.SetUartComNum(m_byAvailableCom[m_CComList.GetCurSel()]);
	}

	m_CBaudList.ResetContent();
	for( int i = 0; i < BAUD_NUM; i++ )
	{
		m_CBaudList.AddString(strBaud[i]);
	}
	m_CBaudList.SetCurSel(0);
	m_CUartControl.SetUartComBaud(nBaudArray[m_CBaudList.GetCurSel()]);
	
	m_srvUUID.SetLimitText(4);
	m_srvUUID.SetWindowText("FFF0");
	m_rxUUID.SetLimitText(4);
	m_rxUUID.SetWindowText("FFF4");
	m_txUUID.SetLimitText(4);
	m_txUUID.SetWindowText("FFF1");
	m_CEditSendPeriod.SetWindowText("1000");
	m_nPeriodSendTimer = PERIOD_SEND_TIMER;
	m_hTerminateSignal = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hCommRecvSignal = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_nExitCommWaitThread = 0;
}

void CUartDemoDlg::DispDevList(BYTE *frameBuff, long len)
{
	long	startIndex;
	int		nameLen;
	BYTE	addrAsc[12];
	BYTE	name[30];
	CString	devList ;
	
	startIndex = 6;
	while( startIndex < len )
	{
		devList = DISP_ADDR;
		nameLen = frameBuff[startIndex];
		memcpy(name, frameBuff+startIndex+1, nameLen);
		startIndex += nameLen+1;
		name[nameLen] = 0;
		Hex2Asc(frameBuff+startIndex, addrAsc, 6);
		addrAsc[6*2] = 0;
		devList =  devList + (LPCTSTR)addrAsc + DISP_NAME+ name +"\r\n";
		m_RxData.SetSel(-1,-1);
		m_RxData.ReplaceSel((LPCTSTR)devList);		
		startIndex += 6;
		
	}
	
}

BOOL CUartDemoDlg::OnInitDialog()
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
	m_CUartControl.SetUartStat(UART_CLOSED);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUartDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUartDemoDlg::OnPaint() 
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
HCURSOR CUartDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CUartDemoDlg::OnDeviceChange(UINT nEventType,DWORD dwData)
{
	int		ret;
	int		index;
	CString		strComBackup;
	int			listCount;
	CString		commList;
	//DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;
	switch (nEventType)
	{
	case DBT_DEVICEREMOVECOMPLETE://移除设备
	case DBT_DEVICEARRIVAL://添加设备
		index = m_CComList.GetCurSel();

		m_CComList.GetWindowText(strComBackup);
		ret = m_CUartControl.GetAvailableCom(m_CComList, m_byAvailableCom);
		if( 1 == ret )
		{
			if( !m_CUartControl.IsUartOpen() )
			{
				m_CComList.SetCurSel(0);
				m_CUartControl.SetUartComNum(m_byAvailableCom[m_CComList.GetCurSel()]);
			}
			else
			{
				listCount = m_CComList.GetCount();
				for( int i = 0; i < listCount; i++ )
				{
					m_CComList.GetLBText(i, commList);
					if(commList.Compare(strComBackup) == 0)
					{
						m_CComList.SetCurSel(i);
						return TRUE;
					}
				}
				m_CComList.SetCurSel(0);
			}

		}	
		break;
		
	default:
		break;
	}
	
	return TRUE;
	
}


UINT WaitComRecv(LPVOID lpVoid)
{
	CUartDemoDlg	*pDemoDlg = (CUartDemoDlg *)lpVoid;
	
	DWORD		dwEvtMask;
	DWORD		dwNumRead = 0;
	HANDLE		hComHandle;
	BOOL		ret;	
	

	hComHandle = (pDemoDlg->m_CUartControl).GetUartHandle();
	if ( !SetCommMask(hComHandle, EV_RXCHAR) )
	{
		return -1;
	}
	while(true)
	{

		ret = WaitCommEvent(hComHandle, &dwEvtMask,NULL);
		if ( (dwEvtMask&EV_RXCHAR) == EV_RXCHAR )
		{
			SetEvent(pDemoDlg->m_hCommRecvSignal);
		}
		if ( 1 == pDemoDlg->m_nExitCommWaitThread )
		{
			pDemoDlg->m_nExitCommWaitThread  = 0;
			return 0;
		}
	}
	return 0;
}
UINT ReadProc(LPVOID lpVoid)
{
	CUartDemoDlg	*pDemoDlg = (CUartDemoDlg *)lpVoid;

	DWORD		dwErrMask;
	DWORD		dwEvtMask;
	DWORD		dwNumRead = 0;
	static BYTE		uartBuff[20480];
	BYTE		byFrameBuff[600];
	long		lFrameLen;
	COMSTAT		comStat;
	OVERLAPPED	ov;
	HANDLE		hComHandle;
	CString		strlog;
	SYSTEMTIME	systemTime;
	CString		strTime;
	CMyUart		*uartControl;
	CStatisInfo	*pCStatis;
	BOOL		ret;
	DWORD		dwIsSginal;
	HANDLE		hWaitHandle[2];


	ov.Internal = 0;
	ov.InternalHigh = 0;
	ov.Offset = 0;
	ov.OffsetHigh = 0;
	ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hComHandle = (pDemoDlg->m_CUartControl).GetUartHandle();
// 	if ( !SetCommMask(hComHandle, EV_RXCHAR) )
// 	{
// 		return -1;
// 	}
	uartControl = &(pDemoDlg->m_CUartControl);
	pCStatis = &(pDemoDlg->m_CStatisInfo);

	hWaitHandle[1] = pDemoDlg->m_hCommRecvSignal;
	hWaitHandle[0] = pDemoDlg->m_hTerminateSignal;
	while(TRUE)
	{
//  	ret = WaitCommEvent(hComHandle, &dwEvtMask, &ov);//NULL);
// 		dwIsSginal = WaitForSingleObject(pDemoDlg->m_hTerminateSignal, 0);
		dwIsSginal = WaitForMultipleObjects(2, hWaitHandle, FALSE, INFINITE);

		if ( WAIT_OBJECT_0 == dwIsSginal )
		{
			ResetEvent(pDemoDlg->m_hTerminateSignal);
			pDemoDlg->m_nExitCommWaitThread = 1;
			return 0;
		}
		if ( WAIT_OBJECT_0+1 == dwIsSginal )
// 		if ( (dwEvtMask&EV_RXCHAR) == EV_RXCHAR )
		{
			ResetEvent(pDemoDlg->m_hCommRecvSignal);
			ClearCommError(hComHandle, &dwErrMask, &comStat);
			if( comStat.cbInQue >0 )
			{
				if ( !ReadFile(hComHandle, uartBuff, comStat.cbInQue, &dwNumRead, &ov) )
				{
					if ( GetLastError() == ERROR_IO_PENDING )
					{
						while ( !GetOverlappedResult(hComHandle, &ov, &dwNumRead, FALSE) )
						{
							if(GetLastError() == ERROR_IO_INCOMPLETE )
								continue;
						}
						int handleIndex = 0;
						while ( dwNumRead > 0 )
						{
							uartControl->HandleRecvByte(uartBuff[handleIndex]);
							dwNumRead--;
							handleIndex++;

							lFrameLen = sizeof(byFrameBuff);
							uartControl->GetFrameData(byFrameBuff, &lFrameLen);
							if( lFrameLen > 0)	// 收到完整一帧了
							{
								GetLocalTime(&systemTime);

								BYTE		szAscii[2048];
								LOGI("Recv:");
								LOG_DATA(byFrameBuff, lFrameLen);
								Hex2Asc(byFrameBuff, szAscii,lFrameLen);
								szAscii[lFrameLen*2] = '\r';
								szAscii[lFrameLen*2+1] = '\n';
								szAscii[lFrameLen*2+2] =0;
								if( uartControl->IsDevListRsp() )	// 查询广播设备响应特殊处理
								{
									pDemoDlg->DispDevList( byFrameBuff, lFrameLen);
								}
								else
								{
									WORD	connId;
									connId = uartControl->GetConnid();
									if ( uartControl->IsNewConnRsp() )
									{
										pCStatis->UpdateConnInfo(connId, pDemoDlg->m_connList);
									}
									else if(uartControl->IsDisConnRsp())
									{
										pDemoDlg->m_CStatisInfo.UpdateDeleteInfo(connId, pDemoDlg->m_connList);
									}
									else if( uartControl->IsNewRecvData() )
									{
										pDemoDlg->m_CStatisInfo.AddRxCount(connId);
										pDemoDlg->m_CStatisInfo.UpdateCountInfo(connId, pDemoDlg->m_connList);
									}
									else if ( uartControl->IsSendDone())
									{
										pDemoDlg->m_CStatisInfo.AddTxCount(connId);
										pDemoDlg->m_CStatisInfo.UpdateCountInfo(connId, pDemoDlg->m_connList);
									}
									pDemoDlg->m_RxData.SetSel(-1,-1);
									pDemoDlg->m_RxData.ReplaceSel((LPCTSTR)szAscii);
								}
								strTime.Format("接收时间：%2dh:%2dm:%2ds:%3dms --",systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds) ;
								strlog = strTime+szAscii;
								fwrite(strlog, 1,strlog.GetLength(), pDemoDlg->m_fpLog);
								uartControl->ClearFrameFlag();
								
							}
							

						}
							
					}
				}
				else
				{
					int handleIndex = 0;
					while ( dwNumRead > 0 )
					{
						uartControl->HandleRecvByte(uartBuff[handleIndex]);
						dwNumRead--;
						handleIndex++;
						lFrameLen = sizeof(byFrameBuff);
						uartControl->GetFrameData(byFrameBuff, &lFrameLen);
						if ( lFrameLen >0 )
						{		
							GetLocalTime(&systemTime);
							BYTE		szAscii[2048];
							Hex2Asc(byFrameBuff, szAscii,lFrameLen);
							LOGI("Recv:");
							LOG_DATA(byFrameBuff, lFrameLen);
							szAscii[lFrameLen*2] = '\r';
							szAscii[lFrameLen*2+1] = '\n';
							szAscii[lFrameLen*2+2] =0;
							if( uartControl->IsDevListRsp() )	// 查询广播设备响应特殊处理
							{
								pDemoDlg->DispDevList( byFrameBuff, lFrameLen);
							}
							else
							{
								WORD	connId;
								connId = uartControl->GetConnid();
								if ( uartControl->IsNewConnRsp() )
								{
									pCStatis->UpdateConnInfo(connId, pDemoDlg->m_connList);
								}
								else if(uartControl->IsDisConnRsp())
								{
									pDemoDlg->m_CStatisInfo.UpdateDeleteInfo(connId, pDemoDlg->m_connList);
								}
								else if( uartControl->IsNewRecvData() )
								{
									pDemoDlg->m_CStatisInfo.AddRxCount(connId);
									pDemoDlg->m_CStatisInfo.UpdateCountInfo(connId, pDemoDlg->m_connList);
								}
								else if ( uartControl->IsSendDone())
								{
									pDemoDlg->m_CStatisInfo.AddTxCount(connId);
									pDemoDlg->m_CStatisInfo.UpdateCountInfo(connId, pDemoDlg->m_connList);
								}
								pDemoDlg->m_RxData.SetSel(-1,-1);
								pDemoDlg->m_RxData.ReplaceSel((LPCTSTR)szAscii);
							}
							strTime.Format("接收时间：%2dh:%2dm:%2ds:%3dms --",systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds) ;
							strlog = strTime+szAscii;
							fwrite(strlog, 1,strlog.GetLength(), pDemoDlg->m_fpLog);
							uartControl->ClearFrameFlag();
						}
					}
					ResetEvent(ov.hEvent);
				}
			}
		}
	}
	return 0;
}


void CUartDemoDlg::OnButtonOpencom() 
{
	// TODO: Add your control notification handler code here
	int ret;
	CString str;//获取系统时间 　　
	CTime tm;
	if ( !m_CUartControl.IsUartOpen() )
	{
		ret = m_CUartControl.OpenUart();
		if ( 0 != ret )
		{
			m_openUart.SetWindowText("Close");
			m_CUartControl.SetUartStat(UART_OPENED);
			m_fpLog = fopen("UartLog.txt","ab+");
			tm=CTime::GetCurrentTime();
			str=tm.Format("           本次日志起始时间是%Y年%m月%d日 %X\r\n");
			str = "\r\n        **************************************************\r\n"+str;
			str += "        **************************************************\r\n";
			ret = fwrite(str, 1, str.GetLength(), m_fpLog );
			AfxBeginThread(WaitComRecv, this);
			AfxBeginThread(ReadProc, this);
		}
	}
	else
	{	
		m_CUartControl.CloseUart();
		m_openUart.SetWindowText("Open");
		m_CUartControl.SetUartStat(UART_CLOSED);
		// 结束串口数据处理线程
		SetEvent(m_hTerminateSignal);
	}
}

void CUartDemoDlg::SendTxEditData(void)
{
	// TODO: Add your control notification handler code here
	CString		strData;
	long		len;
	SYSTEMTIME	systemTime;
	CString		strTime;
	CString		strLog;
	BYTE		szHex[1024];
	BYTE		szFrameData[1024];
	LPCTSTR		szAsc;
	WORD		connid;
	
	if( !m_CUartControl.IsUartOpen())
	{
		//	AfxMessageBox("串口未打开！");
		return ;
	}
	if( !m_CUartControl.IsMasterConnected() )
	{
		//	AfxMessageBox("主机未连接！");
		return ;
	}
	m_CEditTxData.GetWindowText(strData);
	len = strData.GetLength();
	szAsc = strData;
	Asc2Hex((BYTE *)szAsc, szHex, len);	
	len = m_CUartControl.PacketFrameData(CMD_SEND_DATA, szHex, szFrameData, len/2);
	
	Hex2Asc(szFrameData, szHex, len);	//szhex临时用来存asc形式数据方便存储日志。
	szHex[len*2] = 0;
	GetLocalTime(&systemTime);
	strTime.Format("发送数据：%2dh:%2dm:%2ds:%3dms --",systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds) ;
	strLog = strTime+szHex+"\r\n";
	
	connid = (WORD)(szFrameData[6]<<8)&0xff00;+szFrameData[7];
	m_CUartControl.SendUartData(szFrameData, len);
	fwrite(strLog, 1,strLog.GetLength(), m_fpLog);	

} 
 

void CUartDemoDlg::OnButtonSend() 
{
	SendTxEditData();
}

void CUartDemoDlg::OnSelchangeCOMBOComList() 
{
	// TODO: Add your control notification handler code here
	int index;

	index = m_CComList.GetCurSel();

	m_CUartControl.SetUartComNum(m_byAvailableCom[index]);
}


void CUartDemoDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	CString		strBtInfo;
	long		len;
	SYSTEMTIME	systemTime;
	CString		strTime;
	CString		strLog;
	BYTE		szAsc[50];
	BYTE		szAddrHex[20];
	BYTE		bleName[21];
	BYTE		szConnCmd[30];
	LPCTSTR		pszBtinfo;
	long		index;
	int			nameLen;
	if( !m_CUartControl.IsUartOpen() )
	{
		AfxMessageBox("串口未打开！");
		return ;
	}
	if(!m_CUartControl.IsMasterCfgedUUID() )
	{
		AfxMessageBox("未设置UUID！");
		return ;
	}
	
	strBtInfo = m_RxData.GetSelText();
	pszBtinfo = strBtInfo;
	index = strBtInfo.Find(DISP_ADDR);
	Asc2Hex((BYTE *)(pszBtinfo+index+strlen(DISP_ADDR)), szAddrHex, 12);	//地址转成hex
	index = strBtInfo.Find(DISP_NAME);
	nameLen = strlen(pszBtinfo+index+strlen(DISP_NAME));
	nameLen = nameLen>MAX_NAME_SIZE?MAX_NAME_SIZE:nameLen;
	memcpy(bleName, pszBtinfo+index+strlen(DISP_NAME), nameLen);
	bleName[nameLen] = 0;//字符串结束符

	// 记录最近发起连接的设备名字和地址
	m_CStatisInfo.SetLastBleName(bleName,nameLen+1);	//+1 为了拷贝字符串结束符	
	m_CStatisInfo.SetLastBleAddr(szAddrHex);
	LOGI("set Last name:%s\r\n",bleName);
	LOGI("set last addr:");
	LOG_DATA(szAddrHex, 6);
	len = m_CUartControl.PacketFrameData(CMD_CONN_DEV, szAddrHex, szConnCmd, 6);// 封包连接命令
	
	// 记录日志信息
	Hex2Asc(szConnCmd, szAsc, len);
	szAsc[len*2]=0;	// 字符串结束
	GetLocalTime(&systemTime);
	strTime.Format("连接设备：%2dh:%2dm:%2ds:%3dms --",systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds) ;
	strLog = strTime+szAsc+"\r\n";
	
	// 发送命令
	m_CUartControl.SendUartData(szConnCmd, len);
	m_CUartControl.SetMasterState(MASTER_CONNED);
	fwrite(strLog, 1,strLog.GetLength(), m_fpLog);
	fflush(m_fpLog);	
	
	return ;
}

void CUartDemoDlg::OnButtonSearchDev() 
{
	// TODO: Add your control notification handler code here
	long		len;
	SYSTEMTIME	systemTime;
	CString		strTime;
	CString		strLog;
	BYTE		szHex[20];
	BYTE		szAsc[50];
	
	if( !m_CUartControl.IsUartOpen() )
	{
		AfxMessageBox("串口未打开！");
		return ;
	}
	len = m_CUartControl.PacketFrameData(CMD_QUERY_DEV_LIST, NULL, szHex, 0);
	Hex2Asc(szHex, szAsc, len);
	szAsc[len*2]=0;	// 字符串结束
	GetLocalTime(&systemTime);
	strTime.Format("查询周围设备：%2dh:%2dm:%2ds:%3dms --",systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds) ;
	strLog = strTime+szAsc+"\r\n";
	
	m_CUartControl.SendUartData(szHex, len);

	fwrite(strLog, 1,strLog.GetLength(), m_fpLog);
	fflush(m_fpLog);	
}

void CUartDemoDlg::OnSelchangeCOMBOBaudList() 
{
	// TODO: Add your control notification handler code here
	int index;
	
	index = m_CBaudList.GetCurSel();
	m_CUartControl.SetUartComBaud(nBaudArray[index]);
}

void CUartDemoDlg::OnButtonCfgUuid() 
{
	// TODO: Add your control notification handler code here
	CString		strTxUUID,strRxUUID,strSrvUUID;
	LPCTSTR		ptxUUID,prxUUID,pSrvUUID;
	BYTE		cmdData[10];
	BYTE		FrameData[40];
	long		lFrameLen;

	SYSTEMTIME	systemTime;
	CString		strTime;
	CString		strLog;
	BYTE		szAsc[2048];
	if( !m_CUartControl.IsUartOpen())
	{
		AfxMessageBox("串口未打开！");
		return ;
	}
	m_rxUUID.GetWindowText(strRxUUID);
	m_txUUID.GetWindowText(strTxUUID);
	m_srvUUID.GetWindowText(strSrvUUID);
	ptxUUID = strTxUUID;
	prxUUID = strRxUUID;
	pSrvUUID  = strSrvUUID;
	Asc2Hex((BYTE *)pSrvUUID, cmdData, 4);
	Asc2Hex((BYTE *)prxUUID, cmdData+2, 4);
	Asc2Hex((BYTE *)ptxUUID, cmdData+4, 4);
	lFrameLen = m_CUartControl.PacketFrameData(CMD_CFG_UUIDS, cmdData, FrameData, 6);
	
	//日志信息
	Hex2Asc(FrameData, szAsc, lFrameLen);
	szAsc[lFrameLen*2]=0;	// 字符串结束
	GetLocalTime(&systemTime);
	strTime.Format("配置UUID：%2dh:%2dm:%2ds:%3dms --",systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds) ;
	strLog = strTime+szAsc+"\r\n";

	m_CUartControl.SendUartData(FrameData, lFrameLen);
	m_CUartControl.SetMasterState(MASTER_CFG_UUID);
}

void CUartDemoDlg::OnBUTTONRXClear() 
{
	// TODO: Add your control notification handler code here
	m_RxData.SetWindowText("");

}

void CUartDemoDlg::OnDblclkListConnlist() 
{
	// TODO: Add your control notification handler code here
	int			selected;
	CString		content;
	BYTE		bleConnId[2];
	BYTE		szAsc[100];
	BYTE		byFrameData[30];
	long		lFrameLen;
	int			index;

	SYSTEMTIME	systemTime;
	CString		strTime;
	CString		strLog;

	selected = m_connList.GetCurSel();
	m_connList.GetText(selected, content);
	m_connList.DeleteString(selected);

	index = content.Find(CONN_ID);
	memcpy(szAsc, (LPCTSTR)content+index+strlen(CONN_ID), 4);
	Asc2Hex(szAsc, bleConnId, 4);
	
	// 封包命令
	lFrameLen = m_CUartControl.PacketFrameData(CMD_DISCONN_DEV, bleConnId, byFrameData, 2);
	LOGI("Disconn :");
	LOG_DATA(byFrameData, lFrameLen);
	//日志信息
	Hex2Asc(byFrameData, szAsc, lFrameLen);
	szAsc[lFrameLen*2]=0;	// 字符串结束
	GetLocalTime(&systemTime);
	strTime.Format("断开设备：%2dh:%2dm:%2ds:%3dms --",systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds) ;
	strLog = strTime+szAsc+"\r\n";
	
	m_CUartControl.SendUartData(byFrameData, lFrameLen);
	
	fwrite(strLog, 1,strLog.GetLength(), m_fpLog);
	fflush(m_fpLog);	

}

void CUartDemoDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	WORD	connId;
	BYTE	szHexConnId[4];
	BYTE	szFrameData[20];
	BYTE	szAscLog[40];
	long	lFrameLen;

	SYSTEMTIME	systemTime;
	CString		strTime;
	CString		strLog;

	for( int i = 0; i < MAX_CONN_COUNT; i++ )
	{
		connId = m_CStatisInfo.GetConnId(i);
		if( INVALID_CONNID != connId)
		{
			szHexConnId[0] = (connId>>8)&0xff;
			szHexConnId[1] = connId&0xff;
			lFrameLen = m_CUartControl.PacketFrameData(CMD_DISCONN_DEV, szHexConnId, szFrameData, 2);
			// 记录日志
			Hex2Asc(szFrameData, szAscLog, lFrameLen);	//szhex临时用来存asc形式数据方便存储日志。
			szAscLog[lFrameLen*2] = 0;
			GetLocalTime(&systemTime);
			strTime.Format("断开设备：%2dh:%2dm:%2ds:%3dms --",systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds) ;
			strLog = strTime+szAscLog+"\r\n";
			
			m_CUartControl.SendUartData(szFrameData, lFrameLen);
			fwrite(strLog, 1,strLog.GetLength(), m_fpLog);
		}
	}
	CDialog::PostNcDestroy();
}

void CUartDemoDlg::OnCheckIssendperiod() 
{
	CString strPeriod;
	long	nPeriod;

	// TODO: Add your control notification handler code here
	if( m_CCheckOk.GetCheck())
	{
		m_CEditSendPeriod.GetWindowText(strPeriod);
		nPeriod = atoi((LPCTSTR)strPeriod);
		SetTimer(m_nPeriodSendTimer, nPeriod, NULL);
	}else
	{
		KillTimer(m_nPeriodSendTimer);
	}


}

void CUartDemoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
		case PERIOD_SEND_TIMER:
			SendTxEditData();
			break;
		default:
			break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CUartDemoDlg::OnChangeEditSendPeriod() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString strPeriod;
	long	nPeriod;

	if( m_CCheckOk.GetCheck())
	{
		m_CEditSendPeriod.GetWindowText(strPeriod);
		nPeriod = atoi((LPCTSTR)strPeriod);
		SetTimer(m_nPeriodSendTimer, nPeriod, NULL);
	}else
	{
		KillTimer(m_nPeriodSendTimer);
	}	
}
