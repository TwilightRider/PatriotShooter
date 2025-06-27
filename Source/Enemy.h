#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Entity.h"
#include "Structs.h"
#include "HelperFunctions.h"

class Enemy : public Entity
{
private:
	void ConstructEnemy();

	sf::Sprite EnemySprite = HelperFunctions::ConstructSprite(DefaultTexture);
	gamestructs::EnemyPreset* CurrentPreset = nullptr;

	void InitVariables();
	sf::Vector2f Size;
	sf::Color Color;
	
	void UpdateEnemy();
	void UpdatePosition();
	
public:
	// Properties
	int EnemyId = 0;
	sf::Vector2f CurrentPosition;
	Enums::EnemyClass EnemyLevel;
	unsigned int KillReward;
	float DownMovementSpeed;
	void ForceSetPosition(const sf::Vector2f& Position);
	void UpdateEntity() override;
	const sf::Sprite& GetEnemySprite();
	sf::Vector2f GetSize();

	Enemy(Enums::EnemyClass EnemyLevel);
	
};

