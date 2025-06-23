#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Color.hpp"
#include <iostream>

class Entity
{
protected:
	sf::RectangleShape* CollisionRectangle = nullptr;
	sf::Vector2f Position;
	sf::Color CollisionColor = { 255, 0, 0, 120 };

	float UpdateRate = 0.5;
	bool bIsDynamic = false;
	bool bHasCollision = false;
	bool bUseScreenKillZone = false;
	
	bool KillOutsideOfWindow();
	virtual void ConstructCollision(float SizeX, float SizeY, bool bRecenter);
public:

	// Constructor Destructor
	Entity() {};
	~Entity();
	
	sf::Vector2f WorldSize;

	float EntityLifeTime = 0;
	float EntityMaxLifeTime = 0;

	bool DrawDebugCollision = true;
	virtual void UpdateEntity();
	void PrintClassName(const std::string& Text);
	void CallEntityDestruction();
	bool GetEntityIsNeedToDestroy();
	sf::RectangleShape* GetCollision();
	
private:
	sf::Vector2f CollisionSize;
	bool bDestroyEntity = false;
	
};

