#pragma once
#include "afxcmn.h"


// PosSeqDialog �Ի���

class PosSeqDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PosSeqDialog)

public:
	PosSeqDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PosSeqDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl PosList;
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton10();
};
