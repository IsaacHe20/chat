// QQ_serverDlg.h : header file
//

#if !defined(AFX_QQ_SERVERDLG_H__5D99A64D_4A30_41C3_B660_4D084A1F78C4__INCLUDED_)
#define AFX_QQ_SERVERDLG_H__5D99A64D_4A30_41C3_B660_4D084A1F78C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//�Զ�����Ϣ
#define WM_SOCKET	WM_USER + 100

//����ṹ
struct client_info
{
	BOOL	isUsed;
	CString name;
	SOCKET	user_socket;
};
/////////////////////////////////////////////////////////////////////////////
// CQQ_serverDlg dialog

class CQQ_serverDlg : public CDialog
{
// Construction
public:
	CQQ_serverDlg(CWnd* pParent = NULL);	// standard constructor

	//ά����Ա�б�ĺ���
	BOOL	addMember(CString name,SOCKET sock);
	BOOL	delMember(SOCKET sock);

	//�������յ�����Ϣ
	CString getKeyMsg(CString recv_msg,CString keyword);

	//��ͻ��˷�����Ϣ�ĺ���
	void	SendMemName(SOCKET sock,CString name);
	void	SendAllMem();
	void	TransMsg(CString recv_msg);
	
	//�б��ؼ��Ĳ���
	void InitListView();
	void AddListMem(CString name,int index);

// Dialog Data
	//{{AFX_DATA(CQQ_serverDlg)

	

	

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQQ_serverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	enum { IDD = IDD_QQ_SERVER_DIALOG };
	CListCtrl	m_memlist;
// Implementation
protected:
	HICON			m_hIcon;
	SOCKET			socket_server;
	client_info		info[5];
	CImageList		m_imagelist;

	// Generated message map functions
	//{{AFX_MSG(CQQ_serverDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartrun();
	virtual void OnCancel();
	//}}AFX_MSG
	afx_msg void OnSocket(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QQ_SERVERDLG_H__5D99A64D_4A30_41C3_B660_4D084A1F78C4__INCLUDED_)
