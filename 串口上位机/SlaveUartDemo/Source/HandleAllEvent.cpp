
#include "stdafx.h"
#include <stdio.h>
#include "SlaveUartDemoDlg.h"
#include "UartHandle.h"
#include "auxiliary.h"

#define IDC_COMBO_COMLIST0              1000
#define IDC_COMBO_BAUDLIST0             1001
#define IDC_BUTTON_COMOPEN0             1002
#define IDC_CHECK_ISPERIODSEND0         1003
#define IDC_EDIT_TXPERIOD0              1004
#define IDC_BUTTON_SENDDATA0            1005
#define IDC_EDIT_TXDATA0                1006
#define IDC_RICHEDIT_RXDATA0            1009
#define IDC_BUTTON_CLEARRX0             1010
#define IDC_EDIT_TXCOUNT0               1036
#define IDC_EDIT_RXCOUNT0               1037
#define IDC_COMBO_COMLIST1              1319
#define IDC_COMBO_BAUDLIST1             1320
#define IDC_BUTTON_COMOPEN1             1321
#define IDC_CHECK_ISPERIODSEND1         1322
#define IDC_EDIT_TXPERIOD1              1323
#define IDC_BUTTON_SENDDATA1            1324
#define IDC_EDIT_TXDATA1                1325
#define IDC_RICHEDIT_RXDATA1            1326
#define IDC_BUTTON_CLEARRX1             1327
#define IDC_EDIT_TXCOUNT1               1328
#define IDC_EDIT_RXCOUNT1               1329
#define IDC_COMBO_COMLIST2              1330
#define IDC_COMBO_BAUDLIST2             1331
#define IDC_BUTTON_COMOPEN2             1332
#define IDC_CHECK_ISPERIODSEND2         1333
#define IDC_EDIT_TXPERIOD2              1334
#define IDC_BUTTON_SENDDATA2            1335
#define IDC_EDIT_TXDATA2                1336
#define IDC_RICHEDIT_RXDATA2            1337
#define IDC_BUTTON_CLEARRX2             1338
#define IDC_EDIT_TXCOUNT2               1339
#define IDC_EDIT_RXCOUNT2               1340
#define IDC_COMBO_COMLIST3              1341
#define IDC_COMBO_BAUDLIST3             1342
#define IDC_BUTTON_COMOPEN3             1343
#define IDC_CHECK_ISPERIODSEND3         1344
#define IDC_EDIT_TXPERIOD3              1345
#define IDC_BUTTON_SENDDATA3            1346
#define IDC_EDIT_TXDATA3                1347
#define IDC_RICHEDIT_RXDATA3            1348
#define IDC_BUTTON_CLEARRX3             1349
#define IDC_EDIT_TXCOUNT3               1350
#define IDC_EDIT_RXCOUNT3               1351
#define IDC_COMBO_COMLIST4              1396
#define IDC_COMBO_BAUDLIST4             1397
#define IDC_BUTTON_COMOPEN4             1398
#define IDC_CHECK_ISPERIODSEND4         1399
#define IDC_EDIT_TXPERIOD4              1400
#define IDC_BUTTON_SENDDATA4            1401
#define IDC_EDIT_TXDATA4                1402
#define IDC_RICHEDIT_RXDATA4            1403
#define IDC_BUTTON_CLEARRX4             1404
#define IDC_EDIT_TXCOUNT4               1405
#define IDC_EDIT_RXCOUNT4               1406
#define IDC_COMBO_COMLIST5              1407
#define IDC_COMBO_BAUDLIST5             1408
#define IDC_BUTTON_COMOPEN5             1409
#define IDC_CHECK_ISPERIODSEND5         1410
#define IDC_EDIT_TXPERIOD5              1411
#define IDC_BUTTON_SENDDATA5            1412
#define IDC_EDIT_TXDATA5                1413
#define IDC_RICHEDIT_RXDATA5            1414
#define IDC_BUTTON_CLEARRX5             1415
#define IDC_EDIT_TXCOUNT5               1416
#define IDC_EDIT_RXCOUNT5               1417
#define IDC_COMBO_COMLIST6              1418
#define IDC_COMBO_BAUDLIST6             1419
#define IDC_BUTTON_COMOPEN6             1420
#define IDC_CHECK_ISPERIODSEND6         1421
#define IDC_EDIT_TXPERIOD6              1422
#define IDC_BUTTON_SENDDATA6            1423
#define IDC_EDIT_TXDATA6                1424
#define IDC_RICHEDIT_RXDATA6            1425
#define IDC_BUTTON_CLEARRX6             1426
#define IDC_EDIT_TXCOUNT6               1427
#define IDC_EDIT_RXCOUNT6               1428
#define IDC_COMBO_COMLIST7              1429
#define IDC_COMBO_BAUDLIST7             1430
#define IDC_BUTTON_COMOPEN7             1431
#define IDC_CHECK_ISPERIODSEND7         1432
#define IDC_EDIT_TXPERIOD7              1433
#define IDC_BUTTON_SENDDATA7            1434
#define IDC_EDIT_TXDATA7                1435
#define IDC_RICHEDIT_RXDATA7            1436
#define IDC_BUTTON_CLEARRX7             1437
#define IDC_EDIT_TXCOUNT7               1438
#define IDC_EDIT_RXCOUNT7               1439
#define IDC_BUTTON_DISCONN0             1440
#define IDC_BUTTON_DISCONN1             1441
#define IDC_BUTTON_DISCONN2             1442
#define IDC_BUTTON_DISCONN3             1443
#define IDC_BUTTON_DISCONN4             1444
#define IDC_BUTTON_DISCONN5             1445
#define IDC_BUTTON_DISCONN6             1446
#define IDC_BUTTON_DISCONN7             1447



