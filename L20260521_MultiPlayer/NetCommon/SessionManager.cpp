#include "pch.h"
#include "SessionManager.h"

void SessionManager::Add(Session InSession)
{
	SessionList.push_back(InSession);
}

void SessionManager::Delete(Session InSession)
{
	// find 가 Iterator을 반환해줄거임.
	SessionList.erase(std::find(SessionList.begin(), SessionList.end(), InSession));

	//for (auto Iter = SessionList.begin(); Iter != SessionList.end(); ++Iter)
	//{
	//	if ((*Iter).ClientSocket == InSession.ClientSocket)
	//	{
	//		SessionList.erase(Iter);
	//		break;
	//	}
	//}
}

Session* SessionManager::GetSession(int Index)
{
	// TODO: insert return statement here
	return &SessionList[Index];
}

Session* SessionManager::GetSession(const SOCKET& InClientSocket)
{
	// TODO: insert return statement here
	for (auto Iter = SessionList.begin(); Iter != SessionList.end(); ++Iter)
	{
		if ((*Iter).ClientSocket == InClientSocket)
		{
			return &(*Iter);
		}
	}

	return nullptr;
}

Session* SessionManager::GetSession(const Session InSession)
{
	return &(*std::find(SessionList.begin(), SessionList.end(), InSession));
}
