#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Entity.h"
#include "Projectile.h"


class TurretObject : public Entity
{
public:
	bool Movable = false;
	bool PosessedByPlayer = false;

	// Turret
	sf::Texture& TurretTexture = ContentManager::GetInstance()->Tank_Turret_01;
	sf::Sprite TurretSprite = HelperFunctions::ConstructSprite(TurretTexture);
	sf::Vector2f TurretLocalOffset = sf::Vector2f({ 0.0f, 45.0f });

	// Base
	sf::Texture& BaseTexture = ContentManager::GetInstance()->Tank_Base_01;
	sf::Sprite BaseSprite = HelperFunctions::ConstructSprite(BaseTexture);
	sf::Vector2f BaseSize = sf::Vector2f({60.f, 110.f});
	sf::Vector2f TurretSize = sf::Vector2f({ 45.f, 45.f });

	// Movement
	float BaseRotationSpeed = 0.f;
	float MovementSpeed = 5.f;
	sf::Vector2f MovementDiretion; // Normalized vector

	sf::Angle BaseAngle;
	sf::Angle TurretAngle;

	void InitVariables();
	void ForceSetPosition(const sf::Vector2f& Position);
	void UpdateEntity() override;
	void MoveTurretByBase();
	void FireProjectile();
	Projectile* CurrentProjectile;
	
	// Constructor Destructorb
	TurretObject(const sf::Vector2f& Position);
	~TurretObject();

private:
	void ConstructTurret();
	void MoveTurret();
};

