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
	strAppName.LoadString(AFX_IDS_APP_TITLE);  // ���Ӧ�ó��������
	pInternetSession = new CInternetSession(strAppName,INTERNET_OPEN_TYPE_PRECONFIG);
    pEdiMes = NULL;
	if(!pInternetSession)
	{
		AfxMessageBox("��ʼ���Ựʧ��!");
		flag = -1;  // ��ʼ��ʧ����Ϊ-1
		return;
	}
	flag =0;  // ��ʼ���ɹ�����־��ʼ��Ϊ0
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
	if (flag == -1) // ��ʵ����ʼ��ʱʧ��
	{
		// �����趨
        strAppName.LoadString(AFX_IDS_APP_TITLE);  // ���Ӧ�ó��������
		pInternetSession = new CInternetSession(strAppName,INTERNET_OPEN_TYPE_PRECONFIG);
		if(!pInternetSession)
		{
			AfxMessageBox("��ʼ���Ựʧ��!");
			flag = -1;  // ��ʼ��ʧ����Ϊ-1
			return 0;
		}
		flag =0;
	}

	// flag ������-1ʱ�Ż������������
	m_strUserName = UserName;    // �û����� 
	m_strPassword = Password; // �û�����
	m_strFullURL = FullURL;  // ����·��


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

