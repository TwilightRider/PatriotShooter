#pragma once
#include <vector>
#include <iostream>
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"


class Structs
{
public:
	struct Scene {

		std::vector<Enemy*> pEnemies;
		std::vector<Projectile*> pProjectiles;

		int GetObjectsCount()
		{
			//std::cout << "Projectile count: " << pProjectiles.size() << std::endl;
			//std::cout << "Enemies count: " << pEnemies.size() << std::endl;
			return pEnemies.size() + pProjectiles.size();
		}

		void AddObjectToScene(Entity* NewObject)
		{
			GetObjectsCount();
			if (typeid(*NewObject) == typeid(Enemy))
			{
				pEnemies.push_back(static_cast<Enemy*>(NewObject));
			}
			else if (typeid(*NewObject) == typeid(Projectile))
			{
				pProjectiles.push_back(static_cast<Projectile*>(NewObject));
			}
		}

		void RemoveFromScene(Entity* ObjectToRemove, int Index)
		{
			GetObjectsCount();
			if (typeid(*ObjectToRemove) == typeid(Enemy))
			{
				pEnemies.erase(pEnemies.begin() + Index);
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

		Scene(int MaxEnemies, int MaxProjectiles)
		{
			pEnemies.reserve(MaxEnemies);
			pProjectiles.reserve(MaxProjectiles);
		}
	};
};

