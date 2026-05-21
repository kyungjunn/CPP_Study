#include "pch.h"
#include "PlayerPositionPacket.h"

void PlayerPositionPacket::Parse(std::string InString)
{
    JSONDocument.Parse(InString.c_str());

    UserID = JSONDocument["UserID"].GetString();
    PositionX = JSONDocument["PositionX"].GetInt();
    PositionY = JSONDocument["PositionY"].GetInt();
    InputKey = JSONDocument["InputKey"].GetInt();
}

std::string PlayerPositionPacket::ToString()
{
    JSONDocument.SetObject();
    JSONDocument.AddMember("UserID", UserID, JSONDocument.GetAllocator());
    JSONDocument.AddMember("PositionX", PositionX, JSONDocument.GetAllocator());
    JSONDocument.AddMember("PositionY", PositionY, JSONDocument.GetAllocator());
    JSONDocument.AddMember("InputKey", InputKey, JSONDocument.GetAllocator());

    rapidjson::StringBuffer Buffer;
    rapidjson::Writer<rapidjson::StringBuffer> Writer(Buffer);
    JSONDocument.Accept(Writer);

    return Buffer.GetString();
}

int PlayerPositionPacket::Length()
{
    return (int)ToString().length();
}
