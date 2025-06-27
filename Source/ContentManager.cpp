#include "ContentManager.h"

ContentManager* ContentManager::InstancePtr = nullptr;


ContentManager::ContentManager()
{
	this->LoadResources();
}

void ContentManager::LoadResources()
{
	this->DefaultTexture = HelperFunctions::LoadImage("./Images/T_DefaultChecker.png");
	this->TXTRocket01 = HelperFunctions::LoadImage("./Images/T_Rocket_01.png");
	this->CrosshairTexture = HelperFunctions::LoadImage("./Images/T_Crosshair.png");
	this->BackgroundTexture = HelperFunctions::LoadImage("./Images/T_Background_02.png");
	this->ArrowPointer = HelperFunctions::LoadImage("./Images/T_Arrow_Pointer_01.png");
	this->Tank_Base_01 = HelperFunctions::LoadImage("./Images/T_Tank_Base_01.png");
	this->Tank_Turret_01 = HelperFunctions::LoadImage("./Images/T_Tank_Turret_01.png");
	LOG("CONTENT MANAGER::", "Resources Loaded");
}
