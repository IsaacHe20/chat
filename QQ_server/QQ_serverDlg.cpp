// QQ_serverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QQ_server.h"
#include "QQ_serverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CQQ_serverDlg dialog

CQQ_serverDlg::CQQ_serverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQQ_serverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQQ_serverDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//��ʼ���ͻ��˳�Ա�б�
	for(int i=0;i<5;i++)
	{
		info[i].isUsed = false;
	}
}

void CQQ_serverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQQ_serverDlg)
	DDX_Control(pDX, IDC_MEMBER, m_memlist);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQQ_serverDlg, CDialog)
	//{{AFX_MSG_MAP(CQQ_serverDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTRUN, OnStartrun)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SOCKET,OnSocket)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQQ_serverDlg message handlers

BOOL CQQ_serverDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	//��ʼ��ͼ���б��
	InitListView();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQQ_serverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQQ_serverDlg::OnPaint() 
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
HCURSOR CQQ_serverDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CQQ_serverDlg::OnStartrun() 
{
	// TODO: Add your control notification handler code here
	//�����׽��ֿ�
	WORD	ver = MAKEWORD(2,0);
	WSADATA	wsadata;
	if( WSAStartup(ver,&wsadata) )
	{
		AfxMessageBox("�����׽��ֿ�ʧ��");
		return;
	}
	
	//��������TCP���׽���
	socket_server = socket(AF_INET,SOCK_STREAM,NULL);
	if( INVALID_SOCKET == socket_server )
	{
		AfxMessageBox("�����׽���ʧ��");
		return;
	}
	
	//��ȡ������ip��ַ
	char host_name[20] = "";
	gethostname(host_name,20);
	hostent *tent = gethostbyname(host_name);
	in_addr	ip_addr;
	memmove(&ip_addr,tent->h_addr_list[0],4);
	
	//�󶨶˿ںź�ip
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port	= htons(3050);		//Ĭ�����õĶ˿ں�
	addr.sin_addr	= ip_addr;
	if( bind(socket_server,(sockaddr *)&addr,sizeof(sockaddr)) )
	{
		AfxMessageBox("�󶨶˿ںź�ip����");
		return;
	}
	
	//����
	listen(socket_server,5);
	
	//�����첽�׽���
	if( SOCKET_ERROR == WSAAsyncSelect(socket_server,this->m_hWnd,WM_SOCKET,
		FD_ACCEPT | FD_CLOSE | FD_READ) )
	{
		AfxMessageBox("�첽�׽������ó���");
		return;
	}

	//��ʾ��Ϣ
	AfxMessageBox("�����������ɹ�");
	GetDlgItem(IDC_STARTRUN)->EnableWindow(false);		//���á���������������ť
}

void CQQ_serverDlg::OnSocket(WPARAM wParam,LPARAM lParam)
{
	SOCKET		sock_temp = SOCKET_ERROR;
	sockaddr_in addr;
	int			len = sizeof(sockaddr_in);
	char		buf_recv[256] = "";			//��ʱ�洢���յ�����Ϣ
	CString		str_name = "";
	
	switch(lParam)
	{
	case FD_ACCEPT:
		sock_temp = accept(socket_server,(sockaddr *)&addr,&len);
		if( INVALID_SOCKET == sock_temp)
		{
			AfxMessageBox("���տͻ��˵���������ʧ��");
			return;
		}
		break;
		
	case FD_CLOSE:
		sock_temp = (SOCKET)wParam;
		if(!delMember(sock_temp))
		{
			return;
		}
		//ͳһ�������г�Ա��ͼ���б���Ϣ
		SendAllMem();			//��װ�ĺ���
		break;
		
	case FD_READ:	
		sock_temp = (SOCKET)wParam;
		if( SOCKET_ERROR == recv(sock_temp,buf_recv,256,NULL) )
		{
			AfxMessageBox("���տͻ������Ƴ���");
			return;
		}
		
		//���տͻ��˷������û�����Ϣ
		if(buf_recv[0] == 'F')
		{
			str_name = getKeyMsg(buf_recv,"From");
			//��ӳ�Ա
			if( !addMember(str_name,sock_temp) )
			{
				return;
			}
			//ͳһ�������г�Ա��ͼ���б���Ϣ
			SendAllMem();			//��װ�ĺ���
			return;
		}
		
		//ת���û���������Ϣ
		TransMsg(buf_recv);
		return;
		
		break;
	}
}

