#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h> // 얘가 나중에 나온거라 include 가 중첩됨. 그래서 먼저 해야됨.
#include <Windows.h>

#include <iostream>
#include <process.h>

#include <atomic> // OS고 뭐고 다 사용 가능

#pragma comment(lib, "ws2_32")

std::atomic<unsigned> 내돈 = 10000;

unsigned Increasement(void* Argument)
{
	for (int i = 0; i < 10000; ++i)
	{
		// 문이 열려있으면 문닫고
		// 원자적으로 작업(원자적으로 더하기)
		// 같은 세줄이지만 이 세줄을 묶어서 뺏기지 않도록
		//InterlockedIncrement(&내돈); // Windows 전용
		내돈.fetch_add(1); // atomic
		//내돈++;
		// 1. 글로벌 변수 접근(숫자 가져오기) << 여기에서 끊김
		// 2. 가져온 숫자에 +1
		// 3. 다시 글로벌 변수에 저장
		// 문열고
	}
	return 0;
}

unsigned Decreasement(void* Argument)
{
	for (int i = 0; i < 10000; ++i)
	{
		//InterlockedDecrement(&내돈);
		//내돈--;
		내돈.fetch_sub(1);
	}
	return 0;
}

// race condition

int main()
{
	//LPDWORD lpThreadId = 0;
	//HANDLE ThreadHandle2 = CreateThread(0, 0, ThreadFunction, 0, 0, lpThreadId);
	HANDLE ThreadHandle1 = (HANDLE)_beginthreadex(0, 0, &Increasement, 0, 0, 0);
	HANDLE ThreadHandle2 = (HANDLE)_beginthreadex(0, 0, &Decreasement, 0, 0, 0);
	HANDLE ThreadHandle3 = (HANDLE)_beginthreadex(0, 0, &Increasement, 0, 0, 0);
	HANDLE ThreadHandle4 = (HANDLE)_beginthreadex(0, 0, &Decreasement, 0, 0, 0);



	//printf("내 돈은? %d\n", 내돈);
	std::cout << "내 돈은? " << 내돈 << std::endl;

	return 0;
}

int main3()
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
