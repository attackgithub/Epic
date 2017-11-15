#include <stdio.h>
#include <Winsock2.h>
#include <string.h>
char const *l;
char const *p;
char const *n;
char const *a;
void analysic(int argc, char const *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-' && argv[i][1] != '-')
		{
			switch (argv[i][1])
			{
			case 'l':
				l = argv[++i];
				break;
			case 'p':
				p = argv[++i];
				break;
			case 'n':
				n = argv[++i];
				break;
			case 'a':
				a = argv[++i];
				break;
			}
		}
	}
}
unsigned int ConvertToPort(const char *OriginString)
{
	unsigned int Port = 0;
	unsigned int Temp;
	for (int i = 0; OriginString[i]; ++i)
	{
		Temp = OriginString[i] - '0';
		if (Temp < 0 || Temp > 9)
		{
			printf("%s", "端口有误！");
			exit(1);
		}
		Port = Port * 10 + OriginString[i] - '0';
	}
	return Port;
}
int main(int argc, char const *argv[])
{
	if (argc != 9)
	{
		printf("%s\n", "缺少必要参数");
		printf("%s\n%s\n%s\n%s", "使用方法 client [选项] [参数]...",
			"	-l 		学号",
			"	-p 		端口",
			"	-n 		名字\n"
			"	-a 		IP 地址");
		return 1;
	}
	else
	{
		analysic(argc, argv);
	}
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return 0;
	}
	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return 0;
	}
	//建立通讯socket
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(a);//设定需要连接的服务器的ip地址
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(ConvertToPort(p));//设定需要连接的服务器的端口地址
	connect(sockClient, 
			(SOCKADDR*)&addrSrv, 
			sizeof(SOCKADDR));//与服务器进行连接
	char recvBuf[100];
	/*接受来自老师的信息
	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("From server : %s\n", recvBuf);*/

	//发送信息给老师
	char str_send[100];
	str_send[0] = '\0';
	strcat(str_send, n);
	strcat(str_send, " ");
	strcat(str_send, l);
	/*strcat(str_send, " ");
	strcat(str_send, a);*/
	send(sockClient,
		str_send,
		strlen(str_send) + 1,
		0
	);
	recv(sockClient, recvBuf, 100, 0);
	printf("From server : %s\n", recvBuf);
	closesocket(sockClient);
	WSACleanup();
	return 0;
}