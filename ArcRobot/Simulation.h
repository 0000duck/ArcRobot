#pragma once
#include "glDisplay.h"
#include "afxwin.h"

// Simulation �Ի���

class Simulation : public CDialogEx
{
	DECLARE_DYNAMIC(Simulation)

public:
	Simulation(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Simulation();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	bool InitGL();
	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
	void RenderScene();
	glDisplay gldisplay;
	HGLRC hrenderRC;
	HDC hrenderDC;
	int PixelFormat;    //���ظ�ʽ
	CStatic m_staticpic;
	float m_yRotate;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