//ת���û���������Ϣ
void CQQ_serverDlg::TransMsg(CString recv_msg)
{
	//ȡ��To��������Ϣ
	CString to_name = getKeyMsg(recv_msg,"To");
	//���Ҷ�Ӧ��socket
	SOCKET	sock_temp = SOCKET_ERROR;
	for(int i=0;i<5;i++)
	{
		if(info[i].isUsed == true && info[i].name == to_name)
		{
			sock_temp = info[i].user_socket;
			break;
		}
	}
	//ת����Ϣ
	if( SOCKET_ERROR == send(sock_temp,recv_msg,recv_msg.GetLength(),NULL) )
	{
		AfxMessageBox("��Ϣת������");
		return;
	}
}

//��ͻ��˳�Ա�б�����ӳ�Ա
BOOL CQQ_serverDlg::addMember(CString name,SOCKET sock)
{
	for(int i=0;i<5;i++)
	{
		if(info[i].isUsed == false)
		{
			info[i].isUsed		= true;
			info[i].name		= name;
			info[i].user_socket = sock;

			//���ͼ���б��Ա
			AddListMem(name,i);
			return true;
		}
	}
	AfxMessageBox("�ͻ��˳�Ա�б�����");
	return false;
}
//ɾ���ͻ��˳�Ա�б��еĳ�Ա
BOOL CQQ_serverDlg::delMember(SOCKET sock)
{
	for(int i=0;i<5;i++)
	{
		if(info[i].isUsed == true && info[i].user_socket == sock)
		{
			//ɾ��ͼ���б��Ա
			LVFINDINFO	findInfo;
			findInfo.flags = LVFI_PARTIAL | LVFI_STRING;
			findInfo.psz   = info[i].name.GetBuffer(0);
			int index = m_memlist.FindItem(&findInfo);
			m_memlist.DeleteItem(index);

			info[i].isUsed		= false;
			info[i].name		= "";

			return true;
		}
	}
	AfxMessageBox("û���ҵ��ó�Ա");
	return false;
}
//�Խ��յ����������ݱ�ʶ�ֶν���ɸѡ
CString CQQ_serverDlg::getKeyMsg(CString recv_msg,CString keyword)
{
	int index_start = 0,index_end = 0;
	int index = 0;
	CString str_temp = "";

	if("To" == keyword)
	{
		index_start = recv_msg.Find("To:");
		index_end	= recv_msg.Find("\r\n",index_start);
		for(index = index_start+3;index < index_end;index++)
		{
			str_temp += recv_msg.GetAt(index);
		}
		return str_temp;
	}

	if("From" == keyword)
	{
		index_start = recv_msg.Find("From:");
		index_end	= recv_msg.Find("\r\n",index_start);
		for(index = index_start+5;index < index_end;index++)
		{
			str_temp += recv_msg.GetAt(index);
		}
		return str_temp;
	}

	return "";
}
//��ʼ��ͼ���б��
void CQQ_serverDlg::InitListView()
{
	//����ͼ���б�
	m_imagelist.Create(32,32,ILC_COLOR32,5,5);
	//���ͼ��
	for(int i = 0;i < 5;i++)
	{
		m_imagelist.Add( LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(129+i)) );
	}
	//�������б�ؼ���
	m_memlist.SetImageList(&m_imagelist,LVSIL_SMALL);
}

//���б��ؼ�����ӳ�Ա
void CQQ_serverDlg::AddListMem(CString name,int index)
{
	LVITEM lvitem;
	memset(&lvitem,0,sizeof(LVITEM));
	lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
	lvitem.iItem = index;
	lvitem.pszText = name.GetBuffer(0);
	lvitem.iImage = index;
	
	m_memlist.InsertItem(&lvitem);
}
//���ͳ�Ա����Ϣ
void CQQ_serverDlg::SendMemName(SOCKET sock,CString name)
{
	//������Ϣ
	CString str_temp = "";
	str_temp  = "List:";
	str_temp += name;
	str_temp += "\r\n";

	if( SOCKET_ERROR == send(sock,str_temp,str_temp.GetLength(),NULL) )
	{
		AfxMessageBox("��Ա����Ϣ���ͳ���");
		return;
	}
}
//�������б��Ա���ͳ�Ա����Ϣ
void CQQ_serverDlg::SendAllMem()
{
	CString name_list = "";
	int count = m_memlist.GetItemCount();
	for(int i=0;i<5;i++)
	{
		if(info[i].isUsed == true)
		{
			//��ʽ�������б�
			for(int j=0;j<count;j++)
			{
				CString name = m_memlist.GetItemText(j,0);
				if(info[i].name != name)
				{
					name_list += name;
					name_list += ",";
				}
			}
			SendMemName(info[i].user_socket,name_list);
			name_list = "";
		}
	}
}

void CQQ_serverDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	closesocket(socket_server);
	WSACleanup();

	CDialog::OnCancel();
}
