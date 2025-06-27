#pragma once
#include <vector>
#include "Entity.h"
#include "Enemy.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"



class Projectile : public Entity
{
public:
	//Structs::Scene* GameScene = nullptr;

	sf::Texture& SpriteTexture = ContentManager::GetInstance()->TXTRocket01;
	sf::Sprite Sprite = HelperFunctions::ConstructSprite(SpriteTexture);

	sf::Vector2f StartPosition;
	sf::Vector2f DestinationPosition;
	sf::Vector2f ProjectileDirection;

	float ProjectileSizeX = 80.f;
	float ProjectileSizeY = 60.f;
	float ProjectileCollisionX = 15.f;
	float ProjectileCollisionY = 15.f;
	float ProjectileCollisionYOffset = 10.f;
	float ProjectileSpeed = 13.f;
	float EntityLifeTime = 5.;

	void SetEnemiesInScene(std::vector<Enemy*> InEnemyList);
	void UpdateEntity() override;

	// Constructor
	Projectile(const sf::Vector2f& Start, const sf::Vector2f& End);
	~Projectile() {};


private:
	// Pointer to enemies array
	void UpdateProjectile();
	void SetSpriteRotation();
	void ConstructProjectile();
	std::vector<Enemy*> pEnemies;
};

