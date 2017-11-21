#pragma once
#include "afxcmn.h"
#include "ABBSocketCommunication.h"


// ScanDialog �Ի���

class ScanDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ScanDialog)

public:
	ScanDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ScanDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl SeqList;
	afx_msg void OnBnClickedButton1();
	CListCtrl PosList2;
private:
	ABBSocket abbsoc;
public:
	afx_msg void OnBnClickedButton2();
};
