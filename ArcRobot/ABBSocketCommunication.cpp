#include "stdafx.h"
#include "ABBSocketCommunication.h"
int ABBSocket::SocketMain()
{
	const int BUF_SIZE = 600;
	WSADATA         wsd;            //WSADATA����  
	SOCKET          sServer;        //�������׽���  
	SOCKET          sClient;        //�ͻ����׽���  
	SOCKADDR_IN     addrServ;;      //��������ַ  
	char            buf[BUF_SIZE];  //�������ݻ�����  
	char            sendBuf[BUF_SIZE];//���ظ��ͻ��˵�����  
	int             retVal;         //����ֵ  
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
	/*vector<vector<double>> targetPosvec = { { 1131.38, 173.02, 90.00 }, { 1138.58, -126.98, 77.49 },
	{740.74, -126.98, 90.00},{726.72, 187.09, 84.18},
	{943.61, 0.00, 1152.50} };*/
	/*vector<vector<char *>> targetPos = {
	{"[1131.38, 173.02, 90.00]", "[0.0918634, -0.942962, -0.296062, -0.12137]",
	"[0, -2, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]"},
	{"[1138.58, -126.98, 77.49]", "[0.0918633, -0.942962, -0.296062, -0.12137]",
	"[-1, -2, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]"},
	{"[740.74, -126.98, 90.00]", "[0.0918632, -0.942962, -0.296063, -0.12137]",
	"[-1, -1, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]"},
	{"[726.72, 187.09, 84.18]", "[0.0918633, -0.942962, -0.296062, -0.12137]",
	"[0, -1, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]"},
	{"[943.61, 0.00, 1152.50]", "[0.5, -1.19121E-08, 0.866025, -6.87746E-09]",
	"[0, 0, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" }
	};*/
	vector<vector<char *>> targetPos = {
		{ "[757.05,-839.97,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[757.05,-1010.73,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[363.58, -1074.88, 945.65]","[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, 0, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[363.58, -704.45, 934.48]", "[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, -1, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[943.61, 0.00, 1152.50]", "[0.5, -1.19121E-08, 0.866025, -6.87746E-09]", "[0, 0, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" }
	};

	/*	vector<vector<char *>> targetPos = {
	{ "[1131.38, 173.02, 90.00]", "[0.0918634, -0.942962, -0.296062, -0.12137]",
	"[0, -2, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
	{ "[1138.58, -126.98, 77.49]", "[0.0918633, -0.942962, -0.296062, -0.12137]",
	"[0, 0, 0, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
	{ "[740.74, -126.98, 90.00]", "[0.0918632, -0.942962, -0.296063, -0.12137]",
	"[0, 0, 0, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
	{ "[726.72, 187.09, 84.18]", "[0.0918633, -0.942962, -0.296062, -0.12137]",
	"[0, 0, 0, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
	{ "[943.61, 0.00, 1152.50]", "[0.5, -1.19121E-08, 0.866025, -6.87746E-09]",
	"[0, 0, 0, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" }
	};
	*/
	for (int i = 0; i != targetPos.size(); i++)
	{
		//���տͻ�������  
		ZeroMemory(buf, BUF_SIZE);//����ڴ�
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
		if (buf[0] == '0')
			break;
		cout << buf << endl;
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