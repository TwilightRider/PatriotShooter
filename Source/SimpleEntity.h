#pragma once
#include "EntityInterface.h"
#include "GameDataManager.h"

class ESimpleEntity : public IEntity
{
protected:
	sf::Vector2f WorldBounds;
	float DeltaTime = 0.f;
	float DeltaTimer = 0.f;
	float Timer = 0.f;

	GameDataManager* GameDataManager = GameDataManager::GetInstance();

public:
};

