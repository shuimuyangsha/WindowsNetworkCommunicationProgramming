// FtpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ftp.h"
#include "FtpDlg.h"
#include <windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern bool bPassive1 = FALSE; // Ϊ0ʱʹ�� active ��ʽ��Ϊ1ʱʹ��Passive��ʽ
extern int bBinary1 = 1;  // Ϊ0ʱʹ��ASCII���䷽ʽ��Ϊ1ʱʹ�ö����ƴ��䷽ʽ,Ϊ2ʱ�Զ�ѡ��
extern int  myPort = 21;
extern bool bAnony = 0;  // ʹ��������ʽΪ1����ʹ��Ϊ0 
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
// CFtpDlg dialog

CFtpDlg::CFtpDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFtpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFtpDlg)
	m_Message = _T("");
	m_iActive = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFtpDlg)
	DDX_Control(pDX, IDC_CHKANONYMOUS, m_chkAnony);
	DDX_Control(pDX, IDC_BINARY, m_ctrBinary);
	DDX_Control(pDX, IDC_EDITPORT, m_editPort);
	DDX_Control(pDX, IDC_ACTIVE, m_ctrActive);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_ediMessage);
	DDX_Control(pDX, IDC_COMBOBOXEX_LOCAL, m_ctrlLocal);
	DDX_Control(pDX, IDC_COMBOBOXEX_SERVER, m_ctrlServer);
	DDX_Control(pDX, IDC_LIST_SERVERFILE, m_ctrlServerFile);
	DDX_Control(pDX, IDC_LIST_LOCALFILE, m_ctrlLocalFile);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClo);
	DDX_Control(pDX, IDC_BTN_CONNECT, m_btnCon);
	DDX_Control(pDX, IDC_EDIT_SERVER, m_editServer);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_Message);
	DDX_Radio(pDX, IDC_ACTIVE, m_iActive);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFtpDlg, CDialog)
//{{AFX_MSG_MAP(CFtpDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_LOCALFILE, OnDblclkListLocalfile)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_SERVERFILE, OnDblclkListServerfile)
ON_CBN_SELCHANGE(IDC_COMBOBOXEX_LOCAL, OnSelchangeComboboxexLocal)
ON_CBN_EDITCHANGE(IDC_COMBOBOXEX_LOCAL, OnEditchangeComboboxexLocal)
ON_BN_CLICKED(IDC_ACTIVE, OnActive)
ON_BN_CLICKED(IDC_PASSIVE, OnPassive)
ON_BN_CLICKED(IDC_BTNUP, OnBtnup)
ON_BN_CLICKED(IDC_BTNDOWN, OnBtndown)
ON_BN_CLICKED(IDC_BTNDEL, OnBtndel)
ON_BN_CLICKED(IDC_BTNHELP, OnBtnhelp)
	ON_BN_CLICKED(IDC_ASCII, OnAscii)
	ON_BN_CLICKED(IDC_BINARY, OnBinary)
	ON_BN_CLICKED(IDC_AUTO, OnAuto)
	ON_BN_CLICKED(IDC_CHKANONYMOUS, OnChkanonymous)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtpDlg message handlers

