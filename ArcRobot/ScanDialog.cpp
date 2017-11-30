// ScanDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ArcRobot.h"
#include "ScanDialog.h"
#include "afxdialogex.h"


// ScanDialog �Ի���

IMPLEMENT_DYNAMIC(ScanDialog, CDialogEx)

ScanDialog::ScanDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

ScanDialog::~ScanDialog()
{
}

void ScanDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, SeqList);
	DDX_Control(pDX, IDC_LIST2, PosList2);
}


BEGIN_MESSAGE_MAP(ScanDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ScanDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ScanDialog::OnBnClickedButton2)
END_MESSAGE_MAP()


// ScanDialog ��Ϣ�������


BOOL ScanDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	SeqList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	SeqList.SetExtendedStyle(SeqList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ�������� 
	SeqList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width() / 8, 0);
	SeqList.InsertColumn(1, _T("�ռ�����"), LVCFMT_CENTER, rect.Width() / 4, 1);
	SeqList.InsertColumn(2, _T("��Ԫ��"), LVCFMT_CENTER, rect.Width() / 4 + rect.Width() / 8, 2);
	SeqList.InsertColumn(3, _T("�ؽ�״̬"), LVCFMT_CENTER, rect.Width() / 4, 3);



	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	PosList2.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	PosList2.SetExtendedStyle(PosList2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ�������� 
	PosList2.InsertColumn(0, _T("ʱ���"), LVCFMT_CENTER, rect.Width() / 8, 0);
	PosList2.InsertColumn(1, _T("�ռ�����"), LVCFMT_CENTER, rect.Width() / 4, 1);
	PosList2.InsertColumn(2, _T("��Ԫ��"), LVCFMT_CENTER, rect.Width() / 4 + rect.Width() / 8, 2);
	PosList2.InsertColumn(3, _T("��������"), LVCFMT_CENTER, rect.Width() / 4, 3);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void ScanDialog::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//SetDlgItemText(IDC_EDIT13, strFilePath);
	}

	//���ú�����T2A��W2A��֧��ATL��MFC�е��ַ�ת��
	//char * pFileName = W2A(str); //Ҳ��ʵ��ת��
	USES_CONVERSION;
	char* filePath = T2A(strFilePath);;

	FILE* FileOut;
	if (fopen_s(&FileOut, filePath, "r") != 0)
		MessageBox(L"û�д��ļ�", L"��ʾ");
	char content[500];
	while (!feof(FileOut))                                   //ѭ����ȡÿһ�У�ֱ���ļ�β  
	{
		fgets(content, 1024, FileOut);                     //��fp��ָ����ļ�һ�����ݶ���strLine������ 
														   //std::cout << content << std::endl;


														   //char* data1,data2,data3;
		char data1[100] = { 0 }, data2[100] = { 0 }, data3[100] = { 0 };
		char* dataChar = content;
		int i = 0;
		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data1[i] = *dataChar;
		data1[i] = *dataChar;
		dataChar += 2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data2[i] = *dataChar;
		data2[i] = *dataChar;
		dataChar += 2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data3[i] = *dataChar;
		data3[i] = *dataChar;

		//std::cout << "data1:" << data1 << std::endl;
		//std::cout << "data2:" << data2 << std::endl;
		//std::cout << "data3:" << data3 << std::endl;
		//std::cout << std::endl;


		CString LineNumStr, posStr, qStr, StateStr;
		int nHeadNum = SeqList.GetItemCount();

		LineNumStr.Format(_T("%d"), nHeadNum + 1);
		posStr.Format(_T("%s"), CStringW(data1));
		qStr.Format(_T("%s"), CStringW(data2));
		StateStr.Format(_T("%s"), CStringW(data3));

		SeqList.InsertItem(nHeadNum, LineNumStr);
		SeqList.SetItemText(nHeadNum, 1, posStr);
		SeqList.SetItemText(nHeadNum, 2, qStr);
		SeqList.SetItemText(nHeadNum, 3, StateStr);
	}
}


void ScanDialog::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nHeadNum = SeqList.GetItemCount();
	CString data1, data2, data3;
	char *dataChar1, *dataChar2, *dataChar3;
	char* dataChar4 = "[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]";
	vector<vector<char *>> targetPos(nHeadNum, vector<char *>(4, nullptr));
	for (int i = 0; i != nHeadNum; i++)
	{
		data1 = SeqList.GetItemText(i, 1);
		data2 = SeqList.GetItemText(i, 2);
		data3 = SeqList.GetItemText(i, 3);
		USES_CONVERSION;
		targetPos[i][0] = T2A(data1);
		targetPos[i][1] = T2A(data2);
		targetPos[i][2] = T2A(data3);
		targetPos[i][3] = dataChar4;
	}

	abbsoc.SocketScan(targetPos);
	char* pos;
	int rval;
	int i = 0;
	vector<vector<double>> res(1000,vector<double>(8, 0));
	pos = abbsoc.SocketPosRecv(&rval);
	while (rval != -1)
	{
		//cout << i << ":   " << pos << endl;	
		i++;
		sscanf_s(pos, "%lf[%lf,%lf,%lf][%lf,%lf,%lf,%lf]", &res[i][0], &res[i][1], &res[i][2], &res[i][3], &res[i][4], &res[i][5], &res[i][6],&res[i][7]);	
		//cout << res[i][0] << " " << res[i][1] << " " << res[i][2] << " " << res[i][3] << " " << res[i][4] << " " << res[i][5] << " " << res[i][6] << " " << res[i][7] << endl;
		CString TimeStr, posStr, qStr, SensorStr;
		int nHeadNum = PosList2.GetItemCount();

		TimeStr.Format(_T("%.4lf"), res[i][0]);
		posStr.Format(_T("[%.4lf, %.4lf, %.4lf]"), res[i][1],res[i][2],res[i][3]);
		qStr.Format(_T("[%.6lf, %.6lf, %.6lf, %.6lf]"), res[i][4], res[i][5], res[i][6], res[i][7]);
		SensorStr.Format(_T("[%.4lf, %.4lf]"), 0.5,0.5);

		PosList2.InsertItem(nHeadNum, TimeStr);
		PosList2.SetItemText(nHeadNum, 1, posStr);
		PosList2.SetItemText(nHeadNum, 2, qStr);
		PosList2.SetItemText(nHeadNum, 3, SensorStr);
		UpdateWindow();
		PosList2.EnsureVisible(nHeadNum,false);

		pos = abbsoc.SocketPosRecv(&rval);	
	}
	
}
