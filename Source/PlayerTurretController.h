#pragma once
#include "HelperFunctions.h"
#include "TurretObject.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "GameDataManager.h"


class PlayerTurretController
{
private:
	bool bMousePressed;
	sf::Vector2f MovementDirection;
	// Get instance of exchange manager
	GameDataManager* GameDataManager = GameDataManager::GetInstance();

public:
	bool ReceiveInput;
	// Contructor Destructor
	PlayerTurretController();
	~PlayerTurretController() {};

	sf::Angle HalfPI = sf::Angle(sf::radians(1.570785f));
	sf::Vector2f MousePosition;
	sf::Vector2f CurrentPosition;
	sf::Vector2f PlayerDirection;

	sf::Angle TurretAngle;
	sf::Angle PlayerAngle;

	TurretObject* PlayerTurret = nullptr;

	float ForwardMovementSpeed = 100.f;
	float PlayerRotationSpeed = 2.f;
	float BackwardsMovementScalar = 0.5f;
	float DeltaTime = 0.f;

	void UpdatePlayerController();
	void TrackInput();
	void InitVariables();
	sf::Angle SetTurretAngles();
};

