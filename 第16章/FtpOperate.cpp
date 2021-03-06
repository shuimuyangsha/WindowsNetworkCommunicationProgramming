// FtpOperate.cpp: implementation of the CFtpOperate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ftp.h"
#include "FtpOperate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__; 
#define new DEBUG_NEW
#endif
#include "FtpDlg.h"

extern bool bPassive1;
extern int bBinary1;
extern int myPort;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpOperate::CFtpOperate()
{
	strAppName.LoadString(AFX_IDS_APP_TITLE);  // 获得应用程序的名字
	pInternetSession = new CInternetSession(strAppName,INTERNET_OPEN_TYPE_PRECONFIG);
    pEdiMes = NULL;
	if(!pInternetSession)
	{
		AfxMessageBox("初始化会话失败!");
		flag = -1;  // 初始化失败设为-1
		return;
	}
	flag =0;  // 初始化成功，标志初始化为0
}                                                                                                                       

CFtpOperate::~CFtpOperate()
{
	pInternetSession->Close();
	// delete the session
	if(pInternetSession != NULL)
	{
		delete pInternetSession;
	}
	
}


bool CFtpOperate::set(CString FullURL,CString UserName,CString Password)
{
	if (flag == -1) // 类实例初始化时失败
	{
		// 重新设定
        strAppName.LoadString(AFX_IDS_APP_TITLE);  // 获得应用程序的名字
		pInternetSession = new CInternetSession(strAppName,INTERNET_OPEN_TYPE_PRECONFIG);
		if(!pInternetSession)
		{
			AfxMessageBox("初始化会话失败!");
			flag = -1;  // 初始化失败设为-1
			return 0;
		}
		flag =0;
	}

	// flag 不等于-1时才会进行以下设置
	m_strUserName = UserName;    // 用户名字 
	m_strPassword = Password; // 用户密码
	m_strFullURL = FullURL;  // 设置路径


    if(m_strFullURL == "" || m_strUserName == "")
	{
		
		flag = 0;
    }
	else
	{
		if (m_strFullURL.Left(6) != "ftp://")
		{
			m_strFullURL = "ftp://" + m_strFullURL;
		}
		flag = 1;
		return 1;
	}
    return 0;	
}

// set之后即可调用OpenConnection打开连接,每次都必须先set在OpenConnection
bool CFtpOperate::OpenConnection()
{

	if (flag ==2)
	{
		// 已连接了，先断开
		CloseConnection();
		flag = 1;
	}
	if (flag != 1)
	{
		AfxMessageBox("未成功进行set调用");
		return 0;
	}
	
	CWaitCursor cursor; 
	CString strTemp;
	strTemp = "ftp://";


	// 解析URL
	if (!AfxParseURL(m_strFullURL, dwServiceType, m_strServerName, strAppName, nPort))
	{
		CurrentTime=CTime::GetCurrentTime(); 
        
        strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		
        strTime += "无法解析 FTP服务器 " + m_strFullURL +"\r\n";
		int  nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
		flag = 0;
		return 0;
	}
    
	//提取path
	int nIndex=strTemp.GetLength()+m_strServerName.GetLength();
	m_strFullPath=m_strFullURL.Right(m_strFullURL.GetLength()-nIndex); // 设置服务器当前路径名
	m_strFullPath += '/';
	// 解析成功后进行连接
	try 
	{
		CurrentTime=CTime::GetCurrentTime(); 
	    strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			              CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
						  CurrentTime.GetSecond());

        strTime += "准备连接FTP服务器 " + m_strServerName + "........\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
         
		// 当选择匿名的时候，m_strUserName为anonymous，m_strPassword
		// 不使用匿名时为用户输入的用户名和密码
		if (bPassive1 ==1)  
		{
			// 使用被动方式
			pFtpConnection = pInternetSession->GetFtpConnection(m_strServerName,m_strUserName,m_strPassword,
				                             myPort,TRUE);
		}
		else
		{
			// 使用主动方式
			pFtpConnection = pInternetSession->GetFtpConnection(m_strServerName,m_strUserName,m_strPassword,
				                                        myPort,FALSE);
		}
		
        if (pFtpConnection == NULL)
		{
			CurrentTime=CTime::GetCurrentTime(); 
			strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
				CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
				CurrentTime.GetSecond());
			
			strTime += "连接失败\r\n";
			nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
			pEdiMes->SetSel(nLength,  nLength);  
			pEdiMes->ReplaceSel(strTime); 
			return 0;
			
        }
		CurrentTime=CTime::GetCurrentTime(); 
        strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			              CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
						  CurrentTime.GetSecond());

        strTime += "成功连接FTP服务器 " + m_strServerName + "\r\n                    当前目录为：" + m_strFullPath + "\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
		flag = 2; // 连接成功后设为2 

	} 
	catch (CInternetException* pEx) 
	{
		TCHAR szErr[1024];
		pEx->GetErrorMessage(szErr, 1024);
		TRACE(szErr);
		CurrentTime=CTime::GetCurrentTime(); 
        strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			              CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
						  CurrentTime.GetSecond());
        strTime = strTime + " " + szErr + "\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
		pEx->Delete();
		flag = 0; // 连接失败
		return 0;
	}
	return 1;
}

