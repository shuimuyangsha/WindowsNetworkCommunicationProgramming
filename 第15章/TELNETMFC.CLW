; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConnectDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Telnetmfc.h"
LastPage=0

ClassCount=6
Class1=CTelnetmfcApp
Class2=CTelnetmfcDoc
Class3=CTelnetmfcView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CConnectDlg
Resource2=IDD_CONNECT
Resource3=IDR_MAINFRAME (English (U.S.))
Resource4=IDD_CONNECT (English (U.S.))

[CLS:CTelnetmfcApp]
Type=0
HeaderFile=Telnetmfc.h
ImplementationFile=Telnetmfc.cpp
Filter=N
LastObject=ID_CONNECT_REMOTESYSTEM

[CLS:CTelnetmfcDoc]
Type=0
HeaderFile=TelnetmfcDoc.h
ImplementationFile=TelnetmfcDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CTelnetmfcView]
Type=0
HeaderFile=TelnetmfcView.h
ImplementationFile=TelnetmfcView.cpp
Filter=C
BaseClass=CEditView
VirtualFilter=VWC
LastObject=CTelnetmfcView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_CONNECT_DISCONNECT




[CLS:CAboutDlg]
Type=0
HeaderFile=Telnetmfc.cpp
ImplementationFile=Telnetmfc.cpp
Filter=D
LastObject=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_CONNECT_REMOTESYSTEM
Command17=ID_CONNECT_DISCONNECT
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_CONNECT_REMOTESYSTEM
Command9=ID_CONNECT_DISCONNECT
Command10=ID_APP_ABOUT
CommandCount=10

[DLG:IDD_CONNECT]
Type=1
Class=CConnectDlg
ControlCount=6
Control1=IDC_EDIT_REMSYS,edit,1350631552
Control2=IDC_EDIT_PORT,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CConnectDlg]
Type=0
HeaderFile=ConnectDlg.h
ImplementationFile=ConnectDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_CONNECT_REMOTESYSTEM

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_CONNECT_REMOTESYSTEM
Command17=ID_CONNECT_DISCONNECT
Command18=ID_APP_ABOUT
CommandCount=18

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_CONNECT_REMOTESYSTEM
Command9=ID_CONNECT_DISCONNECT
Command10=ID_APP_ABOUT
CommandCount=10

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_CONNECT (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDC_EDIT_REMSYS,edit,1350631552
Control2=IDC_EDIT_PORT,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

