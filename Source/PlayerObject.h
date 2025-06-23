#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Entity.h"

class PlayerObject : public Entity
{
public:
	sf::Texture& SpriteTexture = ContentManager::GetInstance()->DefaultTexture;
	sf::Sprite Sprite = HelperFunctions::ConstructSprite(SpriteTexture);
	sf::Vector2f PlayerSize = sf::Vector2f({40.f, 40.f});
	float MovementSpeed = 5.;
	sf::Vector2f MousePosition;

	void InitVariables();
	void ForceSetPosition(const sf::Vector2f& Position);
	void SetSpriteRotation();
	void UpdateEntity() override;

	// Constructor Destructor
	PlayerObject(const sf::Vector2f& Position);
	~PlayerObject();
private:
	void ConstructPlayer();
	sf::Vector2f PlayerDirection;
};