WORD pwOpenUartButtonId[MAX_SLAVE_DEVICE] = {
IDC_BUTTON_COMOPEN0,IDC_BUTTON_COMOPEN1,IDC_BUTTON_COMOPEN2,IDC_BUTTON_COMOPEN3,
IDC_BUTTON_COMOPEN4,IDC_BUTTON_COMOPEN5,IDC_BUTTON_COMOPEN6,IDC_BUTTON_COMOPEN7,
};

WORD pwSendButtonId[MAX_SLAVE_DEVICE] = {
IDC_BUTTON_SENDDATA0,IDC_BUTTON_SENDDATA1,IDC_BUTTON_SENDDATA2,IDC_BUTTON_SENDDATA3,
IDC_BUTTON_SENDDATA4,IDC_BUTTON_SENDDATA5,IDC_BUTTON_SENDDATA6,IDC_BUTTON_SENDDATA7,
};

WORD pwClearButtonId[MAX_SLAVE_DEVICE] = {
IDC_BUTTON_CLEARRX0,IDC_BUTTON_CLEARRX1,IDC_BUTTON_CLEARRX2,IDC_BUTTON_CLEARRX3,
IDC_BUTTON_CLEARRX4,IDC_BUTTON_CLEARRX5,IDC_BUTTON_CLEARRX6,IDC_BUTTON_CLEARRX7,
};
WORD pwDisconnButtonId[MAX_SLAVE_DEVICE] = {
IDC_BUTTON_DISCONN0,IDC_BUTTON_DISCONN1,IDC_BUTTON_DISCONN2,IDC_BUTTON_DISCONN3,
IDC_BUTTON_DISCONN4,IDC_BUTTON_DISCONN5,IDC_BUTTON_DISCONN6,IDC_BUTTON_DISCONN7,
};
WORD pwCheckPeriodId[MAX_SLAVE_DEVICE] = {
IDC_CHECK_ISPERIODSEND0,IDC_CHECK_ISPERIODSEND1,IDC_CHECK_ISPERIODSEND2,IDC_CHECK_ISPERIODSEND3,
IDC_CHECK_ISPERIODSEND4,IDC_CHECK_ISPERIODSEND5,IDC_CHECK_ISPERIODSEND6,IDC_CHECK_ISPERIODSEND7,
};

WORD pwCommListId[MAX_SLAVE_DEVICE] = {
IDC_COMBO_COMLIST0,IDC_COMBO_COMLIST1,IDC_COMBO_COMLIST2,IDC_COMBO_COMLIST3,
IDC_COMBO_COMLIST4,IDC_COMBO_COMLIST5,IDC_COMBO_COMLIST6,IDC_COMBO_COMLIST7,
};

WORD pwBaudListId[MAX_SLAVE_DEVICE] = {
IDC_COMBO_BAUDLIST0,IDC_COMBO_BAUDLIST1,IDC_COMBO_BAUDLIST2,IDC_COMBO_BAUDLIST3,
IDC_COMBO_BAUDLIST4,IDC_COMBO_BAUDLIST5,IDC_COMBO_BAUDLIST6,IDC_COMBO_BAUDLIST7,
};

WORD pwSendPeriodId[MAX_SLAVE_DEVICE] = {
IDC_EDIT_TXPERIOD0,IDC_EDIT_TXPERIOD1,IDC_EDIT_TXPERIOD2,IDC_EDIT_TXPERIOD3,
IDC_EDIT_TXPERIOD4,IDC_EDIT_TXPERIOD5,IDC_EDIT_TXPERIOD6,IDC_EDIT_TXPERIOD7,
};


int GetControlIndex(WORD ID)
{
	int i;
	for( i = 0; i < MAX_SLAVE_DEVICE; i++ )
	{
		if( (pwOpenUartButtonId[i] == ID) || (pwSendButtonId[i] == ID) || (pwClearButtonId[i] == ID) || (pwDisconnButtonId[i] == ID) ||
			(pwCheckPeriodId[i] == ID) || (pwCommListId[i] == ID) || (pwBaudListId[i] == ID) || (pwSendPeriodId[i] == ID) )
		{
			return i;
		}
	}
	return 0xFFFF;

}

