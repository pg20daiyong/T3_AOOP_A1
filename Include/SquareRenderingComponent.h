#pragma once
#include "ComponentBase.h"
#include "EngineInterface.h"
#include "EngineTypes.h"
#include "Game.h"
#include "Actor.h"

class SquareRenderingComponent : public ComponentBase
{
public:
	SquareRenderingComponent(int actorID);

	ComponentType GetType() override { return ComponentType::SquareRendering; }
	
	exColor	 GetColor() const { return mColor; }
	void SetColor(exColor color) { mColor = color; }

	//void Render(Actor* actor);
	void Render();

private:
	
	exColor mColor;
	

};
