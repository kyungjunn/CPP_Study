#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32")

using namespace std;

int main()
{
	// winsock.dll -> 정확히는 ws2_32.dll 로딩  winsock -> bsd socket 윈도우에서 구현체
	// 초기화
	WSAData wsaData;

	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (Result != 0)
	{
		cout << "WSAStartup Error" << WSAGetLastError() << endl; // GetLastError  마지막으로 난 에러 알려주셈
		exit(-1); // 바로 실행 끝내버리기.
	}

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "socket Error" << WSAGetLastError() << endl;
		exit(-1);
	}

	// 내가 접속할 주소
	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr)); // 시작위치, 값, 사이즈
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 무조건 자기 자신 IPv4 127.0.0.1, 192.168.0.97
	ServerSockAddr.sin_port = htons(1234); // 포트번호


	srand((unsigned int)time(NULL));


	// blocking 함수
	Result = connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	if (Result == SOCKET_ERROR)
	{
		cout << "connect Error" << WSAGetLastError() << endl;
		exit(-1);
	}


	while (1)
	{
		char Buffer[6];

		int number1 = rand() % 90 + 10;
		int number2 = rand() % 90 + 10;

		char Operators[4] = { '+', '-', '*', '/' };

		char Op = Operators[rand() % 4];

		// 0 나누기 방지
		if (Op == '/')
		{
			number2 = rand() % 89 + 1;
		}

		Buffer[0] = (number1 / 10) + '0';
		Buffer[1] = (number1 % 10) + '0';

		Buffer[2] = Op;

		Buffer[3] = (number2 / 10) + '0';
		Buffer[4] = (number2 % 10) + '0';

		cout << "number 1 : " << number1 << endl;
		cout << "operator : " << Op << endl;
		cout << "number 2 : " << number2 << endl;

		int RecvLength = send(ServerSocket, Buffer, sizeof(Buffer), 0);
		if (RecvLength <= 0)
		{
			cout << "send Error" << endl;
		}

		// 결과 받기
		char RecvBuffer[16] = { 0, };

		int RecvBytes = recv(ServerSocket, RecvBuffer, sizeof(RecvBuffer), 0);

		if (RecvBytes > 0)
		{
			int ResultValue = atoi(RecvBuffer);
			cout << "Result : " << ResultValue << endl;
		}

	}
	closesocket(ServerSocket);


	WSACleanup();

	return 0;
}