#include "TextRenderActor.h"
#include "TextRenderComponent.h"

ATextRenderActor::ATextRenderActor()
{
	// CreateDefaultSubobject 얘가  Owner 호출하고 컴포넌트에 넣어줄거임.
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
}
ATextRenderActor::~ATextRenderActor()
{
}
