#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include "ChatPacket.h"										
#include "NetUtil.h"

#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <process.h>
#include <conio.h>
#include "SDL.h"

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "NetCommon")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")

using namespace std;

char SendBuffer[1024] = { 0, };
char RecvBuffer[1024] = { 0, };

bool bIsRunning = true;
bool IsRecvThreadRunning = true;
bool IsSendThreadRunning = true;

// ActorList
SessionManager MySessionManager;
SOCKET MyClientID;

// 윈도우 창 초기화
SDL_Window* MyWindow = nullptr;

// 윈도우 렌더러 초기화
SDL_Renderer* MyRenderer = nullptr;

// 키 입력 알림 이벤트 헨들
HANDLE hSendEvent = nullptr;      

// 공유 KeyCode
SDL_Keycode SharedKeyCode = 0;

void Render(SDL_Renderer* InRenderer)
{
	system("cls");

	// 지우기
	SDL_SetRenderDrawColor(InRenderer, 255, 255, 255, 255);
	SDL_RenderClear(InRenderer);

	for (auto Player : MySessionManager.SessionList)
	{
		COORD Where;
		Where.X = Player.X;
		Where.Y = Player.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Where);

		std::cout << (char)Player.Shape << endl;

		// 사각형 그리기
		int TileSize = 20;
		SDL_SetRenderDrawColor(InRenderer, 255, 0, 0, 255);
		SDL_Rect Square = { Player.X * TileSize, Player.Y * TileSize, TileSize, TileSize };
		SDL_RenderFillRect(InRenderer, &Square);
	}
	// Cpu -> Gpu 보내기
	SDL_RenderPresent(InRenderer);
}

void ProcessPacket(SOCKET ProcessSocket, const char* InBuffer, const Header& InHeader)
{
	switch ((EPacketType)InHeader.PacketType)
	{
	case EPacketType::S2C_Login:
	{
		S2C_Login LoginPacket;
		LoginPacket.Parse(InBuffer);
		//cout << LoginPacket.ToString() << endl;
		MyClientID = LoginPacket.ClientSocketID;
	}
	break;
	case EPacketType::S2C_Spawn:
	{
		S2C_Spawn SpawnData;
		SpawnData.Parse(InBuffer);
		std::cout << SpawnData.ToString() << endl;

		Session InSession;
		InSession.ClientSocket = SpawnData.ClientSocket;
		InSession.Shape = SpawnData.Shape;
		InSession.X = SpawnData.X;
		InSession.Y = SpawnData.Y;

		MySessionManager.Add(InSession);
		//Render(MyRenderer);
	}
	break;
	case EPacketType::S2C_Move:
	{
		S2C_Move MoveData;
		MoveData.Parse(InBuffer);
		Session* FindSession = MySessionManager.GetSession(MoveData.ClientSocket);
		FindSession->X = MoveData.X;
		FindSession->Y = MoveData.Y;

		//std::cout << MoveData.ToString() << endl;
		//Render(MyRenderer);
	}
	break;
	case EPacketType::S2C_Destroy:
	{
		S2C_Destroy DestroyPacket;
		DestroyPacket.Parse(InBuffer);

		Session* FindSession = MySessionManager.GetSession(DestroyPacket.ClientSocket);

		//std::cout << "Quit : " << FindSession->ClientSocket << endl;

		MySessionManager.Delete(*FindSession);

		//Render(MyRenderer);
	}
	break;
	}


}

unsigned WINAPI RecvThread(void* Argument)
{
	SOCKET ServerSocket = *(SOCKET*)Argument;

	while (IsRecvThreadRunning)
	{
		unsigned short PacketSize = 0;

		//header
		Header DataHeader;
		int RecvBytes = RecvAll(ServerSocket, (char*)&DataHeader, HeaderSize);
		if (RecvBytes <= 0)
		{
			std::cout << "header recv fail " << endl;
			break;
		}

		DataHeader.NetworkToHost();

		memset(RecvBuffer, 0, sizeof(RecvBuffer));
		//data JSON
		RecvBytes = RecvAll(ServerSocket, RecvBuffer, DataHeader.PacketSize);
		if (RecvBytes <= 0)
		{
			std::cout << "Data recv fail " << endl;
			break;
		}

		ProcessPacket(ServerSocket, RecvBuffer, DataHeader);
	}

	bIsRunning = false;
	return 0;
}

