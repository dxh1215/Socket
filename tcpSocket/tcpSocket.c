#include"tcpSocket.h"
bool init_Socket()
{
	//windows异步套接字
	//param1请求版本 parameter2传出参数
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		printf("WSAStartup failed code %d", WSAGetLastError());//获取错误代码
		return false;
	}
	return true;
}

bool close_Socket()
{
	if (0 != WSACleanup())
	{
		printf("WSACleanup failed code %d", WSAGetLastError());
		return false;
	}
	return true;
}

SOCKET creatServerSocket()
{
	//1.创建空的socket 
	//param1:地址协议族 param2：协议传输类型 流式 数据报 param3:使用具体报文的传输协议
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET) {
		err("socket");
		return INVALID_SOCKET;
	}

	//2,给socket绑定ip地址和端口号
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;//创建socket时必须要一样
	addr.sin_port = htons(PORT);	//
	addr.sin_addr.S_un.S_addr = ADDR_ANY;//inet_addr("127.0.0.1");

	if (SOCKET_ERROR == bind(fd, &addr, sizeof(addr))) {
		err("bind");
		return false;
	}

	//监听电话
	listen(fd, 10);

	return fd;
}

SOCKET createClientSocket(const char* ip)
{
	//1.创建空的socket 
	//param1:地址协议族 param2：协议传输类型 流式 数据报 param3:使用具体报文的传输协议
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET) {
		err("socket");
		return INVALID_SOCKET;
	}

	//2,与服务器建立连接
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;//创建socket时必须要一样
	addr.sin_port = htons(PORT);	//
	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr))) {
		err("connect");
		return false;
	}

	return fd;
}


