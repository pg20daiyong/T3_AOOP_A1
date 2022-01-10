#include "ComponentBase.h"
#include "Actor.h"
#include "World.h"

ComponentBase::ComponentBase(int actorID) :
	mActorID(actorID)
{}

Actor* ComponentBase::GetOwner() const
{
	return WORLD->GetActor(mActorID);
}