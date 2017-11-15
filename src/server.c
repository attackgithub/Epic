#include <Winsock2.h>
#include <stdio.h>
#include <string.h>
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
	unsigned int Port;
	if (argc != 2)
	{
		printf("%s\n", "请设定端口！");
		printf("%s\n", "command : server [port]");
		printf("%s\n", "forexample : server 8888");
		return 1;
	}
	else
	{
		Port = ConvertToPort(argv[1]);
	}
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);//该函数的功能是加载一个Winsocket库版本
	if (err != 0) {
		return 1;
	}
	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return 1;
	}
	//真正socket编程部分
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//面向连接的可靠性服务SOCK_STRAM

	SOCKADDR_IN addrSrv;//存放本地地址信息的
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htol将主机字节序long型转换为网络字节序
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(Port);//htos用来将端口转换成字符，1024以上的数字即可

	int e = bind(sockSrv, 
		(SOCKADDR*)&addrSrv, 
		sizeof(SOCKADDR)
		);//将socket绑定到相应地址和端口上

	if (e == -1)
	{
		exit(1);
	}
	listen(sockSrv, 100);//等待队列中的最大长度为100

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char sendBuf[100];
	char recvBuf[100];
	SOCKET sockConn;
	printf("%s%d......\n", "listening at port ", Port);
	while (1)
	{
		sockConn = accept(sockSrv, 
						 (SOCKADDR*)&addrClient, 
						 &len);//建立一个新的套接字用于通信，不是前面的监听套接字
		recv(sockConn, recvBuf, 100, 0);
		sprintf(sendBuf, 
			    "Server receive infomation is : %s",
				recvBuf
				);//inet_nota函数是将字符转换成ip地址
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);//服务器向客户端发送数据
		//recv(sockConn, recvBuf, 100, 0);//服务器从客户端接受数据
		printf("%s\n", recvBuf);
		closesocket(sockConn);//关闭socket
	}
	return 0;
}