#pragma once
#include "PlayerTurretController.h"
#include "TurretObject.h"
#include "Structs.h"
#include "EntityInterface.h"


class Player : public IEntity
{
private:
	//bool FireProjectile;
	// Get instance of exchange manager
	GameDataManager* GameDataManager = GameDataManager::GetInstance();
	void UpdatePlayerController();

public:
	unsigned PlayerLevel;
	unsigned PlayerPoints;

	unsigned Health;
	unsigned HealthDecrementRate = 100;

	PlayerTurretController* PlayerController = nullptr;
	TurretObject* PlayerTurret;

	// Constructor destructor
	Player();

	~Player();

	void InitVariables();

	void UpdateEntity() override;
	void NotifySceneWasChanged() override;
	void SendObjectToScene() override;
};