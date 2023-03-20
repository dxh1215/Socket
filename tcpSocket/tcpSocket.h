#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")//库文件
#include<stdbool.h>
#include<stdio.h>

#define PORT 8888
#define err(errMsg)	printf("[line:%d]%s failed code %d",__LINE__,errMsg,WSAGetLastError());//获取错误代码
//打开网路库
bool init_Socket();

//关闭网络库
bool close_Socket();

//创建服务器socket
SOCKET creatServerSocket();

//创建客户端socket
SOCKET createClientSocket(const char* ip);


#endif // !_TCPSOCKET_H_