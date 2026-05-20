#pragma once
#include "Packet.h"

class PlayerPacket : public IPacket
{
	std::string UserID;
	int TransformX;
	int TransformY;

	// Inherited via IPacket
	void Parse(std::string InString) override;
	std::string ToString() override;
	int Length() override;
};

