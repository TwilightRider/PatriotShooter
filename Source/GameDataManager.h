#pragma once
#include "SFML/System/Vector2.hpp"
#include "EntityInterface.h"
#include <vector>
#include <string>


// Scene forward declaration
class Scene;
class GameDataManager
{
public:
	float DeltaTime = 0.f;
	sf::Vector2f WorldBounds; // bigger than window
	sf::Vector2f WindowSize;
	sf::Vector2f MousePositionView;
	sf::Vector2f PlayerStartPosition;

	Scene* GameScene = nullptr;
	IEntity* SpawnedEntity = nullptr;

	static GameDataManager* GameDataExchangePtr;
	static GameDataManager* GetInstance()
	{
		//std::cout << "Content manager called at adress: " << &InstancePtr << std::endl;
		if (GameDataExchangePtr == nullptr)
		{ // race condition can happen here.
			GameDataExchangePtr = new GameDataManager(); // Create the instance on first call
		}
		// ======================================
		return GameDataExchangePtr;
	}

	void AddNewObjectToScene(IEntity* InputEntity);
	void GetEntitiesByClassName(const std::string& Name, std::vector<IEntity*>& OutEntities);


private:
	// Constructor Destructor
	GameDataManager() {};
	~GameDataManager() { delete GameDataExchangePtr; };
	GameDataManager(const GameDataManager&) = delete; // Prevent copy constructor
	GameDataManager& operator=(const GameDataManager&) = delete; // Prevent copy assignme

};

