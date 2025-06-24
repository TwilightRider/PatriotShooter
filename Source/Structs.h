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

		void SendEnemiesToProjectiles()
		{
			for (Projectile* CurrentProjectile : pProjectiles)
			{
				CurrentProjectile->SetEnemiesInScene(pEnemies);
			}
		}

		Scene(int MaxEnemies, int MaxProjectiles)
		{
			pEnemies.reserve(MaxEnemies);
			pProjectiles.reserve(MaxProjectiles);
		}
	};


	struct EnemyProperties
	{
		int KillReward = 5;
		sf::Vector2f Size = { 40.f, 40.f };;
		sf::Color Color = sf::Color::Green;
		int DownMovementSpeed = 2;
	};

	EnemyProperties EnemyEasyProperty = {

	};

	/*this->KillReward = 5;
	this->Size = { 40.f, 40.f };;
	this->Color = sf::Color::Green;
	this->DownMovementSpeed = 2;
	break;
	case Enums::EnemyClass::MEDIUM:
	this->KillReward = 10;
	this->Size = { 30.f, 30.f };;
	this->Color = { 255, 255, 0 };
	this->DownMovementSpeed = 4;
	break;
	case Enums::EnemyClass::HARD:
	this->KillReward = 15;
	this->Size = { 20.f, 20.f };;
	this->Color = { 255, 0, 0 };
	this->DownMovementSpeed = 7;
	break;*/

};

