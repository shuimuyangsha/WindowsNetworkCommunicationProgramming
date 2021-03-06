// Telnetmfc.h : main header file for the TELNETMFC application
//

#if !defined(AFX_TELNETMFC_H__1D6A0AC5_4836_4517_85B4_B46085844AF8__INCLUDED_)
#define AFX_TELNETMFC_H__1D6A0AC5_4836_4517_85B4_B46085844AF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcApp:
// See Telnetmfc.cpp for the implementation of this class
//

class CTelnetmfcApp : public CWinApp
{
public:
	CTelnetmfcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelnetmfcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTelnetmfcApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TELNETMFC_H__1D6A0AC5_4836_4517_85B4_B46085844AF8__INCLUDED_)
