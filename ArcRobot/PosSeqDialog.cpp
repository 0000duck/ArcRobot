// PosSeqDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ArcRobot.h"
#include "PosSeqDialog.h"
#include "afxdialogex.h"


// PosSeqDialog �Ի���

IMPLEMENT_DYNAMIC(PosSeqDialog, CDialogEx)

PosSeqDialog::PosSeqDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

PosSeqDialog::~PosSeqDialog()
{
}

void PosSeqDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, PosList);
}


BEGIN_MESSAGE_MAP(PosSeqDialog, CDialogEx)
//	ON_WM_ACTIVATE()
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// PosSeqDialog ��Ϣ�������

BOOL PosSeqDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	PosList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	PosList.SetExtendedStyle(PosList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ�������� 
	PosList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width() / 4, 0);
	PosList.InsertColumn(1, _T("�ռ�����"), LVCFMT_CENTER, rect.Width() / 4, 1);
	PosList.InsertColumn(2, _T("��Ԫ��"), LVCFMT_CENTER, rect.Width() / 4, 2);
	PosList.InsertColumn(3, _T("�ؽ�״̬"), LVCFMT_CENTER, rect.Width() / 4, 3);

	// ���б���ͼ�ؼ��в����б���������б������ı�   
	PosList.InsertItem(0, _T("Java"));
	PosList.SetItemText(0, 1, _T("1"));
	PosList.SetItemText(0, 2, _T("1"));
	PosList.SetItemText(0, 3, _T("1"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
