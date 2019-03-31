// QQ_clientDlg.h : header file
//

#if !defined(AFX_QQ_CLIENTDLG_H__A2C45C50_250A_4C16_833C_B3F2DBF95D75__INCLUDED_)
#define AFX_QQ_CLIENTDLG_H__A2C45C50_250A_4C16_833C_B3F2DBF95D75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TalkDlg.h"

//�Զ�����Ϣ
#define WM_SOCKET WM_USER+100

/////////////////////////////////////////////////////////////////////////////
// CQQ_clientDlg dialog

class CQQ_clientDlg : public CDialog
{
// Construction
public:
	CQQ_clientDlg(CWnd* pParent = NULL);	// standard constructor

	//������Ϣ
	CString getKeyMsg(CString recv_msg,CString keyword);

	//���б�ؼ��Ĳ���
	void AddMem(CString name);
	void UpdateList(CString MemList);

public:
	SOCKET		socket_client;
	CString 	from_name;			//�����û�����Ϣ
	CString		to_name;			//�����������Ϣ

// Dialog Data
	//{{AFX_DATA(CQQ_clientDlg)
	enum { IDD = IDD_QQ_CLIENT_DIALOG };
	CListCtrl	m_listmem;
	CString	m_username;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQQ_clientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON		m_hIcon;
	CImageList	m_imagelist;
	int			index_image;
	CTalkDlg	m_dlg;

	// Generated message map functions
	//{{AFX_MSG(CQQ_clientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	virtual void OnCancel();
	afx_msg void OnDblclkListmem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnSocket(WPARAM wParam,LPARAM lParam);		//�Զ�����Ϣ����Ӧ����
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QQ_CLIENTDLG_H__A2C45C50_250A_4C16_833C_B3F2DBF95D75__INCLUDED_)