BOOL CFtpDlg::OnInitDialog()
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
	
	m_ctrBinary.SetCheck(1);
    m_ctrActive.SetCheck(1);
    m_editPort.SetWindowText("21");
	bBinary1 = 1; // ʹ�ö�����
    bPassive1 = 0; // ʹ������
    myPort = 21;
	m_imgList.Create(20,20,ILC_COLOR32,0,0); // ����ͼ���б�
    m_imgList.SetBkColor(RGB(255,255,255)); 
    
    hIconFold = ::LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_FOLDER)); // �ļ���ͼ��
	hIconFile = ::LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_FILE));   // �ļ�ͼ��
	m_imgList.Add(hIconFold);
    m_imgList.Add(hIconFile);
	
    m_ctrlLocalFile.SetImageList(&m_imgList,LVSIL_SMALL);  // ����
    m_ctrlServerFile.SetImageList(&m_imgList,LVSIL_SMALL); // ����
    
	m_editName.SetWindowText("anonymous");
	m_editPassword.SetWindowText("");
	m_btnCon.EnableWindow(TRUE);
	m_btnClo.EnableWindow(FALSE);
	
	m_ctrlLocalFile.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlServerFile.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_ctrlLocalFile.InsertColumn(0,"�ļ���",LVCFMT_LEFT,140,0);//������
    m_ctrlLocalFile.InsertColumn(1,"�ļ�����",LVCFMT_LEFT,100,1);
    m_ctrlLocalFile.InsertColumn(2,"�޸�����",LVCFMT_LEFT,100,2);
	m_ctrlServerFile.InsertColumn(0,"�ļ���",LVCFMT_LEFT,140,0);//������
    m_ctrlServerFile.InsertColumn(1,"�ļ�����",LVCFMT_LEFT,100,1);
    m_ctrlServerFile.InsertColumn(2,"�޸�����",LVCFMT_LEFT,100,2);
	
	// ���Ӳ���̷�
	size_t szAllDriveStrings=::GetLogicalDriveStrings(0,NULL);
	TCHAR *pDriveStrings=new TCHAR[szAllDriveStrings+sizeof(_T(" "))];
	GetLogicalDriveStrings(szAllDriveStrings,pDriveStrings);
	size_t szDriveString=::strlen(pDriveStrings);
	while(szDriveString>0)
	{
		m_ctrlLocal.AddString(pDriveStrings);
		pDriveStrings+=szDriveString+1;
		szDriveString=::strlen(pDriveStrings);
	}
	
	int index = m_ctrlLocal.FindString(0,"c:\\");
	m_ctrlLocal.SetCurSel(index);
	m_strLocPath = "c:\\"; // ��ʼ��Ϊc��
	ListLocFile();
	cFtpOpr.setEidt(&m_ediMessage);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFtpDlg::OnPaint() 
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
HCURSOR CFtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFtpDlg::OnBtnConnect() 
{
	// TODO: Add your control notification handler code here
   

    m_editServer.GetWindowText(m_strServer);  // ��¼FTP��������ַ 
    
	CString strtemp;
	m_editPort.GetWindowText(strtemp);
	myPort = ::atoi(strtemp); // ������õĶ˿ں�
	
	int i;
	if (bAnony == 0)
	{
		// ��ʹ������
		m_editName.GetWindowText(m_strName);             // ��¼FTP��½�û���
	    m_editPassword.GetWindowText(m_strPassword);  // ��¼FTP��½�û�����
        
		i = cFtpOpr.set(m_strServer,m_strName,m_strPassword);
	}
	else
	{
		// ʹ������
		CString strNameTemp;
		m_editName.GetWindowText(strNameTemp); // ������½���û���
		i = cFtpOpr.set(m_strServer,strNameTemp,"");			 
	}


	if (i)
	{
		// ���óɹ���������

        if (cFtpOpr.OpenConnection())
		{
			// ���ӳɹ�
			m_btnClo.EnableWindow(TRUE);
			m_btnCon.EnableWindow(FALSE);
			UpdateServerFile();// ���·��������ļ���ʾ
			
			m_ctrlServer.ResetContent();
			CString temp;
			cFtpOpr.GetPath(temp);
			m_ctrlServer.AddString((LPSTR)(LPCTSTR)temp);
            m_ctrlServer.SetCurSel(0);
			m_chkAnony.EnableWindow(FALSE);
			m_ctrActive.EnableWindow(FALSE);
			CButton *temp2 =(CButton*)GetDlgItem(IDC_PASSIVE);
			temp2->EnableWindow(FALSE);
			m_editPort.EnableWindow(FALSE);
        }
		else
		{
			// ����ʧ��
		}
	}
}

