#pragma once

#include "Actor.h"

template <typename T>

T* Actor::GetComponent(ComponentType type) const
{
	for (auto* c : mComponent)
	{
		if (c->GetType() == type)
		{
			return static_cast<T*>(c);
		}
	}
	return nullptr;
}