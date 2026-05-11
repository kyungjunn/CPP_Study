#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32")

using namespace std;

int main()
{
	// winsock.dll -> 정확히는 ws2_32.dll 로딩  winsock -> bsd socket 윈도우에서 구현체
	WSAData wsaData;

	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (Result != 0)
	{
		cout << "WSAStartup Error" << WSAGetLastError() << endl; // GetLastError  마지막으로 난 에러 알려주셈
		exit(-1); // 바로 실행 끝내버리기.
	}

	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "socket Error" << WSAGetLastError() << endl; 
		exit(-1);
	}	


	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr)); // 시작위치, 값, 사이즈
	ListenSockAddr.sin_family = AF_INET; 
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY; //-> 설정 파일 / INADDR_ANY 아무거나 다 들어와
	ListenSockAddr.sin_port = htons(1234); // 포트번호

	Result = bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));
	if (Result == SOCKET_ERROR)
	{
		cout << "bind Error" << WSAGetLastError() << endl;
		exit(-1);
	}
	
	// 누가 전화걸면 오는지 봐야함 -> 듣는다 -> listen
	Result = listen(ListenSocket, SOMAXCONN);
	if (Result == SOCKET_ERROR)
	{
		cout << "listen Error" << WSAGetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int LengthClientSockAddr = sizeof(ClientSockAddr);

	// blocking 함수. 누가 들어오기 전까지 멈춰있음.
	// 전화가 오면 받는다 -> accept
	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &LengthClientSockAddr);

	if (ClientSocket == INVALID_SOCKET)
	{
		cout << "accept Error" << WSAGetLastError() << endl;
		exit(-1);
	}


	// 서버는 종료하지 않음.
	while (true)
	{
		char Buffer[6] = { 0, };



		int RecvBytes = recv(ClientSocket, Buffer, sizeof(Buffer), 0);

		if (RecvBytes > 0)
		{
			int ResultValue = 0;

			char Op = Buffer[2];

			int Number1 = (Buffer[0] - '0') * 10 + (Buffer[1] - '0');	
			int Number2 = (Buffer[3] - '0') * 10 + (Buffer[4] - '0');

			cout << "Number1 : " << Number1 << endl;
			cout << "Operator: " << Op << endl;
			cout << "Number2 : " << Number2 << endl;

			switch (Op)
			{
			case '+':
				ResultValue = Number1 + Number2;
				break;

			case '-':
				ResultValue = Number1 - Number2;
				break;

			case '*':
				ResultValue = Number1 * Number2;
				break;

			case '/':
				ResultValue = Number1 / Number2;
				break;

			default:
				cout << "Unknown Operator" << endl;
				break;
			}

			cout << "Result : " << ResultValue << endl;

			char SendBuffer[16] = { 0, };

			sprintf(SendBuffer, "%d", ResultValue);
			//SendBuffer[0] = (ResultValue / 1000) % 10 + '0';
			//SendBuffer[1] = (ResultValue / 100) % 10 + '0';
			//SendBuffer[2] = (ResultValue / 10) % 10 + '0';
			//SendBuffer[3] = ResultValue % 10 + '0';

			send(ClientSocket, SendBuffer, sizeof(SendBuffer), 0);
		}
	}

	closesocket(ClientSocket);
	closesocket(ListenSocket);


	WSACleanup();

	return 0;
}