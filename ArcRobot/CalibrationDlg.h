#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "calibration.h"

// CalibrationDlg �Ի���

class CalibrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CalibrationDlg)

public:
	CalibrationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CalibrationDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();

	CListCtrl clbrtl;
	Calibration calibration;
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
};