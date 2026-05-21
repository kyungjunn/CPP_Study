#pragma once
#include "Packet.h"
class PlayerDirectionPacket : public IPacket
{
public:
	std::string UserID;
	std::string Direction;

	// Inherited via IPacket
	void Parse(std::string InString) override;
	std::string ToString() override;
	int Length() override;
};

