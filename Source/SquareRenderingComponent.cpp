#include "SquareRenderingComponent.h"
#include "TransformComponent.h"
#include "ActorImpl.h"
#include "Game.h"

SquareRenderingComponent::SquareRenderingComponent(int actorID)
	:ComponentBase(actorID)
{}


void SquareRenderingComponent::Render()
{
	auto transform = GetOwner()->GetComponent<TransformComponent>(ComponentType::Transform);
    auto bounds = transform->GetBounds();

    auto engine = Game::GetInstance()->GetEngine();
    SetColor(exColor(66, 33, 0));
    engine->DrawBox(bounds.min, bounds.max, GetColor(), 0);
}
