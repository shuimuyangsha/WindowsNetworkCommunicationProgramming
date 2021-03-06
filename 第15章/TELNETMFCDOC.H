// TelnetmfcDoc.h : interface of the CTelnetmfcDoc class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TELNETMFCDOC_H__2960826F_DD2C_412E_9EEA_D208840E0E77__INCLUDED_)
#define AFX_TELNETMFCDOC_H__2960826F_DD2C_412E_9EEA_D208840E0E77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const	unsigned char IAC		= 255;
const	unsigned char DO		= 253;
const	unsigned char DONT		= 254;
const	unsigned char WILL		= 251;
const	unsigned char WONT		= 252;
const	unsigned char SB		= 250;
const	unsigned char SE		= 240;
const	unsigned char IS		= '0';
const	unsigned char SEND		= '1';
const	unsigned char INFO		= '2';
const	unsigned char VAR		= '0';
const	unsigned char VALUE		= '1';
const	unsigned char ESC		= '2';
const	unsigned char USERVAR	= '3';


class CClientSocket;

class CTelnetmfcDoc : public CDocument
{
protected: // create from serialization only
	CTelnetmfcDoc();
	DECLARE_DYNCREATE(CTelnetmfcDoc)

// Attributes
public:
	CByteArray m_bBuf;
	CString m_strNormalText;
	CString m_strLine;
	CStringList m_ListOptions;
	CString m_strResp;
	int TempCounter;
	CClientSocket* m_sClient;
	BOOL bOptionsSent;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelnetmfcDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ConnectToHost(CString m_strHost, UINT m_nPort);
	void DispatchMessage(CString strText);
	void RespondToOptions();
	void ProcessOptions();
	BOOL GetLine( const CByteArray& bytes, int nBytes, int& ndx );
	void ProcessMessage(CClientSocket * cSocket);
	virtual ~CTelnetmfcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTelnetmfcDoc)
	afx_msg void OnConnectRemotesystem();
	afx_msg void OnConnectDisconnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	void ArrangeReply(CString strOption);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TELNETMFCDOC_H__2960826F_DD2C_412E_9EEA_D208840E0E77__INCLUDED_)
