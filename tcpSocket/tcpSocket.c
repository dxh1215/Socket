#include"tcpSocket.h"
bool init_Socket()
{
	//windows�첽�׽���
	//param1����汾 parameter2��������
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		printf("WSAStartup failed code %d", WSAGetLastError());//��ȡ�������
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
	//1.�����յ�socket 
	//param1:��ַЭ���� param2��Э�鴫������ ��ʽ ���ݱ� param3:ʹ�þ��屨�ĵĴ���Э��
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET) {
		err("socket");
		return INVALID_SOCKET;
	}

	//2,��socket��ip��ַ�Ͷ˿ں�
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;//����socketʱ����Ҫһ��
	addr.sin_port = htons(PORT);	//
	addr.sin_addr.S_un.S_addr = ADDR_ANY;//inet_addr("127.0.0.1");

	if (SOCKET_ERROR == bind(fd, &addr, sizeof(addr))) {
		err("bind");
		return false;
	}

	//�����绰
	listen(fd, 10);

	return fd;
}

SOCKET createClientSocket(const char* ip)
{
	//1.�����յ�socket 
	//param1:��ַЭ���� param2��Э�鴫������ ��ʽ ���ݱ� param3:ʹ�þ��屨�ĵĴ���Э��
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET) {
		err("socket");
		return INVALID_SOCKET;
	}

	//2,���������������
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;//����socketʱ����Ҫһ��
	addr.sin_port = htons(PORT);	//
	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr))) {
		err("connect");
		return false;
	}

	return fd;
}


