// PosSeqDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include "stdlib.h"
#include "ArcRobot.h"
#include "PosSeqDialog.h"
#include "afxdialogex.h"
#include <vector>
using namespace std;


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
ON_BN_CLICKED(IDC_BUTTON1, &PosSeqDialog::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &PosSeqDialog::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON12, &PosSeqDialog::OnBnClickedButton12)
ON_BN_CLICKED(IDC_BUTTON10, &PosSeqDialog::OnBnClickedButton10)
ON_BN_CLICKED(IDC_BUTTON3, &PosSeqDialog::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON11, &PosSeqDialog::OnBnClickedButton11)
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
	PosList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width() / 10, 0);
	PosList.InsertColumn(1, _T("�ռ�����"), LVCFMT_CENTER, rect.Width() / 5, 1);
	PosList.InsertColumn(2, _T("��Ԫ��"), LVCFMT_CENTER, rect.Width() / 5+rect.Width() / 10, 2);
	PosList.InsertColumn(3, _T("�ؽ�״̬"), LVCFMT_CENTER, rect.Width() / 5, 3);
	PosList.InsertColumn(4, _T("������"), LVCFMT_CENTER, rect.Width() / 5, 4);

	// ���б���ͼ�ؼ��в����б���������б������ı�   
	//PosList.InsertItem(0, _T("Java"));
	//PosList.SetItemText(0, 1, _T("1"));
	//PosList.SetItemText(0, 2, _T("1"));
	//PosList.SetItemText(0, 3, _T("1"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void PosSeqDialog::OnBnClickedButton1()
{
	CString LineNumStr,posStr,qStr,StateStr,extra;
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�ж������Ƿ���Ч


	GetDlgItem(IDC_EDIT1)->GetWindowText(posStr);
	GetDlgItem(IDC_EDIT11)->GetWindowText(qStr);
	GetDlgItem(IDC_EDIT12)->GetWindowText(StateStr);
	GetDlgItem(IDC_EDIT28)->GetWindowText(extra);

	int nHeadNum =PosList.GetItemCount();

	LineNumStr.Format(_T("%d"),nHeadNum+1 );
	PosList.InsertItem(nHeadNum, LineNumStr);
	PosList.SetItemText(nHeadNum, 1, posStr);
	PosList.SetItemText(nHeadNum, 2, qStr);
	PosList.SetItemText(nHeadNum, 3, StateStr);
	PosList.SetItemText(nHeadNum, 4, extra);
}


void PosSeqDialog::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int column=PosList.GetSelectionMark();        //ѡ��һ��
	if (column == -1 || PosList.GetItemState(column, LVIS_SELECTED) != LVIS_SELECTED)
	{
		MessageBox(L"��ѡ��һ�У��ٽ���ɾ��", L"��δѡ��Ҫɾ������");
		column = -1;
	}
	//bool selected = PosList.GetItemState(column, LVIS_SELECTED) != LVIS_SELECTED;
	PosList.DeleteItem(column);
	CString LineNumStr;
	int nHeadNum = PosList.GetItemCount();
	for (int i = column; i != nHeadNum; i++)
	{
		LineNumStr.Format(_T("%d"), i+1);
		PosList.SetItemText(i, 0, LineNumStr);
	}
}


void PosSeqDialog::OnBnClickedButton12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT11)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT12)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT28)->SetWindowText(_T(""));
}


void PosSeqDialog::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT13, strFilePath);
	}

	//���ú�����T2A��W2A��֧��ATL��MFC�е��ַ�ת��
	//char * pFileName = W2A(str); //Ҳ��ʵ��ת��
	USES_CONVERSION;
	char* filePath= T2A(strFilePath);;

	FILE* FileOut;
	if(fopen_s(&FileOut, filePath, "r")!=0)
		MessageBox(L"û�д��ļ�", L"��ʾ");
	char content[500];
	while (!feof(FileOut))                                   //ѭ����ȡÿһ�У�ֱ���ļ�β  
	{
		fgets(content, 1024, FileOut);                     //��fp��ָ����ļ�һ�����ݶ���strLine������ 
		//std::cout << content << std::endl;


		//char* data1,data2,data3;
		char data1[100] = {0}, data2[100]= {0}, data3[100]= {0}, data4[100]= {0};
		char* dataChar=content;
		int i = 0;
		for (i = 0; *dataChar != ']'; i++, dataChar++)
				data1[i] = *dataChar;
		data1[i] = *dataChar;
		dataChar+=2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
				data2[i] = *dataChar;
		data2[i] = *dataChar;
		dataChar+=2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
				data3[i] = *dataChar;
		data3[i] = *dataChar;
		dataChar+=2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
				data4[i] = *dataChar;
		data4[i] = *dataChar;

		//std::cout << "data1:" << data1 << std::endl;
		//std::cout << "data2:" << data2 << std::endl;
		//std::cout << "data3:" << data3 << std::endl;
		//std::cout << std::endl;


		CString LineNumStr, posStr, qStr, StateStr,ExtraStr;
		int nHeadNum = PosList.GetItemCount();

		LineNumStr.Format(_T("%d"), nHeadNum + 1);
		posStr.Format(_T("%s"), CStringW(data1));
		qStr.Format(_T("%s"), CStringW(data2));
		StateStr.Format(_T("%s"), CStringW(data3));
		ExtraStr.Format(_T("%s"), CStringW(data4));

		PosList.InsertItem(nHeadNum, LineNumStr);
		PosList.SetItemText(nHeadNum, 1, posStr);
		PosList.SetItemText(nHeadNum, 2, qStr);
		PosList.SetItemText(nHeadNum, 3, StateStr);
		PosList.SetItemText(nHeadNum, 4, ExtraStr);

	}
}


void PosSeqDialog::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nHeadNum = PosList.GetItemCount();
	CString data1, data2, data3, data4;
	//��Ӻ��ӣ�ֱ��Բ�����ٶȵ�ѡ�target��
	vector<vector<char *>> targetPos(nHeadNum, vector<char *>(6, nullptr));
	for (int i = 0; i != nHeadNum; i++)
	{
		data1 = PosList.GetItemText(i, 1);
		data2 = PosList.GetItemText(i, 2);
		data3 = PosList.GetItemText(i, 3);
		data4 = PosList.GetItemText(i, 4);
		USES_CONVERSION;
		targetPos[i][0] = T2A(data1);
		targetPos[i][1] = T2A(data2);
		targetPos[i][2] = T2A(data3);
		targetPos[i][3] = T2A(data4);
		targetPos[i][4] = "ArcL";
		targetPos[i][5] = "v10";
	}

	abbsoc.SocketSendPos(targetPos,targetPos.size());
}


void PosSeqDialog::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
