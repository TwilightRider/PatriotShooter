#include "Enemy.h"

void Enemy::ConstructEnemy()
{
	this->InitVariables();
	this->ConstructCollision(this->Size.x, this->Size.y, false);
}


void Enemy::InitVariables()
{
	// Set ignore out of world check, for it is checked in game
	this->bUseScreenKillZone = false;
	this->bHit = 0;
	switch (this->EnemyLevel) {
	case Enums::EnemyClass::EASY:
		this->KillReward = 5;
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
		break;
	}
	this->EnemyShape.setPosition(this->CurrentPosition);
	this->EnemyShape.setSize(static_cast<sf::Vector2f>(this->Size));
	this->EnemyShape.setFillColor(this->Color);
}

void Enemy::UpdateEnemy()
{
	this->UpdatePosition();
}

void Enemy::ForceSetPosition(const sf::Vector2f& Position)
{
	this->EnemyShape.setPosition(Position);
	this->CollisionRectangle->setPosition(Position);
}


void Enemy::UpdatePosition()
{
	// Enemy movement
	this->EnemyShape.move(sf::Vector2f{ 0.f, this->DownMovementSpeed });
	this->CollisionRectangle->move(sf::Vector2f{ 0.f, this->DownMovementSpeed });
	this->Position = EnemyShape.getPosition();
}

void Enemy::UpdateEntity()
{
	this->UpdateEnemy();
}

Enemy::Enemy(Enums::EnemyClass EnemyLevel)
{
	this->EnemyLevel = EnemyLevel;
	this->ConstructEnemy();
}

