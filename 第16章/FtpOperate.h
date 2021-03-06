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
	bool OpenConnection();  // 打开连接
	bool CloseConnection(); // 关闭连接
    int ReStatus();  // 返回flag状态 
	int GetMultipleFileName(CStringArray *localNameArray);
    int GetFtpFile(CString remote,CString local);
	int PutFtpFile(CString local,CString remote);
    bool setNextPath(CString strPath); // 设置服务器下一层文件目录
	bool setBackPath(); // 返回上一层目录  
	void GetPath(CString &temp);
	void setEidt(CEdit *pEdiMessage); // 信息输出的控件ID)
	int DeleteFTPf(CString remote,int index);
private:
	int flag; // 初始化失败设为-1，初始化成功为0，set设置成功后为1，连接成功为2
    CEdit	*pEdiMes; // 信息输出的控件ID
	CString m_strServerName;  // FTP服务器名字
    CString m_strFullURL;  // FTP服务器的URL
    CString m_strPreURL;  // 服务器的上层URL

	CString m_strUserName;    // 用户名字 
	CString m_strPassword; // 用户密码
    INTERNET_PORT nPort;  // 端口号

    CString m_strFullPath; // 服务器上的当前路径名
    
	// 消息使用
	CTime CurrentTime; 
    CString strTime; 
    int  nLength;

	DWORD dwServiceType;
	CInternetSession *pInternetSession;
	CFtpConnection *pFtpConnection;

public:
	CString strAppName;  // 记录应用程序的名字

};

#endif // !defined(AFX_FTPOPERATE_H__1569CF50_F2DA_4C07_81B9_AC95B8303FEB__INCLUDED_)
