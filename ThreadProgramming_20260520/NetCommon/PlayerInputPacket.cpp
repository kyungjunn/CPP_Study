#include "pch.h"
#include "PlayerInputPacket.h"

void PlayerInputPacket::Parse(std::string InString)
{
    JSONDocument.Parse(InString.c_str());

    UserID = JSONDocument["UserID"].GetString();
    InputKey = JSONDocument["InputKey"].GetInt();
}   

std::string PlayerInputPacket::ToString()
{
    JSONDocument.SetObject();
    JSONDocument.AddMember("UserID", UserID, JSONDocument.GetAllocator());
    JSONDocument.AddMember("InputKey", InputKey, JSONDocument.GetAllocator());

    rapidjson::StringBuffer Buffer;
    rapidjson::Writer<rapidjson::StringBuffer> Writer(Buffer);
    JSONDocument.Accept(Writer);

    return Buffer.GetString();
}

int PlayerInputPacket::Length()
{
    return (int)ToString().length();
}
