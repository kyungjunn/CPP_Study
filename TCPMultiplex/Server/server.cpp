#define FD_SETSIZE		100

#include <WinSock2.h>
#include <iostream>
#include <set>


#pragma comment(lib, "ws2_32")

int main()
{
	// 초기화
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 소켓 생성
	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ListenSocketAddr;
	memset(&ListenSocketAddr, 0, sizeof(ListenSocketAddr));
	ListenSocketAddr.sin_family = AF_INET;
	ListenSocketAddr.sin_addr.s_addr = INADDR_ANY;
	ListenSocketAddr.sin_port = htons(43000);

	// bind
	bind(ListenSocket, (SOCKADDR*)&ListenSocketAddr, sizeof(ListenSocketAddr));
	
	// listen
	listen(ListenSocket, 5);

	SOCKADDR_IN ClientSocketAddr;
	memset(&ClientSocketAddr, 0, sizeof(ClientSocketAddr));
	int ClientSockAddrLength = sizeof(ClientSocketAddr);


	// 다했냐? 물어보기 
	int ReadSocketCount = 0; //windows X

	fd_set ReadSockets; // set -> 집합
	fd_set CopyReadSockets; // 복사본

	FD_ZERO(&ReadSockets); // 지우기 , 하나만 지우는건 FD_CLR
	FD_SET(ListenSocket, &ReadSockets); // 계속 감시할 소켓 -> ListenSocket 

	struct timeval TimeOut;

	// 0.100 초 기다림
	TimeOut.tv_sec = 0;
	TimeOut.tv_usec = 500000; // 마이크로초

	while (true)
	{
		CopyReadSockets = ReadSockets; // 복사본에 넣어주기

		//polling
		int ChangeSocketCount = select(0, &CopyReadSockets, nullptr, nullptr, &TimeOut); // select -> Inout_opt 입력 출력 다 됨.
		if (ChangeSocketCount <= 0)
		{
			//실 서버 작업을 함.
			//tick
			continue;
		}

		for (int i = 0; i < (int)ReadSockets.fd_count; ++i)
		{	
			// 바꼈냐?
			if (FD_ISSET(ReadSockets.fd_array[i], &CopyReadSockets))
			{
				// 그거 리슨이냐?
				if (ReadSockets.fd_array[i] == ListenSocket)
				{
					SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSocketAddr, &ClientSockAddrLength);
					printf("connect client\n");
					// ReadSocket에 ClientSocket 넣기
					FD_SET(ClientSocket, &ReadSockets);
				}
				else // recv. 리슨이 아니면(이미 연결된 클라이언트라면)
				{
					char Buffer[1024] = { 0, };

					int RecvBytes = recv(ReadSockets.fd_array[i], Buffer, sizeof(Buffer), 0);
					if (RecvBytes <= 0)
					{
						printf("disconnect client\n");
						closesocket(ReadSockets.fd_array[i]);
						FD_CLR(ReadSockets.fd_array[i], &ReadSockets);
					}
					
					else // 클라이언트한테 뭐가 하나 들어옴.
					{
						for (int j = 0; j < (int)ReadSockets.fd_count; ++j) 
						{																			
							SOCKET TargetSocket = ReadSockets.fd_array[j];

							// 리슨소켓 제외하고 전송
							if (TargetSocket != ListenSocket)
							{
								int SendBytes = send(TargetSocket, Buffer, sizeof(Buffer), 0);
								if (SendBytes <= 0)
								{
									printf("server multi send error");
									closesocket(TargetSocket);
									FD_CLR(TargetSocket, &ReadSockets);
								}
							}
						}
						printf("server recv : %s\n", Buffer);
					}
				}
			}																					
		}
	}


	closesocket(ListenSocket);


	WSACleanup();

	return 0;
}