void CFtpDlg::OnBtnClose() 
{
	// TODO: Add your control notification handler code here
	// �ر�����
	if (cFtpOpr.CloseConnection())
	{
		// �رճɹ�
		m_btnClo.EnableWindow(FALSE);
		m_btnCon.EnableWindow(TRUE);
		m_ctrlServerFile.DeleteAllItems();
		m_ctrlServer.ResetContent();
		
		m_ctrActive.EnableWindow(TRUE);
		//			m_ctrAscii.EnableWindow(TRUE);
		//			CButton *temp =(CButton*)GetDlgItem(IDC_BINARY);
		//			temp->EnableWindow(TRUE);
		CButton *temp2 =(CButton*)GetDlgItem(IDC_PASSIVE);
		temp2->EnableWindow(TRUE);
		m_editPort.EnableWindow(TRUE);
		m_chkAnony.EnableWindow(TRUE);
		
	}
}

void CFtpDlg::OnDblclkListLocalfile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	POSITION p=m_ctrlLocalFile.GetFirstSelectedItemPosition();
	if (p == NULL)
	{
		return;
	}
	//��ȡ��ѡȡ��λ�õ��±�(��0��ʼ��) 
	int index = m_ctrlLocalFile.GetNextSelectedItem(p);
	//���ѡ�е�����
	//�õ���index��.��0�е�����(�±��0��ʼ)
	CString FirstColumn=m_ctrlLocalFile.GetItemText(index,0);
    CString SecondColumn = m_ctrlLocalFile.GetItemText(index,1);
	if (index == 0) // �����ϲ�Ŀ¼ 
	{
		
		int k = m_strLocPath.GetLength() - 1;
		if (m_strLocPath.Right(2) == ":\\")
		{
			return;
		}
		
		// ɾ���������Ŀ
		int ix = m_ctrlLocal.FindString(0,m_strLocPath);
		if (ix != CB_ERR)
		{
			m_ctrlLocal.DeleteString(ix);
		}
		
        for (int j = k -1; j >= 2;--j) 
		{
			if (m_strLocPath.GetAt(j) == '\\')
			{
				m_strLocPath = m_strLocPath.Left(j+1);
				break;
			}
        }
		ListLocFile();
        *pResult = 0;
		return;
	}
	
	if (SecondColumn=="�ļ���") 
	{
		CString strTemp = FirstColumn;
		m_strLocPath += strTemp + '\\';
        ListLocFile(); // ���±��ش����ļ���ʾ
	}
	else if (SecondColumn=="�ļ�") 
	{
		// �㵽�����ļ��������ϴ�
		if (cFtpOpr.ReStatus()==2)
		{
			cFtpOpr.PutFtpFile(m_strLocPath + FirstColumn,FirstColumn);
			UpdateServerFile();// ���·��������ļ���ʾ
		}
	}
	
	*pResult = 0;
}

void CFtpDlg::OnDblclkListServerfile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��ȡѡ�еĵ�һ��λ��
	
	POSITION p=m_ctrlServerFile.GetFirstSelectedItemPosition();
	if (p == NULL)
	{
		return;
		
	}
	//��ȡ��ѡȡ��λ�õ��±�(��0��ʼ��) 
	int index = m_ctrlServerFile.GetNextSelectedItem(p);
	//���ѡ�е�����
	//�õ���index��.��0�е�����(�±��0��ʼ)
	CString FirstColumn=m_ctrlServerFile.GetItemText(index,0);
    CString SecondColumn = m_ctrlServerFile.GetItemText(index,1);
	CStringArray ServName;	
    int nFileNumber=0;
	
	if (index == 0) // �����ϲ�Ŀ¼ 
	{
		if (cFtpOpr.setBackPath() == 0) 
		{
			*pResult = 0;
			return;
		}
        UpdateServerFile();// ���·��������ļ���ʾ
		
		CString temp;
		m_ctrlServer.ResetContent();
		cFtpOpr.GetPath(temp);
		m_ctrlServer.AddString((LPSTR)(LPCTSTR)temp);
        m_ctrlServer.SetCurSel(0);
		
        *pResult = 0;
		return;
	}
	
	
	//	if (FirstColumn.GetAt(i) =='>' && FirstColumn.GetAt(i-1) == 'R'&& FirstColumn.GetAt(i-2) == 'I'&&
	//		 FirstColumn.GetAt(i-3) == 'D'&& FirstColumn.GetAt(i-4) == '<')
	if (SecondColumn=="�ļ���") 
	{
		if (cFtpOpr.setNextPath(FirstColumn) == 0) 
		{
			*pResult = 0;
			return;
		}
		
		UpdateServerFile();// ���·��������ļ���ʾ
		
		CString temp;
		m_ctrlServer.ResetContent();
		cFtpOpr.GetPath(temp);
		m_ctrlServer.AddString((LPSTR)(LPCTSTR)temp);
        m_ctrlServer.SetCurSel(0);
	}
	else if (SecondColumn=="�ļ�") 
	{
		// �㵽�����ļ�����������
		cFtpOpr.GetFtpFile(FirstColumn,m_strLocPath);
		ListLocFile();
	}
	
	*pResult = 0;
}

