; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUartDemoDlg
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "UartDemo.h"

ClassCount=5
Class1=CUartDemoApp
Class2=CUartDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CHListBox
Class5=CMyEdit
Resource3=IDD_UARTDEMO_DIALOG

[CLS:CUartDemoApp]
Type=0
HeaderFile=UartDemo.h
ImplementationFile=UartDemo.cpp
Filter=N

[CLS:CUartDemoDlg]
Type=0
HeaderFile=UartDemoDlg.h
ImplementationFile=UartDemoDlg.cpp
Filter=D
LastObject=IDC_EDIT_SEND_PERIOD
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=UartDemoDlg.h
ImplementationFile=UartDemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_UARTDEMO_DIALOG]
Type=1
Class=CUartDemoDlg
ControlCount=25
Control1=IDC_STATIC,button,1342177287
Control2=IDC_COMBO_ComList,combobox,1344339970
Control3=IDC_BUTTON_OPENCOM,button,1342242817
Control4=IDC_EDIT_TXDATA,edit,1352732748
Control5=IDC_BUTTON_SEND,button,1342242816
Control6=IDC_COMBO_BaudList,combobox,1344339970
Control7=IDC_BUTTON_CONNECT,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_BUTTON_SEARCH_DEV,button,1342242816
Control11=IDC_RICHEDIT_RXDARA,RICHEDIT,1352730628
Control12=IDC_EDIT_RXUUID,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_TXUUID,edit,1350631552
Control16=IDC_BUTTON_CFG_UUID,button,1342242816
Control17=IDC_EDIT_SRVUUID,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_BUTTON_RXClear,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_LIST_CONNLIST,listbox,1351684353
Control22=IDC_EDIT_SEND_PERIOD,edit,1350631424
Control23=IDC_CHECK_ISSENDPERIOD,button,1342242819
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352

[CLS:CHListBox]
Type=0
HeaderFile=HListBox.h
ImplementationFile=HListBox.cpp
BaseClass=CListBox
Filter=W

[CLS:CMyEdit]
Type=0
HeaderFile=MyEdit.h
ImplementationFile=MyEdit.cpp
BaseClass=CEdit
Filter=W
LastObject=CMyEdit
VirtualFilter=WC

