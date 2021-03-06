// TelnetmfcView.cpp : implementation of the CTelnetmfcView class
//

#include "stdafx.h"
#include "Telnetmfc.h"

#include "TelnetmfcDoc.h"
#include "TelnetmfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcView

IMPLEMENT_DYNCREATE(CTelnetmfcView, CEditView)

BEGIN_MESSAGE_MAP(CTelnetmfcView, CEditView)
	//{{AFX_MSG_MAP(CTelnetmfcView)
	ON_WM_CHAR()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcView construction/destruction

CTelnetmfcView::CTelnetmfcView()
{
	// TODO: add construction code here

}

CTelnetmfcView::~CTelnetmfcView()
{
}

BOOL CTelnetmfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
//	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcView drawing

void CTelnetmfcView::OnDraw(CDC* pDC)
{
	CTelnetmfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcView printing

BOOL CTelnetmfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CTelnetmfcView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CTelnetmfcView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcView diagnostics

#ifdef _DEBUG
void CTelnetmfcView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTelnetmfcView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTelnetmfcDoc* CTelnetmfcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTelnetmfcDoc)));
	return (CTelnetmfcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcView message handlers

void CTelnetmfcView::Message(LPCTSTR lpszMessage)
{
	CString strTemp = lpszMessage;
	int len = GetWindowTextLength();
	GetEditCtrl().SetSel(len,len);
	GetEditCtrl().ReplaceSel(strTemp);
}

void CTelnetmfcView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CTelnetmfcDoc* pDoc = GetDocument();

	if (nChar == VK_RETURN)
	{
		pDoc->DispatchMessage("\r\n");
	}

	else
	{
		CString a;
		a.Format(_T("%c"),nChar);
		pDoc->DispatchMessage(a);
//		CEditView::OnChar(nChar, nRepCnt, nFlags);
		return;
	}
}

int CTelnetmfcView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CClientDC dc (this);
    int nHeight = -((dc.GetDeviceCaps (LOGPIXELSY) * 10) / 72);

    m_font.CreateFont (nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier New");

    SetFont (&m_font, FALSE);

	return 0;
}
