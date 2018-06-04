
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
const int BUF_SIZE2 = 600;

class SensorSocket
{
public:
	int SocketListen();
	int SocketAccept();
	int SocketStart(char* Data);
	int RecvLine(char *vptr, int maxlen = 150, char partChar = 0);
	int my_read(char *ptr);
	int closeSocket(){ return closesocket(sClient);  };


public:

	WSADATA         wsd;            //WSADATA����  
	SOCKET          sServer;        //�������׽���  
	SOCKET          sClient;        //�ͻ����׽���  
	SOCKADDR_IN     addrServ;;      //��������ַ  
	char            buf[BUF_SIZE2];  //�������ݻ�����  
	char            sendBuf[BUF_SIZE2];//���ظ��ͻ��˵�����  
	int             retVal;         //����ֵ  

	static int read_cnt;
	static char *read_ptr;
	static char read_buf[BUF_SIZE2];
};
