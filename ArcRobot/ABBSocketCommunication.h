#pragma once

#include "winsock2.h"  
#pragma comment(lib, "ws2_32.lib")  
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
	int SocketSendPos(vector<vector<char *>>);
	int SocketStop();
	int SocketSend(char* Data);
	char* GetCurPos();
private:

	WSADATA         wsd;            //WSADATA����  
	SOCKET          sServer;        //�������׽���  
	SOCKET          sClient;        //�ͻ����׽���  
	SOCKADDR_IN     addrServ;;      //��������ַ  
	char            buf[BUF_SIZE];  //�������ݻ�����  
	char            sendBuf[BUF_SIZE];//���ظ��ͻ��˵�����  
	int             retVal;         //����ֵ  
};