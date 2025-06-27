#pragma once
#include <vector>
#include <iostream>
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"


class Scene
{
private:
	std::vector<Enemy*> pEnemies;
	std::vector<Projectile*> pProjectiles;

	void SendEnemiesToProjectiles()
	{
		for (Projectile* CurrentProjectile : pProjectiles)
		{
			CurrentProjectile->SetEnemiesInScene(pEnemies);
		}
	}

public:
	const std::vector<Enemy*>& GetEnemies()
	{
		return pEnemies;
	}

	const std::vector<Projectile*>& GetProjectiles()
	{
		return pProjectiles;
	}


	int GetObjectsCount()
	{
		LOG("Projectile count: ", std::to_string(pProjectiles.size()));
		LOG("Enemies count: ", std::to_string(pEnemies.size()));
		return pEnemies.size() + pProjectiles.size();
	}

	void AddObjectToScene(Entity* NewObject)
	{
		GetObjectsCount();
		if (typeid(*NewObject) == typeid(Enemy))
		{
			pEnemies.push_back(static_cast<Enemy*>(NewObject));
			SendEnemiesToProjectiles();
		}
		else if (typeid(*NewObject) == typeid(Projectile))
		{
			pProjectiles.push_back(static_cast<Projectile*>(NewObject));
			SendEnemiesToProjectiles();
		}
	}

	void RemoveFromScene(Entity* ObjectToRemove, int Index)
	{
		GetObjectsCount();
		if (typeid(*ObjectToRemove) == typeid(Enemy))
		{
			pEnemies.erase(pEnemies.begin() + Index);
			SendEnemiesToProjectiles();
		}
		else if (typeid(*ObjectToRemove) == typeid(Projectile))
		{
			pProjectiles.erase(pProjectiles.begin() + Index);
		}
	}

	void ClearScene()
	{
		pEnemies.clear();
		pProjectiles.clear();
	}


	// Constructor
	Scene(int MaxEnemies, int MaxProjectiles)
	{
		pEnemies.reserve(MaxEnemies);
		pProjectiles.reserve(MaxProjectiles);
	}
};


