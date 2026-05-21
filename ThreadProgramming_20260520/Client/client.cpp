#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "ChatPacket.h"
#include "PlayerPositionPacket.h"
#include "PlayerDirectionPacket.h"
#include "NetUtil.h"

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <process.h>
#include <conio.h>
#include <map>

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

string MyUserID = "";

// 서버로부터 받은 모든 유저의 실시간 좌표를 저장하는 테이블
// key: UserID(string), value: pair<int, int> (X, Y 좌표)
std::map<std::string, std::pair<int, int>> OnlinePlayers;

// 렌더링 함수
void RenderMap()
{
	system("cls");

	const int MAP_WIDTH = 20;
	const int MAP_HEIGHT = 10;

	cout << "========= MULTIPLAYER GAME [" << MyUserID << "] =========" << endl;

	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			bool isPlayerDrawn = false;

			// 현재 (x, y) 좌표에 존재하는 유저가 있는지 전역 맵에서 검색
			for (auto const& playerPair : OnlinePlayers)
			{
				string userId = playerPair.first;
				pair<int, int> position = playerPair.second;

				if (position.first == x && position.second == y)
				{
					if (userId == "Player1") cout << "1 ";
					else if (userId == "Player2") cout << "2 ";
					else cout << "P ";

					isPlayerDrawn = true;
					break;
				}
			}

			// 해당 좌표에 플레이어가 없다면 빈 공간(.) 출력
			if (!isPlayerDrawn)
			{
				cout << ". ";
			}
		}
		cout << endl;
	}
	cout << "====================================" << endl;
	cout << "[WASD] 이동 | [T] 채팅 입력" << endl;
}

unsigned WINAPI RecvThread(void* Argument)
{
	SOCKET ServerSocket = *(SOCKET*)Argument;

	while (IsRecvThreadRunning)
	{
		unsigned short PacketSize = 0;

		//header
		int RecvBytes = recv(ServerSocket, (char*)&PacketSize, sizeof(PacketSize), MSG_WAITALL);
		if (RecvBytes <= 0)
		{
			cout << "recv fail " << endl;
			break;
		}

		PacketSize = ntohs(PacketSize);

		memset(RecvBuffer, 0, sizeof(RecvBuffer));

		//data JSON
		RecvBytes = recv(ServerSocket, RecvBuffer, PacketSize, MSG_WAITALL);
		if (RecvBytes <= 0)
		{
			cout << "recv fail." << endl;
			break;
		}

		rapidjson::Document Doc;
		Doc.Parse(RecvBuffer);

		if (Doc.HasMember("PositionX"))
		{
			PlayerPositionPacket PositionData;
			PositionData.Parse(RecvBuffer);

			// 좌표를 클라이언트 관리 테이블에 갱신
			OnlinePlayers[PositionData.UserID] = make_pair(PositionData.PositionX, PositionData.PositionY);

			RenderMap();

			cout << "[위치]" << PositionData.UserID << " : " << PositionData.PositionX << ", " << PositionData.PositionY << endl;
		}
		else if (Doc.HasMember("Message"))
		{
			ChatPacket Data;
			Data.Parse(RecvBuffer);

			cout << "[채팅]" << Data.UserID << " : " << Data.Message << " " << Data.Gold << endl;
		}
	}

	return 0;
}

void SetPositionPacket(SOCKET ServerSocket, int InX, int InY, char InKey)
{

	// 플레이어 위치 패킷
	PlayerPositionPacket PositionData;
	PositionData.UserID = MyUserID;
	PositionData.PositionX = InX;
	PositionData.PositionY = InY;
	PositionData.InputKey = (int)InKey;

	std::string JSONString = PositionData.ToString();
	unsigned short PacketSize = (unsigned short)JSONString.length();
	PacketSize = htons(PacketSize);

	//header
	int SentBytes = SendAll(ServerSocket, (char*)&PacketSize, 2);
	if (SentBytes <= 0)
	{
		cout << "header send fail." << endl;
	}

	//Data
	SentBytes = SendAll(ServerSocket, JSONString.c_str(), ntohs(PacketSize));
	if (SentBytes <= 0)
	{
		cout << "data send fail." << endl;
	}
}

unsigned WINAPI SendThread(void* Argument)
{
	// 책임은 사용하는 놈이 진다.
	SOCKET ServerSocket = *(SOCKET*)Argument;

	// 플레이어 시작 좌표
	int PlayerX = 10;
	int PlayerY = 5;

	SetPositionPacket(ServerSocket, PlayerX, PlayerY, ' ');

	while (IsSendThreadRunning)
	{
		char Keycode = _getch();

		if (Keycode == 'w' || Keycode == 'a' || Keycode == 's' || Keycode == 'd')
		{
			if (Keycode == 'w' && PlayerY > 0) PlayerY--;
			else if (Keycode == 's' && PlayerY < 9) PlayerY++;
			else if (Keycode == 'a' && PlayerX > 0) PlayerX--;
			else if (Keycode == 'd' && PlayerX < 19) PlayerX++;

			SetPositionPacket(ServerSocket, PlayerX, PlayerY, Keycode);
		}
		else if (Keycode == 't')
		{
			cin.getline(SendBuffer, sizeof(SendBuffer));
			std::string InputString(SendBuffer);

			// 채팅 패킷
			ChatPacket Data;
			Data.UserID = "NULLPTR";
			Data.Message = SendBuffer;
			Data.Gold = 1000;
			std::string JSONString = Data.ToString();


			unsigned short PacketSize = (unsigned short)JSONString.length();
			PacketSize = htons(PacketSize);

			//header
			int SentBytes = SendAll(ServerSocket, (char*)&PacketSize, 2);
			if (SentBytes <= 0)
			{
				cout << "header send fail." << endl;
				break;
			}

			//Data
			SentBytes = SendAll(ServerSocket, JSONString.c_str(), ntohs(PacketSize));
			if (SentBytes <= 0)
			{
				cout << "data send fail." << endl;
				break;
			}
		}
	}


	return 0;
}

int main()
{
	cout << "이 클라이언트의 아이디를 입력하세요 (Player1 또는 Player2): ";
	cin >> MyUserID;
	cin.ignore();

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
	//SuspendThread(ThreadHandles[0]); // 스레드 일시 중단
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