// set֮�󼴿ɵ���OpenConnection������,ÿ�ζ�������set��OpenConnection
bool CFtpOperate::OpenConnection()
{

	if (flag ==2)
	{
		// �������ˣ��ȶϿ�
		CloseConnection();
		flag = 1;
	}
	if (flag != 1)
	{
		AfxMessageBox("δ�ɹ�����set����");
		return 0;
	}
	
	CWaitCursor cursor; 
	CString strTemp;
	strTemp = "ftp://";


	// ����URL
	if (!AfxParseURL(m_strFullURL, dwServiceType, m_strServerName, strAppName, nPort))
	{
		CurrentTime=CTime::GetCurrentTime(); 
        
        strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		
        strTime += "�޷����� FTP������ " + m_strFullURL +"\r\n";
		int  nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
		flag = 0;
		return 0;
	}
    
	//��ȡpath
	int nIndex=strTemp.GetLength()+m_strServerName.GetLength();
	m_strFullPath=m_strFullURL.Right(m_strFullURL.GetLength()-nIndex); // ���÷�������ǰ·����
	m_strFullPath += '/';
	// �����ɹ����������
	try 
	{
		CurrentTime=CTime::GetCurrentTime(); 
	    strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			              CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
						  CurrentTime.GetSecond());

        strTime += "׼������FTP������ " + m_strServerName + "........\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
         
		// ��ѡ��������ʱ��m_strUserNameΪanonymous��m_strPassword
		// ��ʹ������ʱΪ�û�������û���������
		if (bPassive1 ==1)  
		{
			// ʹ�ñ�����ʽ
			pFtpConnection = pInternetSession->GetFtpConnection(m_strServerName,m_strUserName,m_strPassword,
				                             myPort,TRUE);
		}
		else
		{
			// ʹ��������ʽ
			pFtpConnection = pInternetSession->GetFtpConnection(m_strServerName,m_strUserName,m_strPassword,
				                                        myPort,FALSE);
		}
		
        if (pFtpConnection == NULL)
		{
			CurrentTime=CTime::GetCurrentTime(); 
			strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
				CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
				CurrentTime.GetSecond());
			
			strTime += "����ʧ��\r\n";
			nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
			pEdiMes->SetSel(nLength,  nLength);  
			pEdiMes->ReplaceSel(strTime); 
			return 0;
			
        }
		CurrentTime=CTime::GetCurrentTime(); 
        strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			              CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
						  CurrentTime.GetSecond());

        strTime += "�ɹ�����FTP������ " + m_strServerName + "\r\n                    ��ǰĿ¼Ϊ��" + m_strFullPath + "\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
		flag = 2; // ���ӳɹ�����Ϊ2 

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
		flag = 0; // ����ʧ��
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
	
	strTime += "------------�ѹر����� ---------\r\n";
	nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
	pEdiMes->SetSel(nLength,  nLength);  
	pEdiMes->ReplaceSel(strTime); 
    flag = 1;  // �رճɹ�
	return 1;
}

 // ���ص�ǰ״̬
 int CFtpOperate::ReStatus()
 {
	 return flag;
 }

 int CFtpOperate::GetFtpFile(CString remote,CString local)						
 {
	 if (flag != 2)
	 {
		 // ����δ�ɹ�
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
		
        strTime += "�����ļ������Ժ� " + remote + ".......\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 

	 pFtpConnection->SetCurrentDirectory(m_strFullPath);
	 if (bBinary1 == 1) 
	 {
		 // �����Ʒ�ʽ
		 goodfile = pFtpConnection->GetFile(m_strFullPath+'/'+remote,local+remote,
			              FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY);
	 }
	 else
	 {
		 if (bBinary1 == 0)
		 {
			 //ASCII��ʽ
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
		
        strTime += "���س���������\r\n";
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
		 
		 strTime += "�����ļ��ɹ��������ڣ�" + local+remote + "\r\n";
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
		 // ����δ�ɹ�
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
	 
	 strTime += "�ϴ��ļ������Ժ�" + local+ "\r\n";
	 nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
	 pEdiMes->SetSel(nLength,  nLength);  
	 pEdiMes->ReplaceSel(strTime);

	 if (bBinary1 == 1) 
	 {
		 // �����Ʒ�ʽ
		 goodfile = pFtpConnection->PutFile(local,m_strFullPath+remote,FTP_TRANSFER_TYPE_BINARY);
	 }
	 else
	 {
		 if (bBinary1 == 0)
		 {
			 //ASCII��ʽ
		     goodfile = pFtpConnection->PutFile(local,m_strFullPath+remote,FTP_TRANSFER_TYPE_ASCII);
		 }
		 else if (bBinary1 == 2)
		 {
			 // �Զ���ʽ
			 goodfile = pFtpConnection->PutFile(local,m_strFullPath+remote,FTP_TRANSFER_TYPE_UNKNOWN);
		 } 
	 }

	 
	 if(!goodfile)
	 {
		  CurrentTime=CTime::GetCurrentTime(); 
		 strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			 CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			 CurrentTime.GetSecond());
		 
		 strTime += "�ϴ�����������\r\n";
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
		 
		 strTime += "�ļ�:"+local + "�ϴ��ɹ�" + "\r\n";
		 nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
		 pEdiMes->SetSel(nLength,  nLength);  
		 pEdiMes->ReplaceSel(strTime);
	 }

	 return 1;
}
int CFtpOperate::GetMultipleFileName(CStringArray *localNameArray)
//localNameArray��Ϊ�������
{
	if (flag != 2)
	{
		// ����δ�ɹ�
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
	//	AfxMessageBox("Ŀ¼Ϊ�ա�");
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

bool CFtpOperate::setNextPath(CString strPath) // ���÷�������һ���ļ�Ŀ¼
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
		
        strTime += "��ǰĿ¼Ϊ��" + m_strFullPath + "\r\n";
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 
  	    return 1;
}
bool CFtpOperate::setBackPath()// ������һ��Ŀ¼  
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
        int i = m_strFullPath.GetLength() - 2; // ʡ������һ����/��
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
				
				strTime += "��ǰĿ¼Ϊ��" + m_strFullPath+ "\r\n";
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

void CFtpOperate::setEidt(CEdit *pEdiMessage) // ��Ϣ����Ŀؼ�ID)
{
	pEdiMes = pEdiMessage;
}
// �Ƴ�,indexΪ0��ʾ�Ƴ��ļ��У�����Ϊ�Ƴ��ļ�
int CFtpOperate::DeleteFTPf(CString remote,int index)  
{
	if (flag != 2)
	 {
		 // ����δ�ɹ�
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
			strTime += "ɾ���ļ��У����Ժ� " + remote + ".......\r\n";
		}
		else
		{
			strTime += "ɾ���ļ������Ժ� " + remote + ".......\r\n";
		}
        
		nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
        pEdiMes->SetSel(nLength,  nLength);  
        pEdiMes->ReplaceSel(strTime); 

	 pFtpConnection->SetCurrentDirectory(m_strFullPath);
        // 
	 if (index == 0)
	 {
		 // ɾ���ļ���
		 goodfile = pFtpConnection->RemoveDirectory(m_strFullPath+'/'+remote);
	 }
	 else
	 {
		 // ɾ���ļ�
		 goodfile = pFtpConnection->Remove(m_strFullPath+'/'+remote);
	 }
		 
     
	 if(!goodfile)
	 {
		  CurrentTime=CTime::GetCurrentTime(); 
	    strTime.Format("%d/%d/%d %d:%d:%d   ",CurrentTime.GetYear(),CurrentTime.GetMonth(),
			CurrentTime.GetDay(),CurrentTime.GetHour(),  CurrentTime.GetMinute(),
			CurrentTime.GetSecond());
		
        strTime += "ɾ��ʧ�ܣ�������\r\n";
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
		 
		 strTime += "ɾ���ļ��ɹ���" +remote + "\r\n";
		 nLength  =  pEdiMes->SendMessage(WM_GETTEXTLENGTH);  
		 pEdiMes->SetSel(nLength,  nLength);  
		 pEdiMes->ReplaceSel(strTime); 
	 }
	 return 1;
}