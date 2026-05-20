#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32")

using namespace std;

char Buffer[1024] = { 0, };

// blocking, synchrous, multiplexing(polling)
int main()
{
	cout << "Server " << endl;
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY;
	ListenSockAddr.sin_port = htons(35000);

	// already use port  이미 포트 사용 중
	bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));

	listen(ListenSocket, SOMAXCONN);

	// blocking, synchronous(TimeOut)
	TIMEVAL TimeOut;
	TimeOut.tv_sec = 0;
	TimeOut.tv_usec = 500000;

	fd_set ReadSockets;
	fd_set CopyReadSockets;

	FD_ZERO(&ReadSockets);
	FD_SET(ListenSocket, &ReadSockets);


	while (true)
	{
		CopyReadSockets = ReadSockets;

		//0.5초씩 blocking
		int ChangeCount = select(0, &CopyReadSockets, 0, 0, &TimeOut);

		if (ChangeCount <= 0)
		{
			// Server Work
			// 0.5초 한 번 서버 작업 하는 거
			continue;
		}

		// 뭔가 자료가 있따
		for (int i = 0; i < (int)ReadSockets.fd_count; ++i)
		{
			if (FD_ISSET(ReadSockets.fd_array[i], &CopyReadSockets))
			{
				if (ReadSockets.fd_array[i] == ListenSocket)
				{
					//connect process
					SOCKADDR_IN ClientSockAddr;
					memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
					int ClientSockLength = sizeof(ClientSockAddr);

					// blocking, synchronous
					SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockLength);

					cout << "connect client " << inet_ntoa(ClientSockAddr.sin_addr) << endl;

					FD_SET(ClientSocket, &ReadSockets);
				}
				else
				{
					// Data Receive
					int RecvBytes = recv(ReadSockets.fd_array[i], Buffer, sizeof(Buffer), 0);
					if (RecvBytes <= 0)
					{
						SOCKADDR_IN ClosedSockAddr;
						memset(&ClosedSockAddr, 0, sizeof(ClosedSockAddr));
						int ClosedSockLength = sizeof(ClosedSockAddr);

						SOCKET ClosedSocket = ReadSockets.fd_array[i];
						getpeername(ClosedSocket, (SOCKADDR*)&ClosedSockAddr, &ClosedSockLength);
						cout << "disconnect client" << inet_ntoa(ClosedSockAddr.sin_addr) << endl;
						FD_CLR(ReadSockets.fd_array[i], &ReadSockets);
						closesocket(ClosedSocket);
					}
					else
					{
						SOCKADDR_IN ClientSockAddr;
						memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
						int ClientSockLength = sizeof(ClientSockAddr);

						getpeername(ReadSockets.fd_array[i], (SOCKADDR*)&ClientSockAddr, &ClientSockLength);

						cout << "client(" << inet_ntoa(ClientSockAddr.sin_addr) << endl;
						cout << ")" << Buffer << " send" << endl;
						// 모든 접속한 유저한테 전달

						for (int j = 0; j < (int)ReadSockets.fd_count; ++j)
						{
							// 자기꺼는 그냥 찍고 안 받으면 안돼요
							// 클라이언트에서는 처리 안함.
							if (ReadSockets.fd_array[j] != ListenSocket)
							{
								int SentBytes = send(ReadSockets.fd_array[j], Buffer, sizeof(Buffer), 0);
								if (SentBytes <= 0)
								{
									SOCKADDR_IN ClosedSockAddr;
									memset(&ClosedSockAddr, 0, sizeof(ClosedSockAddr));
									int ClosedSockLength = sizeof(ClosedSockAddr);

									SOCKET ClosedSocket = ReadSockets.fd_array[j];
									getpeername(ClosedSocket, (SOCKADDR*)&ClosedSockAddr, &ClosedSockLength);
									cout << "send fail." << endl;
									cout << "disconnect send" << inet_ntoa(ClosedSockAddr.sin_addr) << endl;
									FD_CLR(ReadSockets.fd_array[j], &ReadSockets);
									closesocket(ClosedSocket);
								}
							}
						}
					}
				}
			}
		}
	}






	closesocket(ListenSocket);

	WSACleanup();
	return 0;
}