bool CFtpOperate::CloseConnection()
{
	// close the connection to server, you can reconnect latter

	if(pFtpConnection == NULL)
	{
		return 1;
	}
	
	try
	{
		pFtpConnection->Close();
	}
	catch(...)
	{
		return 0;
	}
	if(pFtpConnection != NULL)
	{
		delete pFtpConnection;
	}

	CurrentTime=CTime::GetCurrentTime(); 
	strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
		CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
						  CurrentTime.GetSecond());
	
	strTime += "------------已关闭连接 ---------\r\n";
	nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
	pEdiMes->SetSel(nLength,  nLength);  
	pEdiMes->ReplaceSel(strTime); 
    flag = 1;  // 关闭成功
	return 1;
}

 // 返回当前状态
 int CFtpOperate::ReStatus()
 {
	 return flag;
 }

 int CFtpOperate::GetFtpFile(CString remote,CString local)						
 {
	 if (flag != 2)
	 {
		 // 连接未成功
		 return 0;
	 }
	 
	 CWaitCursor cursor;
	 // init some var
	 BOOL goodfile;
	 int x=0;

	 CurrentTime=CTime::GetCurrentTime(); 
	    strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		
        strTime += "下载文件，请稍候： " + remote + ".......\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 

	 pFtpConnection->SetCurrentDirectory(m_strFullPath);
	 if (bBinary1 == 1) 
	 {
		 // 二进制方式
		 goodfile = pFtpConnection->GetFile(m_strFullPath+'/'+remote,local+remote,
			              FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY);
	 }
	 else
	 {
		 if (bBinary1 == 0)
		 {
			 //ASCII方式
		     goodfile = pFtpConnection->GetFile(m_strFullPath+'/'+remote,local+remote,
			      FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_ASCII);
		 }
		 else if (bBinary1 == 2)
		 {
              goodfile = pFtpConnection->GetFile(m_strFullPath+'/'+remote,local+remote,
			      FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_UNKNOWN);
		 }
		 
	 }
     
	 if(!goodfile)
	 {
		  CurrentTime=CTime::GetCurrentTime(); 
	    strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		
        strTime += "下载出错，请重试\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
		return 0;
	 }
	 else
	 {
		 CurrentTime=CTime::GetCurrentTime(); 
		 strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			 CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			 CurrentTime.GetSecond());
		 
		 strTime += "下载文件成功，保存于：" + local+remote + "\r\n";
		 nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
		 pEdiMes->SetSel(nLength,  nLength);  
		 pEdiMes->ReplaceSel(strTime); 
	 }
	 return 1;
}
int CFtpOperate::PutFtpFile(CString local,CString remote)
{
	 if (flag != 2)
	 {
		 // 连接未成功
		 return 0;
	 }
	 CWaitCursor cursor;
	 BOOL goodfile;
	 int x=0;

	 pFtpConnection->SetCurrentDirectory(m_strFullPath);
	 CurrentTime=CTime::GetCurrentTime(); 
	 strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
		 CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
		 CurrentTime.GetSecond());
	 
	 strTime += "上传文件，请稍候：" + local+ "\r\n";
	 nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
	 pEdiMes->SetSel(nLength,  nLength);  
	 pEdiMes->ReplaceSel(strTime);

	 if (bBinary1 == 1) 
	 {
		 // 二进制方式
		 goodfile = pFtpConnection->PutFile(local,m_strFullPath+remote,FTP_TRANSFER_TYPE_BINARY);
	 }
	 else
	 {
		 if (bBinary1 == 0)
		 {
			 //ASCII方式
		     goodfile = pFtpConnection->PutFile(local,m_strFullPath+remote,FTP_TRANSFER_TYPE_ASCII);
		 }
		 else if (bBinary1 == 2)
		 {
			 // 自动方式
			 goodfile = pFtpConnection->PutFile(local,m_strFullPath+remote,FTP_TRANSFER_TYPE_UNKNOWN);
		 } 
	 }

	 
	 if(!goodfile)
	 {
		  CurrentTime=CTime::GetCurrentTime(); 
		 strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			 CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			 CurrentTime.GetSecond());
		 
		 strTime += "上传出错，请重试\r\n";
		 nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
		 pEdiMes->SetSel(nLength,  nLength);  
		 pEdiMes->ReplaceSel(strTime);
		 return 0;
	 }
	 else
	 {
		  CurrentTime=CTime::GetCurrentTime(); 
		 strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			 CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			 CurrentTime.GetSecond());
		 
		 strTime += "文件:"+local + "上传成功" + "\r\n";
		 nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
		 pEdiMes->SetSel(nLength,  nLength);  
		 pEdiMes->ReplaceSel(strTime);
	 }

	 return 1;
}
int CFtpOperate::GetMultipleFileName(CStringArray *localNameArray)
//localNameArray作为输出参数
{
	if (flag != 2)
	{
		// 连接未成功
		return 0;
	}
	CWaitCursor cursor;
	// init some var
	BOOL goodfile;
	int x=0;
	int nFileNumber=0;  
	
//	if (m_strFullPath == "/" || m_strFullPath =="")
//	{
//        m_strFullPath = "/";
//    }
//	else
//	{
//		m_strFullPath = m_strFullPath +'/';
//	}
    
	pFtpConnection->SetCurrentDirectory(m_strFullPath);
	
	//AfxMessageBox(m_strFullPath +"99++++22");
	CFtpFileFind fFiles(pFtpConnection);
	goodfile=fFiles.FindFile(m_strFullPath+"*");
	
	if(goodfile==FALSE)
	{
	//	AfxMessageBox("目录为空。");
		fFiles.Close();
		return 0;
	}

	// while loop to transfer every file in the array
	CString str;
	while(goodfile)
	{
	    goodfile=fFiles.FindNextFile();

		 // try to get file name

	    str=fFiles.GetFileName();
	
	   if(fFiles.IsDirectory())
		{
			str+="<DIR>";
		}
	   	localNameArray->InsertAt(x,str);
		nFileNumber++;
		x++;
	}
     fFiles.Close();
	//return the number of missing file, if any.
	return nFileNumber;
}

