
// ArcRobotDlg.cpp : ʵ���ļ�
//

#include <iostream>
#include "stdafx.h"
#include "ArcRobot.h"
#include "ArcRobotDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CArcRobotDlg �Ի���



CArcRobotDlg::CArcRobotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ARCROBOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArcRobotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CArcRobotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CArcRobotDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CArcRobotDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CArcRobotDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CArcRobotDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CArcRobotDlg ��Ϣ�������

BOOL CArcRobotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_SHOWNORMAL);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CArcRobotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CArcRobotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CArcRobotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CArcRobotDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CArcRobotDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ABBSocket abbsoc;
	abbsoc.SocketListen();
	addtext(IDC_EDIT2, L"start Listen!");
	abbsoc.SocketAccept();
	addtext(IDC_EDIT2, L"aceepted a controller !");

	/*vector<vector<char *>> targetPos = {
		{ "[757.05,-839.97,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[757.05,-1010.73,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[363.58, -1074.88, 945.65]","[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, 0, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[363.58, -704.45, 934.48]", "[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, -1, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[943.61, 0.00, 1152.50]", "[0.5, -1.19121E-08, 0.866025, -6.87746E-09]", "[0, 0, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" }
	};
	abbsoc.SocketSendPos(targetPos);
	addtext(IDC_EDIT2, L"send over !");*/
	
}

int CArcRobotDlg::addtext(int nID, CString str)
{
	CString strOrigin;
	GetDlgItem(nID)->GetWindowText(strOrigin);
	strOrigin += str;
	strOrigin += "\r\n";
	GetDlgItem(nID)->SetWindowText(strOrigin);
	CEdit*p = (CEdit*)GetDlgItem(nID); //����һ��ָ��༭��ľ����ָ��
	p->LineScroll(p->GetLineCount()); //�������õ�
	return 0;
}

void CArcRobotDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	str += "test display";
	str += "\r\n";
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	CEdit*p = (CEdit*)GetDlgItem(IDC_EDIT2); //����һ��ָ��༭��ľ����ָ��
	p->LineScroll(p->GetLineCount()); //�������õ�
}



void CArcRobotDlg::OnBnClickedButton3()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������

	char* pos;
	CString cpos;
	pos = abbsoc.GetCurPos();
	cout << pos << endl;
	cpos.Format(_T("%s"), CStringW(pos));
	cout << cpos << endl;
	addtext(IDC_EDIT1,cpos);

}
