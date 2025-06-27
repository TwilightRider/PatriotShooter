#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "HelperFunctions.h"


class ContentManager
{
private:

	static ContentManager* InstancePtr;

	// Constructor Destructor
	ContentManager();
	~ContentManager() { delete InstancePtr; };
	ContentManager(const ContentManager&) = delete; // Prevent copy constructor
	ContentManager& operator=(const ContentManager&) = delete; // Prevent copy assignme

	void LoadResources();

public:
	// List of resources
	sf::Texture DefaultTexture;
	sf::Texture TXTRocket01;
	sf::Texture CrosshairTexture;
	sf::Texture BackgroundTexture;
	sf::Texture ArrowPointer;
	sf::Texture Tank_Base_01;
	sf::Texture Tank_Turret_01;

	static ContentManager* GetInstance()
	{
		//std::cout << "Content manager called at adress: " << &InstancePtr << std::endl;
		if (InstancePtr == nullptr) 
		{ // race condition can happen here.
			InstancePtr = new ContentManager(); // Create the instance on first call
		}
		// ======================================
		return InstancePtr;
	}
};