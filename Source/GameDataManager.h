#pragma once
#include "SFML/System/Vector2.hpp"



class GameDataManager
{
public:
	float DeltaTime = 0.f;
	sf::Vector2f WorldBounds;
	sf::Vector2f MousePositionView;
	sf::Vector2f PlayerStartPosition;

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

private:
	// Constructor Destructor
	GameDataManager() {};
	~GameDataManager() { delete GameDataExchangePtr; };
	GameDataManager(const GameDataManager&) = delete; // Prevent copy constructor
	GameDataManager& operator=(const GameDataManager&) = delete; // Prevent copy assignme

};

