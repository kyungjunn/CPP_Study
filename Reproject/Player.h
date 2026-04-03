#include "Actor.h"

class USpriteAnimationComponent;

class APlayer : public AActor
{
public:
	APlayer(int InX = 1, int InY = 1, char InMesh = 'P');
	virtual ~APlayer();

	virtual void BeginPlay() override;

	virtual void Tick() override;

	USpriteAnimationComponent* SpriteAnimationComponent;

protected:
	int SpriteIndexX = 0;
	int Direction = 0;

	float ElapsedTime = 0;
	float ExecutionTime = 0.1f;
};
