#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Color.hpp"
#include "ContentManager.h" 
#include "HelperFunctions.h"


class Entity
{
protected:
	
	sf::RectangleShape* CollisionRectangle = nullptr;
	sf::Shape* CollisionShape = nullptr;
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
	Entity();
	~Entity();
	
	sf::Vector2f WorldSize;
	float DeltaTime = 0.f;
	float DeltaTimer = 0.f;
	float Timer = 0.f;
	float EntityLifeTime = 0;
	float EntityMaxLifeTime = 0;
	bool bDrawDebugCollision = false;
	bool GetEntityIsNeedToDestroy();

	virtual void UpdateEntity();
	void PrintClassName(const std::string& Text);
	void CallEntityDestruction();
	sf::RectangleShape* GetCollision();
	sf::Vector2f GetPosition();
	std::string GetClassName();

private:
	sf::Vector2f CollisionSize;
	bool bDestroyEntity = false;
	std::string ClassName = "";
};

