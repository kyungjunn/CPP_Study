#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NetUtil.h"
//#include "DBManager.h"
#include "jdbc/mysql_connection.h"
#include "jdbc/cppconn/driver.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/prepared_statement.h"

#include <winsock2.h>
#include <iostream>


#pragma comment(lib, "ws2_32")
#pragma comment(lib, "NetCommon")

#ifndef _DEBUG
#pragma comment(lib, "mysqlcppconn")
#else
#pragma comment(lib, "debug/mysqlcppconn")
#endif // !_DEBUG


using namespace std;

char Buffer[65536] = { 0, };

SessionManager MySessionManager;
//DBManager MyDBManager;

sql::Driver* MyDriver; //workbench
sql::Connection* MyConnection; //접속 정보
sql::ResultSet* MyResultSet; // 결과 창
sql::PreparedStatement* MyPreparedStatement; // 쿼리 만들 때 injection 방어.

void ConnectDB()
{
	try
	{
		// MySQL 연결
		MyDriver = get_driver_instance(); //드라이버 싱글톤 생성 -> 그리고 자동으로 지워줌.
		MyConnection = MyDriver->connect("tcp://127.0.0.1", "june021124", "rudwns1124");

		// DataBase 연결
		MyConnection->setSchema("membership");
	}
	catch (sql::SQLException Exception)
	{
		std::cout << Exception.what() << std::endl;
		std::cout << Exception.getSQLState() << std::endl;
	}
}