// �������ļ��б����
void  CFtpDlg::ListLocFile()
{
	m_ctrlLocalFile.DeleteAllItems();
	int ix = m_ctrlLocal.FindString(0,m_strLocPath);
    if (ix == CB_ERR)
	{
		int iy = m_ctrlLocal.GetCount();
        m_ctrlLocal.SetCurSel(m_ctrlLocal.AddString(m_strLocPath));
    }
	else
	{
		m_ctrlLocal.SetCurSel(m_ctrlLocal.SetCurSel(ix));
	}
	
	int k = 0;
	m_ctrlLocalFile.InsertItem(0,"...�ϲ�Ŀ¼");
    char * lpPath = (LPSTR)(LPCTSTR)m_strLocPath;
    char szFind[300];
    WIN32_FIND_DATA FindFileData;
    
	
    strcpy(szFind,lpPath);
    strcat(szFind,"*.*");
    HANDLE hFind=::FindFirstFile(szFind,&FindFileData);
    //if(INVALID_HANDLE_VALUE==hFind)
	//return;
    while(TRUE)
    {
        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
			CString str = FindFileData.cFileName;
			if (str != '.' && str != "..")
			{
				//str += "<DIR>";
				LVITEM lvitem;
				lvitem.mask = LVIF_IMAGE|LVIF_TEXT;   
				lvitem.iItem = k+1;   
				lvitem.pszText = (LPSTR)(LPCTSTR)str;   
				lvitem.iImage = 0;   
				lvitem.iSubItem =0;   
				m_ctrlLocalFile.InsertItem(&lvitem); 
				
                //m_ctrlLocalFile.InsertItem(k+1,str);//������
				m_ctrlLocalFile.SetItemText(k+1,1,"�ļ���");
                ++k;
			}
			
        }
        else
        {
			// �ļ�
			LVITEM lvitem;
			lvitem.mask = LVIF_IMAGE|LVIF_TEXT;   
			lvitem.iItem = k+1;   
			lvitem.pszText = FindFileData.cFileName;   
			lvitem.iImage = 1;   
			lvitem.iSubItem = 0;   
			m_ctrlLocalFile.InsertItem(&lvitem);    
			
			//m_ctrlLocalFile.InsertItem(k+1,);//������
			
			m_ctrlLocalFile.SetItemText(k+1,1,"�ļ�");
			
			
            ++k;
		}
        if(!FindNextFile(hFind,&FindFileData))break;
    }
	
    FindClose(hFind);
}

void CFtpDlg::OnSelchangeComboboxexLocal() 
{
	// TODO: Add your control notification handler code here
	m_ctrlLocal.SetCurSel(m_ctrlLocal.GetCurSel());
	m_ctrlLocal.GetWindowText(m_strLocPath);
	
    m_ctrlLocal.ResetContent();
	// ���Ӳ���̷�
	size_t szAllDriveStrings=::GetLogicalDriveStrings(0,NULL);
	TCHAR *pDriveStrings=new TCHAR[szAllDriveStrings+sizeof(_T(" "))];
	GetLogicalDriveStrings(szAllDriveStrings,pDriveStrings);
	size_t szDriveString=::strlen(pDriveStrings);
	while(szDriveString>0)
	{
		m_ctrlLocal.AddString(pDriveStrings);
		pDriveStrings+=szDriveString+1;
		szDriveString=::strlen(pDriveStrings);
	}
	
	ListLocFile();
	
}

