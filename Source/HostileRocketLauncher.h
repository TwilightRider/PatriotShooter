#pragma once
//#include "EntityInterface.h"
#include "Projectile.h"
#include "SimpleEntity.h"
#include "HelperFunctions.h"



class EHostileRocketLauncher : public ESimpleEntity
{
private:
	float RocketIntervals = 6.f;
	float RocketlaunchTimer = 0.f;
	float PlayerRadiud = 30.f; // smaller with level

	virtual void SendObjectToScene() override;
	void FireProjectile();
	void GetRandomPointOutsideWindow();

public:
	sf::Vector2f PlayerPosition;
	unsigned PlayerLevel;
	virtual void UpdateEntity() override;
	virtual void NotifySceneWasChanged() override;

};