void UartReadProc(unsigned char index, CSlaveUartDemoDlg *pDlg)
{

	DWORD			dwErrMask;
	DWORD			dwEvtMask;
	DWORD			dwNumRead = 0;
	static BYTE		uartBuff[4048];
	BYTE			byFrameBuff[600];
	long			lFrameLen;
	COMSTAT			comStat;
	OVERLAPPED		ov;
	HANDLE			hComHandle;
	CMyUart			*pUartControl;

	ov.Internal = 0;
	ov.InternalHigh = 0;
	ov.Offset = 0;
	ov.OffsetHigh = 0;

	if ( NULL == pDlg )
	{
		return ;
	}
	pUartControl = &((pDlg->m_CUartControl)[index]);

	ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hComHandle = pUartControl->GetUartHandle();
	if ( !SetCommMask(hComHandle, EV_RXCHAR) )
	{
		return ;
	}

	while(TRUE)
	{
		WaitCommEvent(hComHandle, &dwEvtMask, NULL);
		if ( (dwEvtMask&EV_RXCHAR) == EV_RXCHAR )
		{
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
							pUartControl->HandleRecvByte(uartBuff[handleIndex]);
							dwNumRead--;
							handleIndex++;

							lFrameLen = sizeof(byFrameBuff);
							pUartControl->GetFrameData(byFrameBuff, &lFrameLen);
							if( lFrameLen > 0)	// 收到完整一帧了
							{
								BYTE		szAscii[2048];
								CString		strCount;
								char		strCountTemp[20];
								long		lCount;
								LOGI("Recv:");
								LOG_DATA(byFrameBuff, lFrameLen);
								Hex2Asc(byFrameBuff, szAscii,lFrameLen);
								szAscii[lFrameLen*2] = '\r';
								szAscii[lFrameLen*2+1] = '\n';
								szAscii[lFrameLen*2+2] =0;
								if( pUartControl->IsNewRecvData() )
								{
									(pDlg->m_CEditRxCount)[index].GetWindowText(strCount);
									lCount  = atoi((LPCSTR)strCount);
									lCount++;
									strCount = itoa(lCount, strCountTemp, 10);
									(pDlg->m_CEditRxCount)[index].SetWindowText(strCountTemp);

								}
								else if ( pUartControl->IsSendDone())
								{
									(pDlg->m_CEditTxCount)[index].GetWindowText(strCount);
									lCount  = atoi((LPCSTR)strCount);
									lCount++;
									itoa(lCount, strCountTemp, 10);
									(pDlg->m_CEditTxCount)[index].SetWindowText(strCountTemp);			
								}
								((pDlg->m_CRicheditRxData)[index]).SetSel(-1,-1);
								((pDlg->m_CRicheditRxData)[index]).ReplaceSel((LPCTSTR)szAscii);
// 								
// 								strTime.Format("接收时间：%2dh:%2dm:%2ds:%3dms --",systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds) ;
// 								strlog = strTime+szAscii;
// 								fwrite(strlog, 1,strlog.GetLength(), pDemoDlg->m_fpLog);
// 								uartControl->ClearFrameFlag();
							}
							

						}
							
					}
				}
				else
				{
					int handleIndex = 0;
					while ( dwNumRead > 0 )
					{
						pUartControl->HandleRecvByte(uartBuff[handleIndex]);
						dwNumRead--;
						handleIndex++;
						lFrameLen = sizeof(byFrameBuff);
						pUartControl->GetFrameData(byFrameBuff, &lFrameLen);
						if ( lFrameLen >0 )
						{		
							BYTE		szAscii[2048];
							CString		strCount;
							long		lCount;
							char		strCountTemp[20];

							LOGI("Recv:");
							LOG_DATA(byFrameBuff, lFrameLen);
							Hex2Asc(byFrameBuff, szAscii,lFrameLen);
							szAscii[lFrameLen*2] = '\r';
							szAscii[lFrameLen*2+1] = '\n';
							szAscii[lFrameLen*2+2] =0;
							if( pUartControl->IsNewRecvData() )
							{
								(pDlg->m_CEditRxCount)[index].GetWindowText(strCount);
								lCount  = atoi((LPCTSTR)strCount);
								lCount++;
								strCount = itoa(lCount, strCountTemp, 10);
								(pDlg->m_CEditRxCount)[index].SetWindowText(strCountTemp);
								
							}
							else if ( pUartControl->IsSendDone())
							{
								(pDlg->m_CEditTxCount)[index].GetWindowText(strCount);
								lCount  = atoi((LPCTSTR)strCount);
								lCount++;
								strCount = itoa(lCount, strCountTemp, 10);
								(pDlg->m_CEditRxCount)[index].SetWindowText(strCountTemp);		
							}
							(pDlg->m_CRicheditRxData)[index].SetSel(-1,-1);
							(pDlg->m_CRicheditRxData)[index].ReplaceSel((LPCTSTR)szAscii);
// 							fwrite(strlog, 1,strlog.GetLength(), pDemoDlg->m_fpLog);
// 							uartControl->ClearFrameFlag();
						}
					}
					ResetEvent(ov.hEvent);
				}
			}
		}
	}
}
