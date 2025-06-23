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

public:
	sf::Texture DefaultTexture = HelperFunctions::LoadImage("./Images/T_DefaultChecker.png");
	sf::Texture TXTRocket01 = HelperFunctions::LoadImage("./Images/T_Rocket_01.png");
	sf::Texture CrosshairTexture = HelperFunctions::LoadImage("./Images/T_Crosshair.png");
	sf::Texture BackgroundTexture = HelperFunctions::LoadImage("./Images/T_Background.png");
	

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