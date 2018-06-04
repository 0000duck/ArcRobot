// Simulation.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ArcRobot.h"
#include "Simulation.h"
#include "afxdialogex.h"



// Simulation �Ի���

IMPLEMENT_DYNAMIC(Simulation, CDialogEx)

Simulation::Simulation(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

Simulation::~Simulation()
{
}

void Simulation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_staticpic);
}


BEGIN_MESSAGE_MAP(Simulation, CDialogEx)
//	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
//	ON_WM_MBUTTONDOWN()
//	ON_WM_MBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// Simulation ��Ϣ�������

BOOL Simulation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	///////////////////////OPENGL INIT///////////////////////// 
	InitGL();
	gldisplay.ReadSlpFile();
	SetTimer(1, 1000, 0);

	////////////////////////////////////////////////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

bool Simulation::InitGL()
{
	///////////////////////OPENGL INIT/////////////////////////
	CWnd *wnd = GetDlgItem(IDC_STATIC_PIC);
	hrenderDC = ::GetDC(wnd->m_hWnd);
	if (SetWindowPixelFormat(hrenderDC) == FALSE)
		return 0;

	if (CreateViewGLContext(hrenderDC) == FALSE)
		return 0;
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	///////////////////////////////////////////
	
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 100, 1200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do

	////////////////////////////////////////////////////////////////
	//���ù�Դ
	GLfloat ambientLight[] = { 1.0f,1.0f,1.0f,1.0f };//��ɫ����Դ������
	GLfloat diffuseLight[] = { 1.0f,1.0f,1.0f,1.0f };//��ɫ����Դ������ 
	GLfloat specularLight[] = { 1.0f,1.0f,1.0f,1.0f };//��ɫ����Դ�����  

	GLfloat redAmbiLight[] = { 0.2f,0.0f,0.0f,1.0f };//��ɫ����Դ������  
	GLfloat redDiffLight[] = { 0.8f,0.0f,0.0f,1.0f };//��ɫ����Դ������  
	GLfloat redSpecLight[] = { 1.0f,0.0f,0.0f,1.0f };//��ɫ����Դ�����  

	GLfloat lightPos[] = { 1.0f,0.0f,1.0f,0 };  //��Դλ��  
	GLfloat spotLightPos[] = { 0.0f,0.0f,200.0f,1.0f }; //���λ��  
	GLfloat spotDir[] = { 0.0f,0.0f,-1.0f };            //��Ʒ���  

	GLfloat redLight[] = { 1.0f,0.0f,0.0f,1.0f };       //��ɫ��Դ  
	GLfloat greenLight[] = { 0.0f,1.0f,0.0f,1.0f };     //��ɫ��Դ  
	GLfloat blueLight[] = { 0.0f,0.0f,1.0f,1.0f };      //��ɫ��Դ  


	glEnable(GL_LIGHTING);                          //���ù���  
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //���û�����Դ  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   //�����������Դ  
	glLightfv(GL_LIGHT0, GL_SPECULAR, blueLight); //���þ����Դ 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //���õƹ�λ��  
	glEnable(GL_LIGHT0);                            //�򿪰�ɫ����Դ  
	////////////////////////////////////////////////////////////////////////


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	/////////////////////////////////////////////////////////////// 
	// TODO: Add extra initialization here
	return true;
}


BOOL Simulation::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER |
		PFD_TYPE_RGBA;

	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 0;
	pixelDesc.cRedShift = 0;
	pixelDesc.cGreenBits = 0;
	pixelDesc.cGreenShift = 0;
	pixelDesc.cBlueBits = 0;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 0;
	pixelDesc.cAccumRedBits = 0;
	pixelDesc.cAccumGreenBits = 0;
	pixelDesc.cAccumBlueBits = 0;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 0;
	pixelDesc.cStencilBits = 1;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	PixelFormat = ChoosePixelFormat(hDC, &pixelDesc);
	if (PixelFormat == 0) // Choose default 
	{
		PixelFormat = 1;
		if (DescribePixelFormat(hDC, PixelFormat,
			sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat(hDC, PixelFormat, &pixelDesc) == FALSE)

	{
		return FALSE;
	}

	return TRUE;
}

BOOL Simulation::CreateViewGLContext(HDC hDC)
{
	hrenderRC = wglCreateContext(hDC);

	if (hrenderRC == NULL)
		return FALSE;

	if (wglMakeCurrent(hDC, hrenderRC) == FALSE)
		return FALSE;

	return TRUE;
}

void Simulation::RenderScene()
{

	/*
	///////////////////////////////////////////////// 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);      // Move Left 1.5 Units And Into The Screen 6.0  
	glRotated(m_yRotate, 0.0, 0, 1.0);
	gluLookAt(0.0, 0.0, 1000.0, 0.0, 0.0, 0.0, 0, 1, 0);

	/////////////////////////////////////////////////
	//�������
	GLfloat robot_mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  //������ʵĻ�������ɫ��ƭ��ɫ  
	GLfloat robot_mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  //������ʵ����������ɫ��ƫ��ɫ  
	GLfloat robot_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   //������ʵľ��淴�����ɫ����ɫ  
	GLfloat robot_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //������ʵķ������ɫ��Ϊ0  
	GLfloat robot_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, robot_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robot_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robot_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, robot_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, robot_mat_shininess);
	////////////////////////////////////////////////

	glBegin(GL_TRIANGLES); // Drawing Using Triangles 

	//glVertex3f(0.0f, 1.0f, 0.0f);     // Top 
	//glVertex3f(-1.0f, -1.0f, 0.0f);     // Bottom Left 
	//glVertex3f(1.0f, -1.0f, 0.0f);     // Bottom Right 
	glColor3f(1, 1, 1);
	for (int i = 0; i != gldisplay.count; i++)
	{
		glNormal3f(gldisplay.NorverVec[i].normal1, gldisplay.NorverVec[i].normal2, gldisplay.NorverVec[i].normal3);
		glVertex3f(gldisplay.NorverVec[i].vertex1, gldisplay.NorverVec[i].vertex2, gldisplay.NorverVec[i].vertex3);
	}
	glEnd();           // Finished Drawing The Triangle */

	gldisplay.GLDraw();
	SwapBuffers(hrenderDC);
}

/*
void Simulation::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	RenderScene();
	m_yRotate += 10;
	CDialogEx::OnTimer(nIDEvent);
}
*/

void Simulation::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	RenderScene();
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


BOOL Simulation::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (zDelta >= 0)
	{
		gldisplay.executeScaleOperation(-0.1);
	}
	else
	{
		gldisplay.executeScaleOperation(0.1);
	}
	OnPaint();

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void Simulation::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (midButtonState)
	{
		if (ctrlKeyState)
		{
			gldisplay.executeTranslateOperation(point.x, point.y);
		}
		else
		{
			gldisplay.executeRotateOperation(point.x, point.y);
		}

		OnPaint();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void Simulation::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
}


void Simulation::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL Simulation::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���


	if (pMsg->message == WM_KEYDOWN)
	{

		if (pMsg->wParam == VK_CONTROL)//ֱ�����������Ϳ�����Ӧ��ָ��  
		{
			ctrlKeyState = true;
		}

	}

	if (pMsg->message == WM_KEYUP)
	{

		if (pMsg->wParam == VK_CONTROL)//ֱ�����������Ϳ�����Ӧ��ָ��  
		{
			ctrlKeyState = false;
		}

	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