void CFtpDlg::OnEditchangeComboboxexLocal() 
{
}

void CFtpDlg::OnAscii() 
{
	// TODO: Add your control notification handler code here
		bBinary1 = 0; 
}

void CFtpDlg::OnBinary() 
{
	// TODO: Add your control notification handler code here
		bBinary1 = 1; // ʹ�ö�����
}
// �Զ�ѡ������ƻ�ASCII
void CFtpDlg::OnAuto() 
{
	// TODO: Add your control notification handler code here

	bBinary1 = 2; // �Զ�
}


void CFtpDlg::OnActive() 
{
	// TODO: Add your control notification handler code here
	bPassive1 = 0;
}

void CFtpDlg::OnPassive() 
{
	// TODO: Add your control notification handler code here
	bPassive1 = 1;
}

// �ϴ�
void CFtpDlg::OnBtnup() 
{
	// TODO: Add your control notification handler code here
	POSITION p=m_ctrlLocalFile.GetFirstSelectedItemPosition();
	if (p == NULL)
	{
		
		return;
	}
	
	//��ȡ��ѡȡ��λ�õ��±�(��0��ʼ��) 
	int index = m_ctrlLocalFile.GetNextSelectedItem(p);
	//���ѡ�е�����
	//�õ���index��.��0�е�����(�±��0��ʼ)
	CString FirstColumn=m_ctrlLocalFile.GetItemText(index,0);
    CString SecondColumn = m_ctrlLocalFile.GetItemText(index,1);
	
	if (SecondColumn=="�ļ���") 
	{
		
		CTime CurrentTime=CTime::GetCurrentTime(); 
		CString strTime;
		strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		
        strTime += "�ݲ�֧���ϴ��ļ���!\r\n";
		int nLength  =  m_ediMessage.SendMessage(WM_GETTEXTLENGTH);  
        m_ediMessage.SetSel(nLength,  nLength);  
        m_ediMessage.ReplaceSel(strTime); 
		return;
	}
	else if (SecondColumn=="�ļ�") 
	{
		// �㵽�����ļ��������ϴ�
		if (cFtpOpr.ReStatus()==2)
		{
			cFtpOpr.PutFtpFile(m_strLocPath + FirstColumn,FirstColumn);
            UpdateServerFile();// ���·��������ļ���ʾ
		}
	}
}

//����
void CFtpDlg::OnBtndown() 
{
	// TODO: Add your control notification handler code here
	POSITION p=m_ctrlServerFile.GetFirstSelectedItemPosition();
	if (p == NULL)
	{
		
		return;
	}
	
	//��ȡ��ѡȡ��λ�õ��±�(��0��ʼ��) 
	int index = m_ctrlServerFile.GetNextSelectedItem(p);
	//���ѡ�е�����
	//�õ���index��.��0�е�����(�±��0��ʼ)
	CString FirstColumn=m_ctrlServerFile.GetItemText(index,0);
    CString SecondColumn = m_ctrlServerFile.GetItemText(index,1);
	
	if (SecondColumn=="�ļ���") 
	{
		
		CTime CurrentTime=CTime::GetCurrentTime(); 
		CString strTime;
		strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		
        strTime += "�ݲ�֧�������ļ���!\r\n";
		int nLength  =  m_ediMessage.SendMessage(WM_GETTEXTLENGTH);  
        m_ediMessage.SetSel(nLength,  nLength);  
        m_ediMessage.ReplaceSel(strTime); 
		return;
	}
	else if (SecondColumn=="�ļ�") 
	{
		// �㵽�����ļ�����������
		if (cFtpOpr.ReStatus()==2)
		{
			// �㵽�����ļ�����������
			cFtpOpr.GetFtpFile(FirstColumn,m_strLocPath);
			ListLocFile();  // ������ɺ���±����ļ���ʾ
		}
	}
	
}
// ɾ���������ļ����ļ���
void CFtpDlg::OnBtndel() 
{
	// TODO: Add your control notification handler code here
	POSITION p=m_ctrlServerFile.GetFirstSelectedItemPosition();
	if (p == NULL)
	{
		return;
	}
	
	//��ȡ��ѡȡ��λ�õ��±�(��0��ʼ��) 
	int index = m_ctrlServerFile.GetNextSelectedItem(p);
	//���ѡ�е�����
	//�õ���index��.��0�е�����(�±��0��ʼ)
	CString FirstColumn=m_ctrlServerFile.GetItemText(index,0);
    CString SecondColumn = m_ctrlServerFile.GetItemText(index,1);
	
	if (SecondColumn=="�ļ���") 
	{
		if (cFtpOpr.ReStatus()==2)
		{
			// �Ƴ��ļ���
			cFtpOpr.DeleteFTPf(FirstColumn,0); 
			UpdateServerFile();// ���·��������ļ���ʾ
		}
		
		return;
	}
	else if (SecondColumn=="�ļ�") 
	{
		
		if (cFtpOpr.ReStatus()==2)
		{	// �Ƴ��ļ�
			cFtpOpr.DeleteFTPf(FirstColumn,1);
			UpdateServerFile();// ���·��������ļ���ʾ
		}
	}
}

