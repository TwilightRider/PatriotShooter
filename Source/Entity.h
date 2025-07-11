#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Color.hpp"
#include "ContentManager.h" 
#include "HelperFunctions.h"
#include "EntityManager.h"
#include "SimpleEntity.h"

class Scene;

class Entity : public ESimpleEntity
{
public:
	// Forward decalration
	//Scene* GameScene = nullptr;
	// Constructor Destructor
	Entity();
	virtual ~Entity();

	float EntityLifeTime = 0.f;
	float EntityMaxLifeTime = 0.f;

	bool bEntityHit = false;
	bool bDrawDebugCollision = false;

	void PrintClassName(const std::string& Text);
	
	const sf::RectangleShape* GetCollisionShape();
	const sf::Vector2f GetPosition() const;
	void UpdateEntity() override;

protected:
	EntityManager* EntityManager = EntityManager::GetInstance();
	ContentManager* ContentManager = ContentManager::GetInstance();
	sf::Texture& DefaultTexture = ContentManager->DefaultTexture;

	sf::RectangleShape* CollisionRectangle = nullptr;
	sf::Shape* CollisionShape = nullptr;
	sf::Vector2f Position;
	sf::Color CollisionColor = { 255, 0, 0, 120 };
	sf::Vector2f CollisionSize;
	sf::Vector2f CollisionLocalOffset;

	float UpdateRate = 0.5;
	bool bIsDynamic = false;
	bool bHasCollision = false;
	bool bUseScreenKillZone = false;

	bool KillOutsideOfWindow() const;
	virtual void ConstructCollision(bool bRecenter);
	
};

