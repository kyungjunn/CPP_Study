#include "Character.h"
#include "Engine.h"
#include "World.h"
#include "CollisionComponent.h"

ACharacter::ACharacter()
{
}

ACharacter::~ACharacter()
{
}
bool ACharacter::PredictMove(int InX, int InY)
{
	for (auto Other : GEngine->GetWorld()->GetActors())
	{
		if (Other == this) // 자기 자신은 비교 X
		{
			continue;
		}
		for (auto OtherComponent : Other->Components)
		{
			UCollisionComponent* OtherCollision = dynamic_cast<UCollisionComponent*>(OtherComponent);
			if (OtherCollision)
			{
				if (OtherCollision->bIsGenerateHit && InX == Other->GetX()
					&& InY == Other->GetY())
				{
					// 겹쳤을 때
					ReceiveHit(Other);
					return false;
				}
				//if (OtherCollision->bIsGenerateOverlap && InX == Other->GetX()
				//	&& InY == Other->GetY())
				//{
				//	// Overlap
				//	OnActorBeginOverlap(Other);
				//	return false;
				//}
			}
		}
	}
	return true;
}
