#pragma once

class UAD;
class UAP;
class UTank;
 
class UCharacteristic
{
public:
	UCharacteristic();
	~UCharacteristic();

	UAD* ADs;
	UAP* APs;
	UTank* Tanks;
};

