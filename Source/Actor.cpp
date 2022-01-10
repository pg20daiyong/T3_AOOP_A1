#include "Actor.h"
#include "ActorImpl.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "SquareRenderingComponent.h"
#include "SquareWithinSquareRenderingComponent.h"
#include "Game.h"

Actor::Actor(int id, bool isActive)
    : mID(id)
    , mIsActive(isActive)
{
    AddComponent(new TransformComponent(id));
    //AddComponent(new SquareRenderingComponent(id));
    //AddComponent(new SquareWithinSquareRenderingComponent(id));

}

//void Actor::Render()
//{    
//    auto transform = GetComponent<TransformComponent>(ComponentType::Transform);
//    auto bounds = transform->GetBounds();
//
//    auto engine = Game::GetInstance()->GetEngine();
//    engine->DrawBox(bounds.min, bounds.max, mColor, 0);
//}

void Actor::AddComponent(ComponentBase* component)
{
    mComponent.push_back(component);
}

void Actor::RemoveComponent(ComponentType type)
{
    for (auto it = mComponent.begin(); it != mComponent.end(); it++)
    {
        if ((*it)->GetType() == type)
        {
            mComponent.erase(it);
            return;
        }
    }
}

bool Actor::IsActive() const 
{
    return mIsActive; 
}

void Actor::SetActive(bool active) 
{ 
    mIsActive = active; 
}