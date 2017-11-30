
// ArcRobotDlg.h : ͷ�ļ�
//

#pragma once

#include "ABBSocketCommunication.h"
#include "mathClass.h"

// CArcRobotDlg �Ի���
class CArcRobotDlg : public CDialogEx
{
// ����
public:
	CArcRobotDlg(CWnd* pParent = NULL);	// ��׼���캯��
	

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARCROBOT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	int addtext(int nID, CString str, bool addition=true);
	ABBSocket abbsoc;
	mathfun mathc;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
};


