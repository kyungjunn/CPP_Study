#include "pch.h"
#include "PlayerDirectionPacket.h"

void PlayerDirectionPacket::Parse(std::string InString)
{
    JSONDocument.Parse(InString.c_str());

    UserID = JSONDocument["UserID"].GetString();
    Direction = JSONDocument["Direction"].GetString();
}

std::string PlayerDirectionPacket::ToString()
{
    JSONDocument.SetObject();

    JSONDocument.AddMember("UserID", UserID, JSONDocument.GetAllocator());
    JSONDocument.AddMember("Direction", Direction, JSONDocument.GetAllocator());

    rapidjson::StringBuffer Buffer;
    rapidjson::Writer<rapidjson::StringBuffer> Writer(Buffer);
    JSONDocument.Accept(Writer);

    return Buffer.GetString();
}

int PlayerDirectionPacket::Length()
{
    return (int)ToString().length();
}