unsigned WINAPI SendThread(void* Argument)
{
	//책임은 사용하는 놈이 진다.
	SOCKET ServerSocket = *(SOCKET*)Argument;

	while (IsSendThreadRunning)
	{
		//int KeyCode = _getch();
		//if (!(KeyCode == 'w' ||
		//	KeyCode == 'W' ||
		//	KeyCode == 'a' ||
		//	KeyCode == 'A' ||
		//	KeyCode == 's' ||
		//	KeyCode == 'S' ||
		//	KeyCode == 'd' ||
		//	KeyCode == 'D'))
		//{
		//	continue;
		//}
		WaitForSingleObject(hSendEvent, INFINITE);

		if (!IsSendThreadRunning) break;

		C2S_Move MoveData;
		MoveData.ClientSocket = MyClientID;
		MoveData.Direction = SharedKeyCode;


		//header
		Header DataHeader;
		DataHeader.MakeHeader((int)(MoveData.ToString().length()), EPacketType::C2S_Move);
		int SentBytes = SendAll(ServerSocket, (char*)&DataHeader, HeaderSize);
		if (SentBytes <= 0)
		{
			std::cout << "header send fail." << endl;
		}

		//Data
		SentBytes = SendAll(ServerSocket, MoveData.ToString().c_str(), (int)(MoveData.ToString().length()));
		if (SentBytes <= 0)
		{
			std::cout << "Data send fail." << endl;
		}

	}

	return 0;
}

int SDL_main(int argc, char* argv[])
{
	std::cout << "client " << endl;

	// SDL 라이브러리 초기화
	SDL_Init(SDL_INIT_EVERYTHING);

	// 윈도우 창 생성
	MyWindow = SDL_CreateWindow("MyWindow", 100, 100, 1024, 720, SDL_WINDOW_SHOWN);

	// 윈도우 렌더러 생성
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, 0);

	// 동기화 이벤트 객체 생성 (자동 리셋 모드)
	hSendEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("192.168.0.97");
	ServerSockAddr.sin_port = htons(35000);

	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	std::cout << "client connect" << endl;

	C2S_Login LoginData;
	LoginData.UserID = "kyungjun";
	LoginData.HashKey = "1q2w3e4r5t";

	Header LoginHeader;
	LoginHeader.MakeHeader(static_cast<unsigned short>(LoginData.ToString().length()), EPacketType::C2S_Login);

	//Login 요청
	if (SendAll(ServerSocket, (char*)&LoginHeader, HeaderSize) <= 0)
	{
		std::cout << "login header Error" << endl;
	}

	if (SendAll(ServerSocket, LoginData.ToString().c_str(), (int)LoginData.ToString().length()) <= 0)
	{
		std::cout << "login data Error" << endl;
	}

	HANDLE ThreadHandles[2] = { 0, };

	//nonblocking, asynchrous
	ThreadHandles[0] = (HANDLE)_beginthreadex(0, 0, RecvThread, &ServerSocket, /*CREATE_SUSPENDED*/0, 0);
	ThreadHandles[1] = (HANDLE)_beginthreadex(0, 0, SendThread, &ServerSocket, /*CREATE_SUSPENDED*/0, 0);
	//ResumeThread(ThreadHandles[0]);
	//ResumeThread(ThreadHandles[1]);
	//SuspendThread(ThreadHandles[0]);
	//SuspendThread(ThreadHandles[1]);

	while (bIsRunning)
	{
		SDL_Event MyEvent;
		while (SDL_PollEvent(&MyEvent))
		{
			if (MyEvent.type == SDL_QUIT)
			{
				bIsRunning = false;
			}
			else if (MyEvent.type == SDL_KEYDOWN)
			{
				SDL_Keycode KeyCode = MyEvent.key.keysym.sym;
				if (KeyCode == SDLK_w || KeyCode == SDLK_s || KeyCode == SDLK_a || KeyCode == SDLK_d)
				{
					// 대기 중인 SendThread를 깨움
					SharedKeyCode = KeyCode;
					SetEvent(hSendEvent);
				}
			}
		}
		
		Render(MyRenderer);
	}
	

	//blocking
	WaitForMultipleObjects(2, ThreadHandles, FALSE, INFINITE);

	closesocket(ServerSocket);

	std::cout << "End Thread" << endl;

	//TerminateThread(ThreadHandles[0], 0);
	//TerminateThread(ThreadHandles[1], 0);
	IsSendThreadRunning = false;
	IsRecvThreadRunning = false;


	CloseHandle(ThreadHandles[0]);
	CloseHandle(ThreadHandles[1]);
	CloseHandle(hSendEvent);

	WSACleanup();

	// 지우기 
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
	SDL_Quit();

	return 0;
}