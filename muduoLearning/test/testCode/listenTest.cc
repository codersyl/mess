// 本测试程序可独立编译，可以接收 5 个连接发送的信息，然后自动结束进程

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 			// inet_addr()
#define PORT 80                           //端口号
#define BUFFER_SIZE  1024                   //数据缓冲区的大小
#define MAX_QUE_CONN_NM 5                   //请求队列的请求数

int main()
{
	struct sockaddr_in server_sockaddr;
	struct sockaddr_in client_sockaddr;
	int recvbytes;                          //实际接受到的字节数，用于recv（）
	int listenFd;                             //套接字，用于socket（）
	int client_fd;                          //套接字，用于accept（）
	char buf[BUFFER_SIZE];                  //缓冲池

	/*建立socket连接*/
	if ((listenFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("falied to get listen socket\n");
		exit(1);
	}
	printf("listen fd = %d\n", listenFd);

	/*设置sockaddr_in结构体中相关参数*/
	server_sockaddr.sin_family = AF_INET;                  //协议簇IPv4
	server_sockaddr.sin_port = htons(PORT);                //端口号
	server_sockaddr.sin_addr.s_addr = INADDR_ANY; // inet_addr("172.24.20.16")
	//bind()
	if (bind(listenFd, (struct sockaddr *)(&server_sockaddr), sizeof(struct sockaddr)) == -1)
	{
		perror("failed to bind\n");
		exit(1);
	}
	printf("Bind success!\n");

	//listen()
	if (listen(listenFd, MAX_QUE_CONN_NM) == -1)
	{
		perror("falied to listen\n");
		exit(1);
	}
	printf("Listening.....\n");

	while (1)
	{
		/*调用accept()函数，等待客户端的连接*/
		socklen_t clientAddrLen = sizeof(struct sockaddr_in);
		if ((client_fd = accept(listenFd, (struct sockaddr *)&client_sockaddr, &clientAddrLen)) == -1)
		{
			perror("accept");
			exit(1);
		}

		memset(buf, 0, sizeof(buf));
		if ((recvbytes = recv(client_fd, buf, BUFFER_SIZE, 0)) == -1)
		{
			perror("recv");
			exit(1);
		}
		printf("Received a message:%s\n", buf);
	}
	close(listenFd);
	return 0;
}

