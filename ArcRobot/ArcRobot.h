
// ArcRobot.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once



#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <io.h>  
#include <fcntl.h>  

// CArcRobotApp: 
// �йش����ʵ�֣������ ArcRobot.cpp
//

class CArcRobotApp : public CWinApp
{
public:
	CArcRobotApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CArcRobotApp theApp;