#pragma once
#include "Packet.h"
class PlayerInputPacket : public IPacket
{
public:
	std::string UserID;
	char InputKey;

	// Inherited via IPacket
	void Parse(std::string InString) override;
	std::string ToString() override;
	int Length() override;
};

