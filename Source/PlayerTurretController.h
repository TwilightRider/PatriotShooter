#pragma once
#include "HelperFunctions.h"
#include "TurretObject.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "Projectile.h"
#include "Structs.h"


class PlayerTurretController
{
private:
	bool bMousePressed;
	sf::Vector2f MovementDirection;
public:
	// Contructor Destructor
	PlayerTurretController();
	~PlayerTurretController() {};

	sf::Vector2f MousePosition;
	sf::Vector2f CurrentPosition;
	sf::Angle TurretAngle = sf::Angle(sf::degrees(0));
	sf::Vector2f WorldBounds;

	Structs::Scene* GameScene = nullptr;
	TurretObject* PlayerEntity = nullptr;

	float DeltaTime = 0.f;
	void UpdateMovement();
	void TrackInput();
	void FireProjectile();
	void InitVariables();
	sf::Angle SetTurretAngles();
};

