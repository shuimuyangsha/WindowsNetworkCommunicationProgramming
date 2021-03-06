// TelnetmfcDoc.cpp : implementation of the CTelnetmfcDoc class
//

#include "stdafx.h"
#include "Telnetmfc.h"

#include "TelnetmfcDoc.h"

#include "ClientSocket.h"
#include "TelnetmfcView.h"
#include "ConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcDoc

IMPLEMENT_DYNCREATE(CTelnetmfcDoc, CDocument)

BEGIN_MESSAGE_MAP(CTelnetmfcDoc, CDocument)
	//{{AFX_MSG_MAP(CTelnetmfcDoc)
	ON_COMMAND(ID_CONNECT_REMOTESYSTEM, OnConnectRemotesystem)
	ON_COMMAND(ID_CONNECT_DISCONNECT, OnConnectDisconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcDoc construction/destruction

CTelnetmfcDoc::CTelnetmfcDoc()
{
	// TODO: add one-time construction code here
	m_bBuf.SetSize(1024);
	bOptionsSent = FALSE;
	TempCounter = 0;
	m_sClient = NULL;
}

CTelnetmfcDoc::~CTelnetmfcDoc()
{
}

BOOL CTelnetmfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcDoc serialization

void CTelnetmfcDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcDoc diagnostics

#ifdef _DEBUG
void CTelnetmfcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTelnetmfcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTelnetmfcDoc commands

void CTelnetmfcDoc::ProcessMessage(CClientSocket *cSocket)
{
	int nBytes = cSocket->Receive(m_bBuf.GetData(),m_bBuf.GetSize() );
	if(nBytes != SOCKET_ERROR)
	{
		int ndx = 0;
		while(GetLine(m_bBuf, nBytes, ndx) != TRUE);

		ProcessOptions();
		( (CTelnetmfcView*)m_viewList.GetHead() )->Message(m_strNormalText);
	}
	m_strLine.Empty();
	m_strResp.Empty();



	TempCounter++;

}

BOOL CTelnetmfcDoc::GetLine(const CByteArray &bytes, int nBytes, int &ndx)
{
	BOOL bLine = FALSE;
	while ( bLine == FALSE && ndx < nBytes )
	{
		unsigned char ch = (char)(bytes.GetAt( ndx ));
		
		switch( ch )
		{
		case '\r': // ignore
			m_strLine += "\r\n"; //"CR";
			break;
		case '\n': // end-of-line
//			m_strLine += '\n'; //"LF";
//			bLine = TRUE;
			break;
		default:   // other....
			m_strLine += ch;
			break;
		} 

		++ndx;

		if (ndx == nBytes)
		{
			bLine = TRUE;
		}
	}
	return bLine;
}

void CTelnetmfcDoc::ProcessOptions()
{
	CString m_strTemp;
	CString m_strOption;
	unsigned char ch;
	int ndx;
	int ldx;
	BOOL bScanDone = FALSE;

	m_strTemp = m_strLine;

	while(!m_strTemp.IsEmpty() && bScanDone != TRUE)
	{
		ndx = m_strTemp.Find(IAC);
		if(ndx != -1)
		{
			m_strNormalText += m_strTemp.Left(ndx);
			ch = m_strTemp.GetAt(ndx + 1);
			switch(ch)
			{
			case DO:
			case DONT:
			case WILL:
			case WONT:
				m_strOption		= m_strTemp.Mid(ndx, 3);
				m_strTemp		= m_strTemp.Mid(ndx + 3);
				m_strNormalText	= m_strTemp.Left(ndx);
				m_ListOptions.AddTail(m_strOption);
				break;
			case IAC:
				m_strNormalText	= m_strTemp.Left(ndx);
				m_strTemp		= m_strTemp.Mid(ndx + 1);
				break;
			case SB:
				m_strNormalText = m_strTemp.Left(ndx);
				ldx = m_strTemp.Find(SE);
				m_strOption		= m_strTemp.Mid(ndx, ldx);
				m_ListOptions.AddTail(m_strOption);
				m_strTemp		= m_strTemp.Mid(ldx);
				AfxMessageBox(m_strOption,MB_OK);
				break;
			}
		}

		else
		{
			m_strNormalText = m_strTemp;
			bScanDone = TRUE;
		}
	} 
	
	RespondToOptions();

}

void CTelnetmfcDoc::RespondToOptions()
{
	CString strOption;
	
	while(!m_ListOptions.IsEmpty())
	{
		strOption = m_ListOptions.RemoveHead();

		ArrangeReply(strOption);
	}

	DispatchMessage(m_strResp);
	m_strResp.Empty();
}

void CTelnetmfcDoc::ArrangeReply(CString strOption)
{
	unsigned char Verb;
	unsigned char Option;
	unsigned char Modifier;
	unsigned char ch;
	BOOL bDefined = FALSE;

	Verb = strOption.GetAt(1);
	Option = strOption.GetAt(2);

	switch(Option)
	{
	case 1:	// Echo
	case 3: // Suppress Go-Ahead
		bDefined = TRUE;
		break;
	}

	m_strResp += IAC;

	if(bDefined == TRUE)
	{
		switch(Verb)
		{
		case DO:
			ch = WILL;
			m_strResp += ch;
			m_strResp += Option;
			break;
		case DONT:
			ch = WONT;
			m_strResp += ch;
			m_strResp += Option;
			break;
		case WILL:
			ch = DO;
			m_strResp += ch;
			m_strResp += Option;
			break;
		case WONT:
			ch = DONT;
			m_strResp += ch;
			m_strResp += Option;
			break;
		case SB:
			Modifier = strOption.GetAt(3);
			if(Modifier == SEND)
			{
				ch = SB;
				m_strResp += ch;
				m_strResp += Option;
				m_strResp += IS;
				m_strResp += IAC;
				m_strResp += SE;
			}
			break;
		}
	}

	else
	{
		switch(Verb)
		{
		case DO:
			ch = WONT;
			m_strResp += ch;
			m_strResp += Option;
			break;
		case DONT:
			ch = WONT;
			m_strResp += ch;
			m_strResp += Option;
			break;
		case WILL:
			ch = DONT;
			m_strResp += ch;
			m_strResp += Option;
			break;
		case WONT:
			ch = DONT;
			m_strResp += ch;
			m_strResp += Option;
			break;
		}
	}

}

void CTelnetmfcDoc::DispatchMessage(CString strText)
{
	if(m_sClient)
		m_sClient->Send(strText, strText.GetLength());
}

void CTelnetmfcDoc::OnConnectRemotesystem() 
{
	// TODO: Add your command handler code here
	CConnectDlg Dialog;
	int nResult;

	nResult = Dialog.DoModal();
	if(nResult == IDOK)
	{
		ConnectToHost(Dialog.m_strHost, Dialog.m_nPort);
	}

}

void CTelnetmfcDoc::ConnectToHost(CString m_strHost, UINT m_nPort)
{
	BOOL bOK;
	
	m_sClient = new CClientSocket(this);
	if(m_sClient != NULL)
	{
		bOK = m_sClient->Create();
		if(bOK == TRUE)
		{
			m_sClient->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT | FD_OOB);
			m_sClient->Connect(m_strHost, m_nPort);
		}

		else
		{
			delete m_sClient;
		}
	}

	else
	{
		AfxMessageBox("Could not create new socket",MB_OK);
	}

}

void CTelnetmfcDoc::OnConnectDisconnect() 
{
	// TODO: Add your command handler code here
	if(m_sClient)
	{
		m_sClient->Close();
		AfxMessageBox("Connection to host closed");
	}
}
