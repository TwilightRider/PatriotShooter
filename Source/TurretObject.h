#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Entity.h"


class TurretObject : public Entity
{
public:
	bool Movable = false;
	bool PosessedByPlayer = false;

	// Turret
	sf::Texture& TurretTexture = ContentManager::GetInstance()->DefaultTexture;
	sf::Sprite TurretSprite = HelperFunctions::ConstructSprite(TurretTexture);

	// Base
	sf::Texture& BaseTexture = ContentManager::GetInstance()->DefaultTexture;
	sf::Sprite BaseSprite = HelperFunctions::ConstructSprite(BaseTexture);

	sf::Vector2f PlayerSize = sf::Vector2f({40.f, 40.f});

	float MovementSpeed = 5.;
	// Normalized vector
	sf::Vector2f MovementDiretion;


	sf::Vector2f MousePosition;

	sf::Angle BaseAngle;
	sf::Angle TurretAngle;

	void InitVariables();
	void ForceSetPosition(const sf::Vector2f& Position);
	void SetSpriteRotation(sf::Sprite& InSprite, const sf::Angle& Angle);
	void UpdateEntity() override;
	void MoveTurret();

	// Constructor Destructorb
	TurretObject(const sf::Vector2f& Position);
	~TurretObject();

private:
	void ConstructTurret();
};

