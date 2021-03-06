// FtpDlg.h : header file
//

#if !defined(AFX_FTPDLG_H__0E67E7AB_E748_4512_B061_4149D3B9D65F__INCLUDED_)
#define AFX_FTPDLG_H__0E67E7AB_E748_4512_B061_4149D3B9D65F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "FtpOperate.h"
/////////////////////////////////////////////////////////////////////////////
// CFtpDlg dialog

class CFtpDlg : public CDialog
{
// Construction
public:
	CFtpDlg(CWnd* pParent = NULL);	// standard constructor
    

    void  CFtpDlg::ListLocFile();
    void UpdateServerFile();// 更新服务器的文件显示

// Dialog Data
	//{{AFX_DATA(CFtpDlg)
	enum { IDD = IDD_FTP_DIALOG };
	CButton	m_chkAnony;
	CButton	m_ctrBinary;
	CEdit	m_editPort;
	CButton	m_ctrActive;
	CEdit	m_ediMessage;
	CComboBox	m_ctrlLocal;
	CComboBox	m_ctrlServer;
	CListCtrl	m_ctrlServerFile;
	CListCtrl	m_ctrlLocalFile;
	CButton	m_btnClo;
	CButton	m_btnCon;
	CEdit	m_editServer;
	CEdit	m_editPassword;
	CEdit	m_editName;
	CString	m_Message;
	int		m_iActive;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFtpDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFtpOperate cFtpOpr; // FTP连接类实例
	CString m_strServer;  // 记录FTP服务器地址
    CString m_strName;  // 记录FTP登陆用户名
    CString m_strPassword;  // 记录FTP登陆用户密码

    CString m_strCurFolder; // 当前选择的本地文件路径，下载和上传都在这个路径操作
    
    CString m_strLocPath;  // 保存本地文件的当前路径
    CImageList m_imgList; // 图像列表，用于显示文件关联图标
    HICON hIconFold ;
	HICON hIconFile ;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFtpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnConnect();
	afx_msg void OnBtnClose();
	afx_msg void OnDblclkListLocalfile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListServerfile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboboxexLocal();
	afx_msg void OnEditchangeComboboxexLocal();
	afx_msg void OnActive();
	afx_msg void OnPassive();
	afx_msg void OnBtnup();
	afx_msg void OnBtndown();
	afx_msg void OnBtndel();
	afx_msg void OnBtnhelp();
	afx_msg void OnAscii();
	afx_msg void OnBinary();
	afx_msg void OnAuto();
	afx_msg void OnChkanonymous();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPDLG_H__0E67E7AB_E748_4512_B061_4149D3B9D65F__INCLUDED_)
