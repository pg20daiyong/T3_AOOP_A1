#include "SquareWithinSquareRenderingComponent.h"
#include "TransformComponent.h"
#include "ActorImpl.h"
#include "Game.h"


SquareWithinSquareRenderingComponent::SquareWithinSquareRenderingComponent(int actorID)
	:ComponentBase(actorID)
{}


void SquareWithinSquareRenderingComponent::Render()
{
    auto engine = Game::GetInstance()->GetEngine();
    auto transform = GetOwner()->GetComponent<TransformComponent>(ComponentType::Transform);
    auto bounds = transform->GetBounds();

    auto size = exVector2(40, 40);
    auto mHalfSize = exVector2(size.x / 2.0f, size.y / 2.0f);
    SetColor(exColor(77, 38, 0));

    engine->DrawLineBox(bounds.min, bounds.max, GetColor(), 0);

    auto coreBounds = bounds;
    coreBounds.min.x += mHalfSize.x / 2.0f;
    coreBounds.min.y += mHalfSize.y / 2.0f;

    coreBounds.max.x -= mHalfSize.x / 2.0f;
    coreBounds.max.y -= mHalfSize.y / 2.0f;

    engine->DrawBox(coreBounds.min, coreBounds.max, GetColor(), 0);
}
