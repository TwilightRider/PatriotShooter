#pragma once
#include "PlayerTurretController.h"
#include "TurretObject.h"
#include "Structs.h"
#include "Scene.h"
#include <functional>


class Player
{
private:
	bool FireProjectile;
	// Get instance of exchange manager
	GameDataManager* GameDataManager = GameDataManager::GetInstance();
	void UpdatePlayerController();

public:
	PlayerTurretController* PlayerController = nullptr;
	Scene* GameScene = nullptr;
	TurretObject* PlayerEntity = nullptr;

	// Constructor destructor
	Player();

	~Player();

	void InitVariables();

	void SetNewProperties();

	void UpdatePlayer();

	void SpawnProjectile();

	
};

