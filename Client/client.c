#include "../tcpSocket/tcpSocket.h"

int main() {
	init_Socket();

	SOCKET fd = createClientSocket("127.0.0.1");
	//��˵һ�仰
	char recvbuf[BUFSIZ] = { 0 };
	char sendbuf[BUFSIZ] = { 0 };
	while (true) {
		//������Ϣ
		printf("send>");
		memset(sendbuf, 0, sizeof(sendbuf));
		gets_s(sendbuf, BUFSIZ);
		if (SOCKET_ERROR == send(fd, sendbuf, strlen(sendbuf), 0)) {
			err("send");
		}
		
		//recv��ָ����socket������Ϣ
		if (0 < recv(fd, recvbuf, BUFSIZ, 0)) {
			printf("recv:%s\n", recvbuf);
			
			memset(recvbuf, 0, sizeof(recvbuf));
		}
	}
	closesocket(fd);
	close_Socket();
	printf("client----end----\n");
	getchar();
	return 0;
}