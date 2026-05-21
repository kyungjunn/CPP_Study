#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NetUtil.h"

#include <WinSock2.h>
#include <iostream>
#include <map>
#include "json.hpp"

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "NetCommon")

using namespace std;
using json = nlohmann::json;

char Buffer[1024] = { 0, };

map<SOCKET, pair<int, int>> PlayerPositions;

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
	::bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));

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
			SOCKET CurrentSocket = ReadSockets.fd_array[i];

			if (FD_ISSET(CurrentSocket, &CopyReadSockets))
			{
				if (CurrentSocket == ListenSocket)
				{
					//connect process
					SOCKADDR_IN ClientSockAddr;
					memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
					int ClientSockLength = sizeof(ClientSockAddr);

					// blocking, synchronous
					SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockLength);

					cout << "connect client " << inet_ntoa(ClientSockAddr.sin_addr) << endl;

					FD_SET(ClientSocket, &ReadSockets);

					PlayerPositions[ClientSocket] = make_pair(10, 10);
				}
				else
				{
					// Data Receive
					//header
					unsigned short PacketSize = 0;
					int RecvBytes = recv(CurrentSocket, (char*)&PacketSize, sizeof(PacketSize), MSG_WAITALL);
					if (RecvBytes <= 0)
					{
						cout << "header recv fail " << endl;
						PlayerPositions.erase(CurrentSocket); // 접속 끊기면 맵에서 삭제
						DisconnectSocket(CurrentSocket, &ReadSockets);
						continue;
					}

					PacketSize = ntohs(PacketSize);
					memset(Buffer, 0, sizeof(Buffer));

					//data JSON
					RecvBytes = recv(CurrentSocket, Buffer, PacketSize, MSG_WAITALL);

					//int RecvBytes = recv(ReadSockets.fd_array[i], Buffer, sizeof(Buffer), 0);
					if (RecvBytes <= 0)
					{
						cout << "data recv fail " << endl;
						PlayerPositions.erase(CurrentSocket); 
						DisconnectSocket(CurrentSocket, &ReadSockets);
						continue;
					}
					else
					{
						unsigned short FinalDataLength = 0;

						// 수신된 JSON 데이터 파싱
						rapidjson::Document Doc;
						Doc.Parse(Buffer);

						// 플레이어 이동 패킷
						if (Doc.HasMember("PositionX"))
						{
							int currentX = PlayerPositions[CurrentSocket].first;
							int currentY = PlayerPositions[CurrentSocket].second;

							// 클라이언트가 보낸 UserID 
							string userId = Doc["UserID"].GetString();

							if (Doc.HasMember("InputKey"))
							{
								int inputKey = Doc["InputKey"].GetInt();
								if (inputKey == 'w') currentY--;
								else if (inputKey == 's') currentY++;
								else if (inputKey == 'a') currentX--;
								else if (inputKey == 'd') currentX++;
							}

							// 서버의 데이터 업데이트
							PlayerPositions[CurrentSocket] = make_pair(currentX, currentY);

							cout << "[client move] " << userId << " -> (" << currentX << ", " << currentY << ")" << endl;

							// 바뀐 좌표를 JSON 데이터에 주입
							Doc["PositionX"].SetInt(currentX);
							Doc["PositionY"].SetInt(currentY);

							// JSON 으로 변환
							rapidjson::StringBuffer StreamBuffer;
							rapidjson::Writer<rapidjson::StringBuffer> Writer(StreamBuffer);
							Doc.Accept(Writer);

							// 전송용 버퍼에 새로 만든 문자열 복사
							memset(Buffer, 0, sizeof(Buffer));
							memcpy(Buffer, StreamBuffer.GetString(), StreamBuffer.GetSize());

							// 바뀐 패킷 사이즈 재설정
							FinalDataLength = (unsigned short)StreamBuffer.GetSize();
						}
						// 채팅 패킷
						else if (Doc.HasMember("Message"))
						{
							SOCKADDR_IN ClientSockAddr;
							memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
							int ClientSockLength = sizeof(ClientSockAddr);

							getpeername(CurrentSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockLength);

							cout << "[client chat] (" << inet_ntoa(ClientSockAddr.sin_addr);
							cout << ")" << Buffer << " send" << endl;

							FinalDataLength = (unsigned short)strlen(Buffer);
						}


						// 모든 접속한 유저한테 전달
						for (int j = 0; j < (int)ReadSockets.fd_count; ++j)
						{
							// 자기꺼는 그냥 찍고 안 받으면 안돼요
							// 클라이언트에서는 처리 안함.
							if (ReadSockets.fd_array[j] != ListenSocket)
							{
								unsigned short NetworkPacketSize = htons(FinalDataLength);



								//header
								int SentBytes = SendAll(ReadSockets.fd_array[j], (char*)&NetworkPacketSize, 2);
								if (SentBytes <= 0)
								{
									cout << "header send fail." << endl;
									DisconnectSocket(ReadSockets.fd_array[j], &ReadSockets);
								}

								//Data
								SentBytes = SendAll(ReadSockets.fd_array[j], Buffer, FinalDataLength);
								if (SentBytes <= 0)
								{
									cout << "Data send fail." << endl;
									DisconnectSocket(ReadSockets.fd_array[j], &ReadSockets);
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