bool Login(std::string UserID, std::string Password)
{
	// Stored Procesdure를 사용.
	sql::SQLString Query = "select * from user where user_id = ? and user_pw = ? and is_delete = 'N'";

	// 실행
	MyPreparedStatement = MyConnection->prepareStatement(Query);

	// 값 바인딩
	MyPreparedStatement->setString(1, UserID);
	MyPreparedStatement->setString(2, Password);

	// 쿼리 실행
	MyResultSet = MyPreparedStatement->executeQuery();

	std::cout << Query << std::endl;

	if (MyResultSet->rowsCount() == 0)
	{
		//Redis와 같은 캐시 서버에 저장
		//hash 키 값을 전송
		std::cout << "아이디 비번이 틀립니다." << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}

bool Signup(std::string UserID, std::string Password, std::string Name)
{
	try
	{
		// SQL X
		sql::SQLString Query = "insert into user (`user_id`, `user_pw`, `name`) values (?, ?, ?);";

		// 실행
		MyPreparedStatement = MyConnection->prepareStatement(Query);

		// 값 바인딩
		MyPreparedStatement->setString(1, UserID);
		MyPreparedStatement->setString(2, Password);
		MyPreparedStatement->setString(3, Name);

		// 쿼리 실행
		MyResultSet = MyPreparedStatement->executeQuery();

		std::cout << Query << std::endl;
	}
	catch (sql::SQLException Exception)
	{
		std::cout << "이미 사용하는 아이디" << std::endl;
		return false;
	}

	return true;
}
bool Logout()
{
	//서버 한대로 작업, 서비스?
	return true;
}

void DisconnectSocket(SOCKET DisconnectedSocket, fd_set* Sockets)
{
	SOCKET ClosedSocket = DisconnectedSocket;

	SOCKADDR_IN ClosedSockAddr;
	memset(&ClosedSockAddr, 0, sizeof(ClosedSockAddr));
	int ClosedSockAddrLength = sizeof(ClosedSockAddr);

	getpeername(ClosedSocket, (SOCKADDR*)&ClosedSockAddr, &ClosedSockAddrLength);

	cout << "disconnect : " << ClosedSocket << endl;

	cout << "disconnect : " << inet_ntoa(ClosedSockAddr.sin_addr) << endl;

	FD_CLR(ClosedSocket, Sockets);
	closesocket(ClosedSocket);


	flatbuffers::FlatBufferBuilder SendBuilder;

	auto DestroyData = UserPacket::CreateS2C_Destroy(
		SendBuilder,
		(uint16_t)ClosedSocket
	);

	auto UserPacketData = UserPacket::CreatePacketData(
		SendBuilder,
		UserPacket::PacketType_S2C_Destroy,
		DestroyData.Union()
	);

	SendBuilder.Finish(UserPacketData);

	//dangling pointer
	// 로그인된 세션인지 찾음
	Session* FindSession = MySessionManager.GetSession(ClosedSocket);

	if (FindSession)
	{
		MySessionManager.Delete(*FindSession);
	}

	//모든 유저한테 이동 패킷 보내줌
	for (auto Receiver : MySessionManager.SessionList)
	{
		SendAll(Receiver.ClientSocket, SendBuilder);
	}
}

void ProcessPacket(SOCKET ProcessSocket, const char* InBuffer)
{
	auto UserPacketData = UserPacket::GetPacketData(InBuffer);

	switch (UserPacketData->data_type())
	{
	case UserPacket::PacketType_C2S_Login:
	{
		auto LoginPacket = UserPacketData->data_as_C2S_Login();

		bool Result = Login(LoginPacket->user_id()->c_str(), LoginPacket->user_pw()->c_str());

		//std::string UserID = LoginPacket->user_id()->c_str();
		//std::string UserPW = LoginPacket->user_pw()->c_str();
		//bool bLogin = MyDBManager.AuthenticateUser(UserID, UserPW);

		flatbuffers::FlatBufferBuilder SendBuilder;

		if (Result) //bLogin
		{
			std::cout << "로그인에 성공 했습니다" << endl;

			Session InSession;
			InSession.ClientSocket = ProcessSocket;
			InSession.UserID = LoginPacket->user_id()->c_str();
			InSession.X = rand() % 640;
			InSession.Y = rand() % 480;
			InSession.R = rand() % 255;
			InSession.G = rand() % 255;
			InSession.B = rand() % 255;

			InSession.Shape = 65 + (rand() % 26);

			MySessionManager.Add(InSession);
			//접속한 아이한테 확인 패킷(S2C_Login)

			auto S2C_Login_Data = UserPacket::CreateS2C_Login(
				SendBuilder,
				(uint16_t)ProcessSocket,
				SendBuilder.CreateString("Welcome."),
				SendBuilder.CreateString("qw3oddpui2"),
				true
			);

			auto UserPacketData = UserPacket::CreatePacketData(
				SendBuilder,
				UserPacket::PacketType_S2C_Login,
				S2C_Login_Data.Union()
			);

			SendBuilder.Finish(UserPacketData);
			SendAll(ProcessSocket, SendBuilder);

			//접속한 모든 유저한테 현재 모든 유저의 정보를 보내준다.
			for (auto Item : MySessionManager.SessionList)
			{
				flatbuffers::FlatBufferBuilder LoginSendBuilder;

				UserPacket::FVector2D Position(Item.X, Item.Y);
				UserPacket::FColor Color(Item.R, Item.G, Item.B);
				auto SpawnData = UserPacket::CreateS2C_Spawn(
					LoginSendBuilder,
					(uint16_t)Item.ClientSocket,
					&Position,
					&Color,
					Item.Shape
				);

				auto UserSpawnPacketData = UserPacket::CreatePacketData(
					LoginSendBuilder,
					UserPacket::PacketType_S2C_Spawn,
					SpawnData.Union()
				);

				LoginSendBuilder.Finish(UserSpawnPacketData);

				for (auto Receiver : MySessionManager.SessionList)
				{
					int SentBytes = SendAll(Receiver.ClientSocket, LoginSendBuilder);
					if (SentBytes <= 0)
					{
						std::cout << "header send fail." << endl;
					}
				}
			}
		}
		else
		{
			std::cout << "로그인에 실패했습니다." << std::endl;

			auto S2C_Login_Fail_Data = UserPacket::CreateS2C_Login(
				SendBuilder,
				(uint16_t)ProcessSocket,
				SendBuilder.CreateString("Failed."),
				SendBuilder.CreateString(""),
				false
			);

			auto FailPacket = UserPacket::CreatePacketData(
				SendBuilder,
				UserPacket::PacketType_S2C_Login,
				S2C_Login_Fail_Data.Union()
			);

			SendBuilder.Finish(FailPacket);
			SendAll(ProcessSocket, SendBuilder);
		}
	}
	break;

	case UserPacket::PacketType_C2S_Move:
	{
		flatbuffers::FlatBufferBuilder SendBuilder;

		auto MovePacket = UserPacketData->data_as_C2S_Move();
		Session* FindSession = MySessionManager.GetSession(ProcessSocket); //(SOCKET)MovePacket->client_socket_id()
		switch (MovePacket->direction())
		{
		case 'W':
		case 'w':
			FindSession->Y-=5;
			break;
		case 'S':
		case 's':
			FindSession->Y+=5;
			break;
		case 'A':
		case 'a':
			FindSession->X-=5;
			break;
		case 'D':
		case 'd':
			FindSession->X+=5;
			break;
		}

		UserPacket::FVector2D Position(FindSession->X, FindSession->Y);
		auto S2C_MoveData = UserPacket::CreateS2C_Move(
			SendBuilder,
			(uint16_t)FindSession->ClientSocket,
			&Position
		);

		//std::cout << FindSession->ClientSocket << std::endl;

		auto MoveData = UserPacket::CreatePacketData(
			SendBuilder,
			UserPacket::PacketType_S2C_Move,
			S2C_MoveData.Union()
		);

		SendBuilder.Finish(MoveData);

		//모든 유저한테 이동 패킷 보내줌
		for (auto Receiver : MySessionManager.SessionList)
		{
			int SentBytes = SendAll(Receiver.ClientSocket, SendBuilder);
			if (SentBytes <= 0)
			{
				std::cout << "move send fail." << endl;
			}
		}
	}
	break;
	case UserPacket::PacketType_C2S_ChangeColor:
	{
		flatbuffers::FlatBufferBuilder SendBuilder;

		auto ChangeColorPacket = UserPacketData->data_as_C2S_ChangeColor();
		Session* ChangeSession = MySessionManager.GetSession(ProcessSocket); //(SOCKET)ChangeColorPacket->client_socket_id()

		if (ChangeSession)
		{
			ChangeSession->R = rand() % 256;
			ChangeSession->G = rand() % 256;
			ChangeSession->B = rand() % 256;

			UserPacket::FColor NewColor(ChangeSession->R, ChangeSession->G, ChangeSession->B);

			auto S2C_ColorData = UserPacket::CreateS2C_ChangeColor(
				SendBuilder,
				ChangeColorPacket->client_socket_id(),
				&NewColor
			);

			auto UserPacketData = UserPacket::CreatePacketData(
				SendBuilder,
				UserPacket::PacketType_S2C_ChangeColor,
				S2C_ColorData.Union()
			);

			SendBuilder.Finish(UserPacketData);

			// 변경된 색상 정보 모든 클라이언트에게 멀티캐스트
			for (auto Receiver : MySessionManager.SessionList)
			{
				int SentBytes = SendAll(Receiver.ClientSocket, SendBuilder);
				if (SentBytes <= 0)
				{
					std::cout << "color change send fail." << endl;
				}
			}
		}
	}
	break;
	case UserPacket::PacketType_C2S_Signup:
	{
		auto SignupPacket = UserPacketData->data_as_C2S_Signup();

		bool Result = Signup(SignupPacket->user_id()->c_str(),
			SignupPacket->user_pw()->c_str(),
			SignupPacket->name()->c_str()
		);

		flatbuffers::FlatBufferBuilder SendBuilder;

		auto S2C_ColorData = UserPacket::CreateS2C_Signup(
			SendBuilder,
			SendBuilder.CreateString(Result ? "가입 성공했습니다." : "가입에 실패 했습니다."),
			Result
		);

		auto UserPacketData = UserPacket::CreatePacketData(
			SendBuilder,
			UserPacket::PacketType_S2C_Signup,
			S2C_ColorData.Union()
		);

		SendBuilder.Finish(UserPacketData);
		SendAll(ProcessSocket, SendBuilder);
	}
	break;
	}
}

//blocking, synchrous, multiplexing(polling)
int main()
{
	srand((unsigned int)time(nullptr));

	//if (!MyDBManager.Connect())
	//{
	//	std::cout << "DBManager의 MySQL 서버 연결 실패" << std::endl;
	//	return -1;
	//}

	cout << "server start" << endl;

	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY;
	ListenSockAddr.sin_port = htons(35000);

	//already use port 이미 포트 사용중
	::bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));

	listen(ListenSocket, SOMAXCONN);

	ConnectDB();

	//blocking, synchronous(TimeOut)
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
			//Server Work
			//0.5초 한 번 서버 작업을 함.
			continue;
		}

		//뭔가 자료가 있다면
		for (int i = 0; i < (int)ReadSockets.fd_count; ++i)
		{
			if (FD_ISSET(ReadSockets.fd_array[i], &CopyReadSockets))
			{
				if (ReadSockets.fd_array[i] == ListenSocket)
				{
					//connect process
					SOCKADDR_IN ClientSockAddr;
					memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
					int ClientSockSockLength = sizeof(ClientSockAddr);

					//blocking, synchronous
					SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockSockLength);

					cout << "connect client " << inet_ntoa(ClientSockAddr.sin_addr) << endl;

					FD_SET(ClientSocket, &ReadSockets);
				}
				else
				{
					//Data Receive
					int RecvBytes = RecvAll(ReadSockets.fd_array[i], Buffer);
					if (RecvBytes <= 0)
					{
						cout << "data recv fail " << endl;
						DisconnectSocket(ReadSockets.fd_array[i], &ReadSockets);
						continue;
					}
					else
					{
						ProcessPacket(ReadSockets.fd_array[i], Buffer);
					}
				}
			}
		}
	}


	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}