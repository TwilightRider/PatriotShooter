#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Projectile.h"


class TurretObject : public Entity
{
public:
	// Turret
	sf::Texture& TurretTexture = ContentManager::GetInstance()->Tank_Turret_01;
	sf::Sprite TurretSprite = HelperFunctions::ConstructSprite(TurretTexture);
	sf::Vector2f TurretLocalOffset = sf::Vector2f({ 0.0f, 45.0f });

	// Base
	sf::Texture& BaseTexture = ContentManager::GetInstance()->Tank_Base_01;
	sf::Sprite BaseSprite = HelperFunctions::ConstructSprite(BaseTexture);
	sf::Vector2f BaseSize = sf::Vector2f({ 60.f, 110.f });
	sf::Vector2f TurretSize = sf::Vector2f({ 45.f, 45.f });

	bool Movable = false;
	bool PosessedByPlayer = false;

	// Movement
	float BaseRotationSpeed = 0.f;
	float MovementSpeed = 5.f;
	sf::Vector2f MovementDiretion; // Normalized vector

	sf::Angle BaseAngle;
	sf::Angle TurretAngle;

	void InitVariables();
	void ForceSetPosition(const sf::Vector2f& Position);
	
	void MoveTurretByBase();
	void FireProjectile();
	void ConstructTurret();

	void UpdateEntity() override;
	void SendObjectToScene() override;
	void NotifySceneWasChanged() override;

	// Constructor Destructorb
	TurretObject(const sf::Vector2f& Position, bool AddToScene);
	virtual ~TurretObject() {};

private:
	void MoveTurret();
};

