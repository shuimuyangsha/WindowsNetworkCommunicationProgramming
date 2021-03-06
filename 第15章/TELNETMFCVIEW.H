// TelnetmfcView.h : interface of the CTelnetmfcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TELNETMFCVIEW_H__A69C32E7_1B2F_4070_822E_5B340519B118__INCLUDED_)
#define AFX_TELNETMFCVIEW_H__A69C32E7_1B2F_4070_822E_5B340519B118__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTelnetmfcView : public CEditView
{
protected: // create from serialization only
	CTelnetmfcView();
	DECLARE_DYNCREATE(CTelnetmfcView)

// Attributes
public:
	CTelnetmfcDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelnetmfcView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Message(LPCTSTR lpszMessage);
	virtual ~CTelnetmfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFont m_font;

// Generated message map functions
protected:
	//{{AFX_MSG(CTelnetmfcView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TelnetmfcView.cpp
inline CTelnetmfcDoc* CTelnetmfcView::GetDocument()
   { return (CTelnetmfcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TELNETMFCVIEW_H__A69C32E7_1B2F_4070_822E_5B340519B118__INCLUDED_)