void CFtpDlg::UpdateServerFile()// ���·��������ļ���ʾ
{
				// ���Ŀ¼
	CStringArray localName;	
	int nFileNumber=0;
	nFileNumber=cFtpOpr.GetMultipleFileName(&localName);
			 
	m_ctrlServerFile.DeleteAllItems();
	m_ctrlServerFile.InsertItem(0,"...�ϲ�Ŀ¼");
    for(int test=0;test<nFileNumber;test++)
	{
				 
		CString stTemp = localName.GetAt(test);
				 
		if (stTemp.Right(5) == "<DIR>")
		{
					 // �ļ���
			LVITEM lvitem;
			CString str = stTemp.Left(stTemp.GetLength() - 5);
			lvitem.mask = LVIF_IMAGE|LVIF_TEXT;   
			lvitem.iItem =test+1;   
			lvitem.pszText = (LPSTR)(LPCTSTR)str;   
			lvitem.iImage = 0;   
			lvitem.iSubItem =0;   
			m_ctrlServerFile.InsertItem(&lvitem); 
			m_ctrlServerFile.SetItemText(test+1,1,"�ļ���");
		}
		else
		{
					 // �ļ�
			LVITEM lvitem;
			lvitem.mask = LVIF_IMAGE|LVIF_TEXT;   
			lvitem.iItem =test+1;   
			lvitem.pszText = (LPSTR)(LPCTSTR)stTemp;   
			lvitem.iImage = 1;   
			lvitem.iSubItem =0;   
			m_ctrlServerFile.InsertItem(&lvitem); 
			m_ctrlServerFile.SetItemText(test+1,1,"�ļ�");
		}
	}
			 
}

void CFtpDlg::OnBtnhelp() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}
// �������ΰ��»س��������˳�������
BOOL CFtpDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if( pMsg->message ==WM_KEYDOWN && pMsg->wParam==VK_RETURN  )
	{
		return true;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

// ��ѡ���Ƿ�����
void CFtpDlg::OnChkanonymous() 
{
	// TODO: Add your control notification handler code here

	if (m_chkAnony.GetCheck())
	{
		// ��ѡ��
		
		bAnony = 1; // ʹ������
		m_editName.GetWindowText(m_strName);          // ��¼FTP��½�û��������ڲ�ʹ��������ָ�
	    m_editPassword.GetWindowText(m_strPassword);  // ��¼FTP��½�û����룬���ڲ�ʹ��������ָ�

        m_editName.SetWindowText("anonymous");
		m_editPassword.SetWindowText("");
		m_editName.EnableWindow(FALSE);
		m_editPassword.EnableWindow(FALSE);
	}
	else
	{
		bAnony = 0; // ��ʹ������
		m_editName.SetWindowText(m_strName);          // �ָ�
	    m_editPassword.SetWindowText(m_strPassword);  // �ָ�
		m_editName.EnableWindow(TRUE);
		m_editPassword.EnableWindow(TRUE);
	}
	
}
