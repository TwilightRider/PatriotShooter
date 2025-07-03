#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Color.hpp"
#include "ContentManager.h" 
#include "HelperFunctions.h"
#include "EntityManager.h"
#include "GameDataManager.h"
#include "EntityInterface.h"

class Scene;

class Entity : public IEntity
{
public:
	// Forward decalration
	//Scene* GameScene = nullptr;
	// Constructor Destructor
	Entity();
	virtual ~Entity();

	sf::Vector2f WorldBounds;
	float DeltaTime = 0.f;
	float DeltaTimer = 0.f;
	float Timer = 0.f;
	float EntityLifeTime = 0;
	float EntityMaxLifeTime = 0;

	bool bEntityHit = false;
	bool bDrawDebugCollision = false;

	void PrintClassName(const std::string& Text);
	

	const sf::RectangleShape* GetCollisionShape();
	const sf::Vector2f GetPosition();
	void UpdateEntity() override;

protected:
	GameDataManager* GameDataManager = GameDataManager::GetInstance();
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

	bool KillOutsideOfWindow();
	virtual void ConstructCollision(bool bRecenter);
	
};

