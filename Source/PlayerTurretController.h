#pragma once
#include <functional>
#include "HelperFunctions.h"
#include "TurretObject.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "Projectile.h"
#include "Scene.h"
#include "GameDataManager.h"


class PlayerTurretController
{
private:
	std::function<void()> CallBackProjectile;

	bool bMousePressed;
	sf::Vector2f MovementDirection;
	// Get instance of exchange manager
	GameDataManager* GameDataManager = GameDataManager::GetInstance();
public:
	// Contructor Destructor
	PlayerTurretController();
	~PlayerTurretController() {};

	sf::Angle HalfPI = sf::Angle(sf::radians(1.570785f));
	sf::Vector2f MousePosition;
	sf::Vector2f CurrentPosition;
	sf::Vector2f PlayerDirection = sf::Vector2f ({0.f, 1.f });

	sf::Angle TurretAngle = sf::Angle(sf::radians(0));
	sf::Angle PlayerAngle = sf::Angle(sf::radians(0));
	sf::Vector2f WorldBounds;

	Scene* GameScene = nullptr;
	TurretObject* PlayerEntity = nullptr;

	float ForwardMovementSpeed = 60.f;
	float PlayerRotationSpeed = 2.f;
	float BackwardsMovementScalar = 0.5f;
	float DeltaTime = 0.f;

	void AssignToProjectileSpawn(std::function<void()> func);
	void UpdatePlayerController();
	void TrackInput();
	void FireProjectile();
	void InitVariables();
	sf::Angle SetTurretAngles();
};

