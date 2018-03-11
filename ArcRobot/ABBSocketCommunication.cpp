#include "stdafx.h"
#include "ABBSocketCommunication.h"
#include "Resource.h"
using namespace std;

int ABBSocket::SocketListen()
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
	addrServ.sin_port = htons(4999);//host to short �˿ں�
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


int ABBSocket::SocketAccept()
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
	ZeroMemory(buf, BUF_SIZE);//����ڴ�
	return 0;
}


int ABBSocket::SocketSend(char* Data)
{
	sprintf_s(sendBuf, Data);
	send(sClient, sendBuf, strlen(sendBuf), 0);
	return 1;
}

char* ABBSocket::GetCurPos()
{
	ZeroMemory(buf, BUF_SIZE);//����ڴ�
	SocketSend("CurPos");
	recv(sClient, buf, BUF_SIZE, 0);
	//cout << buf << endl;
	return buf;
	

}

char* ABBSocket::GetPointPos()
{
	ZeroMemory(buf, BUF_SIZE);//����ڴ�
	SocketSend("PointPos");
	recv(sClient, buf, BUF_SIZE, 0);
	//cout << buf << endl;
	return buf;
}

char* ABBSocket::GetEndPos()
{
	ZeroMemory(buf, BUF_SIZE);//����ڴ�
	SocketSend("EndPos");
	recv(sClient, buf, BUF_SIZE, 0);
	//cout << buf << endl;
	return buf;
}


//
int ABBSocket::SocketSendPos(vector<vector<char *>> targetPos,int num) 
{
	ZeroMemory(buf, BUF_SIZE);//����ڴ�
	SocketSend("RecPos");
	for (int i = 0; i != num; i++)
	{
		//���տͻ�������  
	    //ԭ�ͣ�int recv(int sockfd,void *buf,int len,unsigned int flags); 
		//recive from :sockfd�ǽ������ݵ�socket��������
		//buf �Ǵ�Ž������ݵĻ�������len�ǻ���ĳ��ȡ�
		//flagsҲ����Ϊ0��
		//recv()����ʵ���Ͻ��յ��ֽ������򵱳��ִ���ʱ������ - 1������Ӧ��errnoֵ��
		retVal = recv(sClient, buf, BUF_SIZE, 0);//���պ���
												 // int recv(int sockfd,void *buf,int len,unsigned int flags); 

		if (SOCKET_ERROR == retVal)
		{
			cout << "recv failed!" << endl;
			closesocket(sServer);   //�ر��׽���  
			closesocket(sClient);   //�ر��׽���       
			WSACleanup();           //�ͷ��׽�����Դ;  
			return -1;
		}
		if (buf[0] == '\0')
			break;
		cout << "dierci:" << buf <<  endl;
		//tans data

		sprintf_s(sendBuf, "Start");
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);

		sprintf_s(sendBuf, "%s", targetPos[i][0]);
		printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		cout << buf << endl;
		//rot data
		sprintf_s(sendBuf, "%s", targetPos[i][1]);
		printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		cout << buf << endl;
		//robconf data
		sprintf_s(sendBuf, "%s", targetPos[i][2]);
		printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		cout << buf << endl;
		//extax data
		sprintf_s(sendBuf, "%s", targetPos[i][3]);
		printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		cout << buf << endl;
		//sprintf_s(sendBuf,"[%.5f, %.5f, %.5f]", posx, posy, posz);


		//int send(int sockfd, const void *msg, int len, int flags);
		//send to:sockfd�����������������ݵ�socket��������msg��һ��ָ��Ҫ�������ݵ�ָ�롣
		//len�����ֽ�Ϊ��λ�����ݵĳ��ȡ�flagsһ���������Ϊ0�����ڸò������÷��ɲ���man�ֲᣩ��
		//send()��������ʵ���Ϸ��ͳ����ֽ��������ܻ�������ϣ�����͵����ݡ�������Ҫ��send()�ķ���ֵ���в�����
		//��send()����ֵ��len��ƥ��ʱ��Ӧ�ö�����������д���


	}
	recv(sClient, buf, BUF_SIZE, 0);
	cout << "ready?       " << buf << endl;
	sprintf_s(sendBuf, "End");
	send(sClient, sendBuf, strlen(sendBuf), 0);
	retVal = recv(sClient, buf, BUF_SIZE, 0);
	cout << "Last: " << buf << endl;
	return 0;
}

