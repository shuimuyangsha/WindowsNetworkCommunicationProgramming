// FtpOperate.h: interface for the CFtpOperate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPOPERATE_H__1569CF50_F2DA_4C07_81B9_AC95B8303FEB__INCLUDED_)
#define AFX_FTPOPERATE_H__1569CF50_F2DA_4C07_81B9_AC95B8303FEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxinet.h>
class CFtpOperate  
{
public:
	CFtpOperate();
	virtual ~CFtpOperate();

    bool set(CString FullURL,CString UserName,CString Password);
	bool OpenConnection();  // ������
	bool CloseConnection(); // �ر�����
    int ReStatus();  // ����flag״̬ 
	int GetMultipleFileName(CStringArray *localNameArray);
    int GetFtpFile(CString remote,CString local);
	int PutFtpFile(CString local,CString remote);
    bool setNextPath(CString strPath); // ���÷�������һ���ļ�Ŀ¼
	bool setBackPath(); // ������һ��Ŀ¼  
	void GetPath(CString &temp);
	void setEidt(CEdit *pEdiMessage); // ��Ϣ����Ŀؼ�ID)
	int DeleteFTPf(CString remote,int index);
private:
	int flag; // ��ʼ��ʧ����Ϊ-1����ʼ���ɹ�Ϊ0��set���óɹ���Ϊ1�����ӳɹ�Ϊ2
    CEdit	*pEdiMes; // ��Ϣ����Ŀؼ�ID
	CString m_strServerName;  // FTP����������
    CString m_strFullURL;  // FTP��������URL
    CString m_strPreURL;  // ���������ϲ�URL

	CString m_strUserName;    // �û����� 
	CString m_strPassword; // �û�����
    INTERNET_PORT nPort;  // �˿ں�

    CString m_strFullPath; // �������ϵĵ�ǰ·����
    
	// ��Ϣʹ��
	CTime CurrentTime; 
    CString strTime; 
    int  nLength;

	DWORD dwServiceType;
	CInternetSession *pInternetSession;
	CFtpConnection *pFtpConnection;

public:
	CString strAppName;  // ��¼Ӧ�ó��������

};

#endif // !defined(AFX_FTPOPERATE_H__1569CF50_F2DA_4C07_81B9_AC95B8303FEB__INCLUDED_)
