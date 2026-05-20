#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "ChatPacket.h"

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <process.h>

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "NetCommon")

using namespace std;


// recv, send 가 같은 버퍼를 사용하면 버퍼 오염
// 가장 쉬운 방법 -> 버퍼 두 개 만들기
// 버퍼 하나를 사용한다면 Lock -> 근데 스레드 자체가 blocking 이라 우짬
char SendBuffer[1024] = { 0, };
char RecvBuffer[1024] = { 0, };

bool IsRecvThreadRunning = true;
bool IsSendThreadRunning = true;

unsigned WINAPI RecvThread(void* Argument)
{
	SOCKET ServerSocket = *(SOCKET*)Argument;

	while (IsRecvThreadRunning)
	{
		// 1ㄷ1로 주고 받는다.
		int RecvBytes = recv(ServerSocket, RecvBuffer, sizeof(RecvBuffer), 0);
		if (RecvBytes <= 0)
		{
			cout << "recv fail." << endl;
			break;
		}

		ChatPacket Data;
		Data.Parse(RecvBuffer);

		cout << Data.UserID << " : " << Data.Message << " " << Data.Gold << endl;
	}

	return 0;
}

unsigned WINAPI SendThread(void* Argument)
{
	// 책임은 사용하는 놈이 진다.
	SOCKET ServerSocket = *(SOCKET*)Argument;

	char* P = new char[1024];

	while (IsSendThreadRunning)
	{
		cin.getline(SendBuffer, sizeof(SendBuffer));

		ChatPacket Data;
		Data.UserID = "kyungjunn";
		Data.Message = SendBuffer;
		Data.Gold = 1000;
		std::string JSONString = Data.ToString();

		//그냥 1대1로 주고 받는다.
		int SentBytes = send(ServerSocket, JSONString.c_str(), (int)JSONString.length(), 0);
		if (SentBytes <= 0)
		{
			cout << "send fail." << endl;
			break;
		}
	}

	delete[] P;

	return 0;
}

int main()
{
	cout << "Client " << endl;
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("192.168.0.97");
	ServerSockAddr.sin_port = htons(35000);

	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	cout << "client connect" << endl;

	HANDLE ThreadHandles[2] = { 0, };

	// nonblocking, asynchrous
	ThreadHandles[0] = (HANDLE)_beginthreadex(0, 0, RecvThread, &ServerSocket, 0, 0);
	ThreadHandles[1] = (HANDLE)_beginthreadex(0, 0, SendThread, &ServerSocket, 0, 0);
	//ResumeThread(ThreadHandles[0]); // 일시 중단된 스레드 다시 시작
	//ResumeThread(ThreadHandles[1]);
	SuspendThread(ThreadHandles[0]); // 스레드 일시 중단
	//SuspendThread(ThreadHandles[1]);


	// blocking
	WaitForMultipleObjects(2, ThreadHandles, FALSE, INFINITE);


	closesocket(ServerSocket);

	//TerminateThread(ThreadHandles[0], 0);
	//TerminateThread(ThreadHandles[1], 0);
	IsSendThreadRunning = false;
	IsRecvThreadRunning = false;


	CloseHandle(ThreadHandles[0]);
	CloseHandle(ThreadHandles[1]);


	WSACleanup();

	return 0;
}