int ABBSocket::SocketScan(vector<vector<char *>> targetPos, DWORD* ScanStartTime, int num)
{
	ZeroMemory(buf, BUF_SIZE);//����ڴ�
	SocketSend("Scan");
	*ScanStartTime = timeGetTime();
	for (int i = 0; i != num; i++)
	{
		//���տͻ�������  
		//ԭ�ͣ�int recv(int sockfd,void *buf,int len,unsigned int flags); 
		//recive from :sockfd�ǽ������ݵ�socket��������
		//buf �Ǵ�Ž������ݵĻ�������len�ǻ���ĳ��ȡ�
		//flagsҲ����Ϊ0��
		//recv()����ʵ���Ͻ��յ��ֽ������򵱳��ִ���ʱ������ - 1������Ӧ��errnoֵ��
		retVal = recv(sClient, buf, BUF_SIZE, 0);//���պ���
												 // int recv(int sockfd,void *buf,int len,unsigned int flags); 

		if (SOCKET_ERROR == retVal)
		{
			cout << "recv failed!" << endl;
			closesocket(sServer);   //�ر��׽���  
			closesocket(sClient);   //�ر��׽���       
			WSACleanup();           //�ͷ��׽�����Դ;  
			return -1;
		}
		if (buf[0] == '\0')
			break;
		//cout << "dierci:" << buf << endl;
		//tans data

		sprintf_s(sendBuf, "Start");
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);

		sprintf_s(sendBuf, "%s", targetPos[i][0]);
		//printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		//cout << buf << endl;
		//rot data
		sprintf_s(sendBuf, "%s", targetPos[i][1]);
		//printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		//cout << buf << endl;
		//robconf data
		sprintf_s(sendBuf, "%s", targetPos[i][2]);
		//printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		//cout << buf << endl;
		//extax data
		sprintf_s(sendBuf, "%s", targetPos[i][3]);
		//printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		//cout << buf << endl;
		//sprintf_s(sendBuf,"[%.5f, %.5f, %.5f]", posx, posy, posz);


		//int send(int sockfd, const void *msg, int len, int flags);
		//send to:sockfd�����������������ݵ�socket��������msg��һ��ָ��Ҫ�������ݵ�ָ�롣
		//len�����ֽ�Ϊ��λ�����ݵĳ��ȡ�flagsһ���������Ϊ0�����ڸò������÷��ɲ���man�ֲᣩ��
		//send()��������ʵ���Ϸ��ͳ����ֽ��������ܻ�������ϣ�����͵����ݡ�������Ҫ��send()�ķ���ֵ���в�����
		//��send()����ֵ��len��ƥ��ʱ��Ӧ�ö�����������д���


	}
	recv(sClient, buf, BUF_SIZE, 0);
	//cout << "ready?       " << buf << endl;
	sprintf_s(sendBuf, "End");
	send(sClient, sendBuf, strlen(sendBuf), 0);
	retVal = recv(sClient, buf, BUF_SIZE, 0);
	//cout << "Last: " << buf << endl;


	//����λ����Ϣ
	/*
	int recvTimeout = 2 * 1000;   //2s
	setsockopt(sClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&recvTimeout, sizeof(int));
	while (-1 != recv(sClient, buf, BUF_SIZE, 0))
	{
		cout << buf << endl;
		ZeroMemory(buf, BUF_SIZE);//����ڴ�
	}
	*/
	return 0;
}

 char* ABBSocket::SocketPosRecv(int* rval)
{	
	int recvTimeout = 2 * 1000;   //2s
	setsockopt(sClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&recvTimeout, sizeof(int));
	ZeroMemory(buf, BUF_SIZE);//����ڴ�
	int rVal=recv(sClient, buf, BUF_SIZE, 0);
	*rval = rVal;
	return buf;
}


 int ABBSocket::SetToZero()
 {
	 SocketSend("ToZero");
	 return 0;
 }

int ABBSocket::SocketStop()
{
	ZeroMemory(buf, BUF_SIZE);//����ڴ�
	retVal = recv(sClient, buf, BUF_SIZE, 0);//���պ���
	sprintf_s(sendBuf, "Stop");
	send(sClient, sendBuf, strlen(sendBuf), 0);
	recv(sClient, buf, BUF_SIZE, 0);
	//�˳�  
	closesocket(sServer);   //�ر��׽���  
	closesocket(sClient);   //�ر��׽���  
	WSACleanup();           //�ͷ��׽�����Դ;  
	return 0;
} 

WSADATA ABBSocket::wsd;            //WSADATA����  
SOCKET ABBSocket::sServer;        //�������׽���  
SOCKET ABBSocket::sClient;        //�ͻ����׽���  
SOCKADDR_IN  ABBSocket::addrServ;      //��������ַ