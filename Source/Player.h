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
	int PlayerLevel = 1;
	int PlayerPoints = 0;

	unsigned Health;
	unsigned HealthDecrementRate = 100;

	PlayerTurretController* PlayerController = nullptr;
	TurretObject* PlayerTurret = nullptr;

	// Constructor destructor
	Player();

	~Player();

	void InitVariables();

	void UpdateEntity() override;
	void NotifySceneWasChanged() override;
	void SendObjectToScene() override;
};