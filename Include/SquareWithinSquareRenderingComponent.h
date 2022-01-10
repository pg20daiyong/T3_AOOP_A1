#pragma once
#include "ComponentBase.h"
#include "ActorFactory.h"
#include "EngineInterface.h"
#include "EngineTypes.h"
#include "Game.h"
#include "Bounds.h"
#include "Actor.h"

class SquareWithinSquareRenderingComponent : public ComponentBase
{
public:
	SquareWithinSquareRenderingComponent(int actorID);

	ComponentType GetType() override { return ComponentType::SquareWithinSquareRendering; }

	exColor   GetColor() const { return mColor; }

	void SetColor(exColor color) { mColor = color; }
	//void Render(Actor* actor);
	void Render();
private:
	
	exColor mColor;

};
