#pragma once
#include "Packet.h"

class PlayerPositionPacket : public IPacket
{
public:
	std::string UserID;
	int PositionX;
	int PositionY;
	char InputKey;

	// Inherited via IPacket
	void Parse(std::string InString) override;
	std::string ToString() override;
	int Length() override;
};

