#pragma once

#include "Enums.h"

class Actor;

class ComponentBase
{
public:
	ComponentBase(int actorID);

	virtual void Initialize() {}
	virtual void Update(float deltaTime) {}
	virtual void PostUpdate() {}

	virtual ComponentType GetType() = 0;

	int GetActorID() const { return mActorID; }
	Actor* GetOwner() const;

protected:
	int mActorID;
};