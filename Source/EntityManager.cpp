#include "EntityManager.h"
EntityManager* EntityManager::pEntityManager = nullptr;


EntityManager::EntityManager()
{
	this->SetEnemiesPrefabs();
	this->SetProjectilesPrefabs();
	this->SetPlayersPrefabs();
}


EntityManager::~EntityManager()
{
	// Delete enemy types
	delete EnemyEasy;
	delete EnemyMedium;
	delete EnemyHard;
	delete Boss;

	// Delete projectiles
	delete GunFire;
	delete SimpleRocket;
	delete HeavyRocket;
}


void EntityManager::SetEnemiesPrefabs()
{
	// Compose Easy
	this->EnemyEasy->Texture = this->ContentManager->DefaultTexture;
	this->EnemyEasy->Size = sf::Vector2f({ 40.f, 40.f });
	this->EnemyEasy->DownMovementSpeed = 2.f;
	this->EnemyEasy->KillReward = 5;
	this->EnemyEasy->Health = 1;
	this->EnemyEasy->bIsBoss = false;

	// Compose Middle
	this->EnemyMedium->Texture = this->ContentManager->DefaultTexture;
	this->EnemyMedium->Size = sf::Vector2f({ 33.f, 33.f });
	this->EnemyMedium->DownMovementSpeed = 4.f;
	this->EnemyMedium->KillReward = 10;
	this->EnemyMedium->Health = 1;
	this->EnemyMedium->bIsBoss = false;

	// Compose Hard
	this->EnemyHard->Texture = this->ContentManager->DefaultTexture;
	this->EnemyHard->Size = sf::Vector2f({ 25.f, 25.f });
	this->EnemyHard->DownMovementSpeed = 6.f;
	this->EnemyHard->KillReward = 15;
	this->EnemyHard->Health = 1;
	this->EnemyHard->bIsBoss = false;
}


void EntityManager::SetProjectilesPrefabs()
{
	// Compose Projectiles
	this->GunFire->Texture = this->ContentManager->DefaultTexture;
	this->GunFire->Size = sf::Vector2f({ 8.f, 8.f });
	this->GunFire->MovementSpeed = 10.f;
	this->GunFire->Damage = 1;

	// Compose Projectiles
	this->SimpleRocket->Texture = this->ContentManager->TXTRocket01;
	this->SimpleRocket->Size = sf::Vector2f({ 80.f, 60.f });
	this->SimpleRocket->MovementSpeed = 12.f;
	this->SimpleRocket->Damage = 1;
}


void EntityManager::SetPlayersPrefabs()
{
	this->PlayerFirstLevel->Projectile = this->GunFire;
	this->PlayerSecondLevel->Projectile = this->SimpleRocket;
}

