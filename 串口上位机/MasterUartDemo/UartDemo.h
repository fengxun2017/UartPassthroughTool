// UartDemo.h : main header file for the UARTDEMO application
//

#if !defined(AFX_UARTDEMO_H__E7E039F2_439E_419D_AD9C_4B97C83CEF13__INCLUDED_)
#define AFX_UARTDEMO_H__E7E039F2_439E_419D_AD9C_4B97C83CEF13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUartDemoApp:
// See UartDemo.cpp for the implementation of this class
//

class CUartDemoApp : public CWinApp
{
public:
	CUartDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUartDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUartDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UARTDEMO_H__E7E039F2_439E_419D_AD9C_4B97C83CEF13__INCLUDED_)
