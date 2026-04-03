#include "GameMode.h"
#include "GameplayStatics.h"

UGameplayStatics::UGameplayStatics()
{
}

UGameplayStatics::~UGameplayStatics()
{
}

AGameMode* UGameplayStatics::GetGameMode()
{
	AActor* Actor = GEngine->GetWorld()->GetActorOfClass<AGameMode>();
	return dynamic_cast<AGameMode*>(Actor);
}