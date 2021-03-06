#include "ColliderComponent.h"
#include "World.h"
#include "Events.h"
#include "EventSystem.h"

bool ColliderComponent::sCollisionLayer[CollisionTag::COUNT][CollisionTag::COUNT] =
{
    // NONE, SHIP, BULLET, ASTEROID
    { false, false, false, false }, // NONE
    { false, false, false, true}, // SHIP
    { false, false, false, true}, // BULLET
    { false, true,  true , false} // ASTEROID
};

ColliderComponent::ColliderComponent(int actorID)
    : ComponentBase(actorID)
{}

void ColliderComponent::Update(float deltaTime) 
{
    if (!GetOwner()->IsActive())
    {
        return;
    }

    auto actors = WORLD->GetActors();

    mCollisions.clear();
    for (Actor* other : actors)
    {
        if (GetOwner() == other)
        {
            continue;
        }

        auto otherCollider = other->GetComponent<ColliderComponent>(ComponentType::Collider);
        if (other->IsActive() && otherCollider != nullptr)
        {
            if (CheckCollision(otherCollider))
            {
                CollisionEventArgs evt = { this, otherCollider->GetTag() };
                mCollisions.push_back(evt);
            }
        }
    }
}

void ColliderComponent::PostUpdate()
{
    for (auto& collision : mCollisions)
    {
        EventSystem::GetInstance()->Trigger(EventTypes::Collision, collision);
    }
    mCollisions.clear();
}

bool ColliderComponent::CheckCollision(const ColliderComponent* other)
{
    if (other == nullptr)
    {
        return false;
    }

    return (sCollisionLayer[GetTag()][other->GetTag()] && mBounds.collides(other->GetBounds()));
}