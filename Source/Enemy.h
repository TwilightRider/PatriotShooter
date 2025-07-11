#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Entity.h"
#include "Structs.h"
#include "HelperFunctions.h"


class Player;
class Enemy : public Entity
{
private:
	sf::Sprite EnemySprite = HelperFunctions::ConstructSprite(DefaultTexture);
	gamestructs::EnemyPreset* CurrentPreset = nullptr;

	sf::Vector2f Size;
	sf::Color Color;

	void InitVariables();
	void UpdatePosition();
	
public:
	Player* MainPlayer = nullptr;
	unsigned HealtDecrementOutBounds = 100;
	// Properties
	int EnemyId = 0;
	sf::Vector2f CurrentPosition;
	Enums::EnemyClass EnemyLevel;
	unsigned int KillReward;
	float DownMovementSpeed;
	void ForceSetPosition(const sf::Vector2f& Position);
	void ConstructEnemy();
	const sf::Sprite& GetEnemySprite();
	const sf::Vector2f GetSize() const;
	void UpdateEntity() override;
	void TrackEnemyOutBounds();

	void NotifySceneWasChanged() override;
	void SendObjectToScene() override;

	Enemy(Enums::EnemyClass EnemyLevel);
};

