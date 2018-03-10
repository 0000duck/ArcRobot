#pragma once
#include "stdafx.h"
#include "SensorCommunicate.h"
int SensorSocket::SocketListen()
{
	//��ʼ���׽��ֶ�̬��  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed!" << endl;
		return 1;
	}

	//�����׽���  
	//int socket(int family, int type, int protocol);
	//familyָ��Э���壻
	//type����ָ��socket�����ͣ�SOCK_STREAM����ʽsocketʹ��TCPЭ��ɿ��������ӡ�
	//SOCK_DGRAM:�����ӵ�UDP��SOCK_RAW:ԭʼ�׽��֣�
	//protocol��Э�飬ͨ����ֵ"0"��
	//sServer:socket������
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{

		cout << "socket failed!" << endl;
		WSACleanup();//�ͷ��׽�����Դ;  
		return  -1;
	}

	//�������׽��ֵ�ַ
	//addrServ����������ַ�ṹ��:socketaddr_in
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(60000);//host to short �˿ں�
	addrServ.sin_addr.s_addr = 0;//��ñ���ip��ַ
								 //���׽��� 
								 //typedef socketaddr* LPSOCKADDR:ָ�򱾵ص�ַ��ָ��

	retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{
		cout << "bind failed!" << endl;
		closesocket(sServer);   //�ر��׽���  
		WSACleanup();           //�ͷ��׽�����Դ;  
		return -1;
	}

	cout << "start listen" << endl;
	//��ʼ����
	//socketϵͳ���÷��صķ�������socket��������
	//backlogָ�������������������������������������������ڶ����еȴ�accept()���ǡ�
	//backlog�Զ����еȴ�������������Ŀ���������ƣ������ϵͳȱʡֵΪ20��
	//��listen��������ʱ����-1,SOCKET_ERROR.
	retVal = listen(sServer, 1);
	if (SOCKET_ERROR == retVal)
	{
		cout << "listen failed!" << endl;
		closesocket(sServer);   //�ر��׽���  
		WSACleanup();           //�ͷ��׽�����Դ;
		return -1;
	}
	return 0;
}


int SensorSocket::SocketAccept()
{
	//���ܿͻ������� 
	//int accept(int sockfd, struct sockaddr *addr, int *addrlen);
	// sockfd�Ǳ������ķ�����socket��������addrͨ����һ��ָ��sockaddr_in������ָ�룬�ñ���������������������Ŀͻ��˵�ַ��
	//addrtenͨ��Ϊһ��ָ��ֵΪsizeof(struct sockaddr_in)������ָ�������
	//������ʱ����һ��-1����������Ӧ��errnoֵ��
	//accept()����������һ���µ�socket�����������������������ʹ�ã����µ�socket�������Ͻ�������send()��recv()������
	sockaddr_in addrClient;
	int addrClientlen = sizeof(addrClient);
	sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientlen);
	if (INVALID_SOCKET == sClient)
	{
		cout << "accept failed!" << endl;
		closesocket(sServer);   //�ر��׽���  
		WSACleanup();           //�ͷ��׽�����Դ;  
		return -1;
	}
	ZeroMemory(buf, BUF_SIZE2);//����ڴ�
	return 0;
}

int SensorSocket::SocketStart(char* Data)
{
	sprintf_s(sendBuf, Data);
	send(sClient, sendBuf, strlen(sendBuf), 0);
	return 1;
}

int SensorSocket::RecvLine(char *vptr, int maxlen, char partChar)
{
	int n, rc;
	char c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++)
	{
		if ((rc = my_read(&c)) == 1)
		{
			*ptr++ = c;
			if (c == partChar)
			{
				break;
			}	
		}	
		else if (rc == 0)
			{
				*ptr = 0;
				return(n - 1);
			}	
		else
				return(-1);
	}
	*ptr = 0;
	return(n);
}

int SensorSocket::my_read(char *ptr)
{
	if(read_cnt<=0)
	{	
	again:
		if ((read_cnt = recv(sClient, read_buf, sizeof(read_buf), 0)) < 0)
		//ע����������ȼ����Ƚ�������ڸ�ֵ
		{
			if (errno == EINTR)
				goto again;
			return (-1);
		}
		else if (read_cnt == 0)
			return (0);
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return (1);

}

int SensorSocket::read_cnt;
char *SensorSocket::read_ptr;
char SensorSocket::read_buf[BUF_SIZE2];
