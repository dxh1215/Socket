#include"../tcpSocket/tcpSocket.h"

int main() {
	init_Socket();

	SOCKET serfd = creatServerSocket();
	printf("wait client connect...\n");
	//����пͻ�����������
	SOCKET clifd = accept(serfd, NULL, NULL);
	if (INVALID_SOCKET == clifd) {
		err("accept");
	}

	//���ԺͿͻ���ͨ����
	char recvbuf[BUFSIZ] = { 0 };
	char sendbuf[BUFSIZ] = { 0 };
	while (true) {
		//recv��ָ����socket������Ϣ
		if (0 < recv(clifd, recvbuf, BUFSIZ, 0)) {
			printf("recv:%s\n", recvbuf);
			memset(recvbuf, 0, sizeof(recvbuf));
		}

		//������Ϣ
		printf("send>");
		memset(sendbuf, 0, sizeof(sendbuf));
		gets_s(sendbuf, BUFSIZ);
		if (SOCKET_ERROR == send(clifd, sendbuf, strlen(sendbuf), 0)) {
			err("send");
		}
	}

	closesocket(clifd);
	closesocket(serfd);

	close_Socket();
	printf("server----end----\n");
	getchar();//��ֹ����
	return 0;

}