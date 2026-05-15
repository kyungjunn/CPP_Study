#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <Winsock2.h>

#include <iostream>
#include <conio.h>

#include "Packet.h"

#pragma comment(lib, "ws2_32")

#define SERVER_IP	"127.0.0.1"

using namespace std;

//4byte 
// 패킷헤더 생성
void MakePacketHeader(PacketHeader& OutPacketHeader, int DataSize, PacketType Type)
{
	OutPacketHeader.Size = htonl(DataSize);
	OutPacketHeader.Code = htons(static_cast<unsigned short>(Type)); // 정적으로 바꿔버리겠다. (unsigned short)Type 해도 됨.
}

void SendAll(SOCKET ReceiverSocket, char* Data, int Size)
{
	int WantSendDataSize = Size;
	int TotalSendDataSize = 0;
	int SentBytes = 0;
	int Count = 0;

	do
	{
		SentBytes = send(ReceiverSocket, Data + TotalSendDataSize, WantSendDataSize - TotalSendDataSize, 0);
		if (SentBytes <= 0)
		{
			return;
		}
		TotalSendDataSize += SentBytes;
		if (SentBytes <= 0)
		{
			return;
		}
		printf("Send %dBytes %d Count\n", SentBytes, Count++);

	} while (TotalSendDataSize < WantSendDataSize);
}

void ProcessPositionPacket(SOCKET SenderSocket, int DataSize)
{
	PositionData Data;

	int RecvBytes = recv(SenderSocket, (char*)&Data, DataSize, MSG_WAITALL);
	Data.X = ntohl(Data.X);
	Data.Y = ntohl(Data.Y);

	printf("Player Position(%d, %d)\n", Data.X, Data.Y);
}

int main()
{
	// 윈도우용 소켓 이건 기본중에 기본. WSACleanup까지
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 소켓 생성
	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 소켓 주소 설정
	SOCKADDR_IN ServerSockAddr;
	//ZeroMemory(&ServerSockAddr, sizeof(ServerSockAddr));
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr(SERVER_IP); _WINSOCK_DEPRECATED_NO_WARNINGS
		ServerSockAddr.sin_port = htons(31000);



	int SendBufferSize = 0;
	int RecvBufferSize = 0;
	int BufferSizeLength = sizeof(SendBufferSize);

	RecvBufferSize = 8 * 1024; // 1000 -> 1k, 2^10 1024
	BufferSizeLength = sizeof(RecvBufferSize);

	//getsockopt(ServerSocket, SOL_SOCKET, SO_SNDBUF, (char*)&SendBufferSize, &BufferSizeLength);
	//printf("Send Buffer Size: %d\n", SendBufferSize);


	//setsockopt(ServerSocket, SOL_SOCKET, SO_SNDBUF, (char*)&SendBufferSize, BufferSizeLength);

	getsockopt(ServerSocket, SOL_SOCKET, SO_RCVBUF, (char*)&RecvBufferSize, &BufferSizeLength);
	printf("Receive Buffer Size : %d\n", RecvBufferSize);

	setsockopt(ServerSocket, SOL_SOCKET, SO_RCVBUF, (char*)&RecvBufferSize, sizeof(BufferSizeLength));

	getsockopt(ServerSocket, SOL_SOCKET, SO_RCVBUF, (char*)&RecvBufferSize, &BufferSizeLength);
	printf("Receive Buffer Size : %d\n", RecvBufferSize);

	//3way handshake
	// 소켓과 주소 연결
	// int 라서 0이면 예외처리 해야함
	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	// DB
	// authentication 인증, 로그인 -> token, key / authorization 인가


	while (true)
	{
		PacketHeader Header;

		MoveData Data;
		Data.Dir = _getch();

		if (Data.Dir == 'F' || Data.Dir == 'f')
		{
			// 파일 요청
			MakePacketHeader(Header, 0, PacketType::C2S_File); // 패킷헤더 생성 함수로.

			//char Buffer[1024] = { 0, };
			// [][][][] [][]
			//memcpy(Buffer, &Header, sizeof(Header));
			//SendAll(ServerSocket, Buffer, sizeof(Header) + sizeof(Data));
			SendAll(ServerSocket, (char*)&Header, sizeof(Header));

			// 파일 받기 헤더
			int RecvBytes = recv(ServerSocket, (char*)&Header, sizeof(Header), MSG_WAITALL);
			Header.Size = ntohl(Header.Size);
			Header.Code = ntohs(Header.Code);

			switch ((PacketType)(Header.Code))
			{
			case PacketType::S2C_File:

				// 파일 받기
				FILE* OutputFile = fopen("워모그.png", "wb");

				int FileSize = Header.Size;
				int TotalFileWriteSize = 0;
				char Buffer[512] = { 0, };
				size_t WriteSize = 0;
				int Count = 0;


				do
				{
					printf("%d\n", Count++);

					int RecvBytes = 0;
					
					// 8192 작은 파일이면 버퍼만큼 받는게 아니라
					if (FileSize - TotalFileWriteSize < sizeof(Buffer))
					{
						// 받을 사이즈가 버퍼보다 작을 경우
						RecvBytes = recv(ServerSocket, Buffer, FileSize - TotalFileWriteSize, MSG_WAITALL);
						if (RecvBytes <= 0)
						{
							break;
						}
					}
					else
					{
						RecvBytes = recv(ServerSocket, Buffer, sizeof(Buffer), MSG_WAITALL);
						if (RecvBytes <= 0)
						{
							break;
						}
					}

					WriteSize = fwrite(Buffer, sizeof(char), RecvBytes, OutputFile);
					TotalFileWriteSize += (int)WriteSize;
				} while (TotalFileWriteSize < FileSize);

				fclose(OutputFile);
				break;
			}
		}
		else
		{
			// 이동 요청
			MakePacketHeader(Header, sizeof(MoveData), PacketType::Move); // 패킷헤더 생성 함수로.


			//[][][][] []
			char Buffer[1024] = { 0, };
			//[][][][]
			memcpy(Buffer, &Header, sizeof(Header));
			// [header][header][header][header] [data]. 
			// Buffer의 시작 주소에서 Header의 크기만큼 뒤로 이동한 지점의 주소
			memcpy(&Buffer[0] + sizeof(Header), &Data, sizeof(Data)); // 버퍼 첫번째값의 주소 + 그 주소로부터 Header 크기(4) 만큼 이동

			// 서버한테 보내기
			//send(ServerSocket, Buffer, sizeof(Header) + sizeof(Data), 0);
			SendAll(ServerSocket, Buffer, sizeof(Header) + sizeof(Data));


			// 받기
			// OS 버퍼에서 가져올 수 있는 만큼 가져올 때까지 기다림.
			int RecvBytes = recv(ServerSocket, (char*)&Header, sizeof(Header), MSG_WAITALL);
			Header.Size = ntohl(Header.Size);
			Header.Code = ntohs(Header.Code);

			switch ((PacketType)(Header.Code))
			{
			case PacketType::Position:
				ProcessPositionPacket(ServerSocket, Header.Size);
				break;
			}
		}
	}

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}