#pragma once

#include "winsock2.h"  
#pragma comment(lib, "ws2_32.lib")  
#pragma comment( lib,"winmm.lib" )
#include <Windows.h>
#include <Mmsystem.h>
#include <vector>
#include "ProcessLog.h"
#define _WINSOCK_DEPRECATECD_NO_WARNINGS
using namespace std;
const int BUF_SIZE = 600;

class ABBSocket : public ProcessLog
{
public:
	int SocketListen();
	int SocketAccept();
	int SocketSendPos(vector<vector<char *>>, int num);
	int SocketScan(vector<vector<char *>>, DWORD*, int);
	int SocketStop();
	int SocketSend(char* Data);
	char* GetCurPos();
	char* SocketPosRecv(int* rval);
	int SetToZero();
	char* GetPointPos();
	char* GetEndPos();
private:

	static WSADATA         wsd;            //WSADATA����  
	static SOCKET          sServer;        //�������׽���  
	static SOCKET          sClient;        //�ͻ����׽���  
	static SOCKADDR_IN     addrServ;;      //��������ַ  
	char            buf[BUF_SIZE];  //�������ݻ�����  
	char            sendBuf[BUF_SIZE];//���ظ��ͻ��˵�����  
	int             retVal;         //����ֵ  
};

