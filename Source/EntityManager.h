#pragma once
#include "ContentManager.h"
#include "Structs.h"


class EntityManager
{
protected:
	/* Class for storing prefabs of enemies */
	/* Game balance here*/

	static EntityManager* pEntityManager;
	ContentManager* ContentManager = ContentManager::GetInstance();

	// Constructor Destructor
	EntityManager();
	~EntityManager();
	EntityManager(const EntityManager&) = delete; // Prevent copy constructor
	EntityManager& operator=(const EntityManager&) = delete; // Prevent copy assignme

	void SetStructProperties();

	
public:
	static EntityManager* GetInstance()
	{
		//std::cout << "Content manager called at adress: " << &InstancePtr << std::endl;
		if (pEntityManager == nullptr)
		{ // race condition can happen here.
			pEntityManager = new EntityManager(); // Create the instance on first call
		}
		// ======================================
		return pEntityManager;
	}
	
	// Define enemy types
	gamestructs::EnemyPreset* EnemyEasy = new gamestructs::EnemyPreset;
	gamestructs::EnemyPreset* EnemyMedium = new gamestructs::EnemyPreset;
	gamestructs::EnemyPreset* EnemyHard = new gamestructs::EnemyPreset;
	gamestructs::EnemyPreset* Boss = new gamestructs::EnemyPreset;

	// Define projectiles
	gamestructs::ProjectilePreset* GunFire = new gamestructs::ProjectilePreset;
	gamestructs::ProjectilePreset* SimpleRocket = new gamestructs::ProjectilePreset;
	gamestructs::ProjectilePreset* HeavyRocket = new gamestructs::ProjectilePreset;
};


