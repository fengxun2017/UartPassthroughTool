// SlaveUartDemo.h : main header file for the SLAVEUARTDEMO application
//

#if !defined(AFX_SLAVEUARTDEMO_H__1C7C7288_2B53_4B78_9BD6_7A9C02B48FF8__INCLUDED_)
#define AFX_SLAVEUARTDEMO_H__1C7C7288_2B53_4B78_9BD6_7A9C02B48FF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSlaveUartDemoApp:
// See SlaveUartDemo.cpp for the implementation of this class
//

class CSlaveUartDemoApp : public CWinApp
{
public:
	CSlaveUartDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlaveUartDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSlaveUartDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLAVEUARTDEMO_H__1C7C7288_2B53_4B78_9BD6_7A9C02B48FF8__INCLUDED_)
