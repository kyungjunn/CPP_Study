#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <WinSock2.h>
#include <iostream>
#include <process.h>

#pragma comment(lib, "ws2_32")

DWORD ThreadFunction(void* Argument)
{
	for (int i = 0; i < 10000; ++i)
	{
		printf("%d\n", i);
	}
	return 0;
}

int main()
{
	LPDWORD lpThreadId = 0;

	// OS님께 부탁하는거임. Thread 함수 알아서 실행 시켜주세요. OS한테 스레드 함수 등록.
	HANDLE ThreadHandle = CreateThread(0, 0, ThreadFunction, 0, 0, lpThreadId); // lpThreadId -> 0 해도 됨.

	while (true);
	return 0;
}
int main2()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerSocketAddr;
	memset(&ServerSocketAddr, 0, sizeof(ServerSocketAddr));
	ServerSocketAddr.sin_family = AF_INET;
	ServerSocketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSocketAddr.sin_port = htons(43000);

	connect(ServerSocket, (SOCKADDR*)&ServerSocketAddr, sizeof(ServerSocketAddr));

	while (true)
	{
		char Message[1024] = { 0, };
		std::cin.getline(Message, 1024);

		int SentBytes = send(ServerSocket, Message, (int)strlen(Message), 0);
		if (SentBytes <= 0)
		{
			printf("client send error");
			break;
		}

		int RecvBytes = recv(ServerSocket, Message, (int)sizeof(Message), 0);
		if (RecvBytes <= 0)
		{
			break;
		}

		printf("서버로부터 받은 메시지: %s\n", Message);
	}

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}
