#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Entity.h"

class Enemy : public Entity
{
private:
	void ConstructEnemy();
	
	void InitVariables();
	sf::Vector2f Size;
	sf::Color Color;
	void UpdateEnemy();
	void UpdatePosition();
	

public:
	// Properties
	int EnemyId = 0;
	sf::RectangleShape EnemyShape;
	sf::Vector2f CurrentPosition;
	Enums::EnemyClass EnemyLevel;
	unsigned int KillReward;
	float DownMovementSpeed;
	bool bHit;
	void ForceSetPosition(const sf::Vector2f& Position);
	void UpdateEntity() override;

	Enemy();
	
};

