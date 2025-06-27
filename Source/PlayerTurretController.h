#pragma once
#include "HelperFunctions.h"
#include "TurretObject.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "Projectile.h"
#include "Scene.h"


class PlayerTurretController
{
private:
	bool bMousePressed;
	sf::Vector2f MovementDirection;
public:
	// Contructor Destructor
	PlayerTurretController();
	~PlayerTurretController() {};

	sf::Angle HalfPI = sf::Angle(sf::radians(1.570785f));
	sf::Vector2f MousePosition;
	sf::Vector2f CurrentPosition;
	sf::Vector2f PlayerDirection = sf::Vector2f ({0.f, 1.f });
	sf::Angle TurretAngle = sf::Angle(sf::radians(0));
	// In radians
	sf::Angle PlayerAngle = sf::Angle(sf::radians(0));
	sf::Vector2f WorldBounds;

	Scene* GameScene = nullptr;
	TurretObject* PlayerEntity = nullptr;

	float ForwardMovementSpeed = 50.f;
	float PlayerRotationSpeed = 2.f;
	float BackwardsMovementScalar = 0.5f;
	float DeltaTime = 0.f;
	void UpdateMovement();
	void TrackInput();
	void FireProjectile();
	void InitVariables();
	sf::Angle SetTurretAngles();
};