bool CFtpOperate::setNextPath(CString strPath) // 设置服务器下一层文件目录
{
//        CString str;
//    	pFtpConnection->GetCurrentDirectoryAsURL(str);
//		int i = m_strFullURL.GetLength() - 1;
//		int j = str.GetLength() - 1;
//		//AfxMessageBox(str);
//		if (i < j)
//		{
//           m_strFullPath = str.Right(j - i);
//		}
	   
		CString temp = m_strFullPath;
		int i = m_strFullPath.GetLength() - 1;
		if (m_strFullPath.GetAt(i)!='/') 
		{
           m_strFullPath +='/';
		}
        m_strFullPath +=  strPath + '/';
		CurrentTime=CTime::GetCurrentTime(); 
		strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		
        strTime += "当前目录为：" + m_strFullPath + "\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
  	    return 1;
}
bool CFtpOperate::setBackPath()// 返回上一层目录  
{
        CString str;
    	pFtpConnection->GetCurrentDirectoryAsURL(str);
		int i = m_strFullURL.GetLength() - 1;
		int j = str.GetLength() - 1;
		//AfxMessageBox(str);
		if (i < j)
		{
           m_strFullPath = str.Right(j - i);
		}

	if (m_strFullPath == '/')
	{
       return 0;
	}
	else
	{
        int i = m_strFullPath.GetLength() - 2; // 省略最后的一个‘/’
		for (;i>=0;--i)
		{
			if (m_strFullPath.GetAt(i) == '/')
			{
				CString temp;
				temp = m_strFullPath.Left(i);
				m_strFullPath = temp;
				m_strFullPath +='/';
				CurrentTime=CTime::GetCurrentTime(); 
				strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
					CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
					CurrentTime.GetSecond());
				
				strTime += "当前目录为：" + m_strFullPath+ "\r\n";
				nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
				pEdiMes->SetSel(nLength,  nLength);  
				pEdiMes->ReplaceSel(strTime); 
				
				return 1;
			}
		}
	}

	return 1;
}


void CFtpOperate::GetPath(CString &temp)
{
	temp =  m_strFullPath;
}

void CFtpOperate::setEidt(CEdit *pEdiMessage) // 信息输出的控件ID)
{
	pEdiMes = pEdiMessage;
}
// 移除,index为0表示移除文件夹，否则为移除文件
int CFtpOperate::DeleteFTPf(CString remote,int index)  
{
	if (flag != 2)
	 {
		 // 连接未成功
		 return 0;
	 }
	 
	 CWaitCursor cursor;
	 // init some var
	 BOOL goodfile;
	 int x=0;

	 CurrentTime=CTime::GetCurrentTime(); 
	    strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		if (index == 0)
		{
			strTime += "删除文件夹，请稍候： " + remote + ".......\r\n";
		}
		else
		{
			strTime += "删除文件，请稍候： " + remote + ".......\r\n";
		}
        
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 

	 pFtpConnection->SetCurrentDirectory(m_strFullPath);
        // 
	 if (index == 0)
	 {
		 // 删除文件夹
		 goodfile = pFtpConnection->RemoveDirectory(m_strFullPath+'/'+remote);
	 }
	 else
	 {
		 // 删除文件
		 goodfile = pFtpConnection->Remove(m_strFullPath+'/'+remote);
	 }
		 
     
	 if(!goodfile)
	 {
		  CurrentTime=CTime::GetCurrentTime(); 
	    strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		
        strTime += "删除失败，请重试\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
		return 0;
	 }
	 else
	 {
		 CurrentTime=CTime::GetCurrentTime(); 
		 strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			 CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			 CurrentTime.GetSecond());
		 
		 strTime += "删除文件成功：" +remote + "\r\n";
		 nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
		 pEdiMes->SetSel(nLength,  nLength);  
		 pEdiMes->ReplaceSel(strTime); 
	 }
	 return 1;
}