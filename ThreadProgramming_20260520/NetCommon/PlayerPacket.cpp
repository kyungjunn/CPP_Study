#include "pch.h"
#include "PlayerPacket.h"

void PlayerPacket::Parse(std::string InString)
{
    JSONDocument.Parse(InString.c_str());

    UserID = JSONDocument["UserID"].GetString();
    TransformX = JSONDocument["TransformX"].GetInt();
    TransformY = JSONDocument["TransformY"].GetInt();

}

std::string PlayerPacket::ToString()
{
    return std::string();
}

int PlayerPacket::Length()
{
    return (int)ToString().length();
}
