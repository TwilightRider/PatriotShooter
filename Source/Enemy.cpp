#include "Enemy.h"
#include "Player.h"


void Enemy::ConstructEnemy()
{
	
	this->InitVariables();
	this->ConstructCollision(false);
}


void Enemy::InitVariables()
{
	switch (this->EnemyLevel) 
	{
	case Enums::EnemyClass::EASY:
		this->CurrentPreset = this->EntityManager->EnemyEasy;
		break;
	case Enums::EnemyClass::MEDIUM:
		this->CurrentPreset = this->EntityManager->EnemyMedium;
		break;
	case Enums::EnemyClass::HARD:
		this->CurrentPreset = this->EntityManager->EnemyHard;
		break;
	}

	this->EnemySprite.setTexture(this->CurrentPreset->Texture);
	this->Size = this->CurrentPreset->Size;
	this->KillReward = this->CurrentPreset->KillReward;
	this->DownMovementSpeed = this->CurrentPreset->DownMovementSpeed;

	HelperFunctions::SetSpriteSizePixels(this->EnemySprite, this->Size.x, this->Size.y);
	this->CollisionSize = this->CurrentPreset->Size;
	// Set ignore out of world check, for it is checked in game
	this->bUseScreenKillZone = false;
}


void Enemy::ForceSetPosition(const sf::Vector2f& Position)
{
	this->EnemySprite.setPosition(Position);
	this->CollisionRectangle->setPosition(Position);
}


void Enemy::UpdatePosition()
{
	// Enemy movement
	this->EnemySprite.move(sf::Vector2f{ 0.f, this->DownMovementSpeed });
	this->CollisionRectangle->move(sf::Vector2f{ 0.f, this->DownMovementSpeed });
	this->Position = EnemySprite.getPosition();
}


void Enemy::UpdateEntity()
{
	this->UpdatePosition();
	this->TrackEnemyOutBounds();
}


void Enemy::TrackEnemyOutBounds()
{
	// if enemy is past the bottom
	if (this->EnemySprite.getPosition().y + this->GetSize().y > this->GameDataManager->WindowSize.y)
	{
		this->CallEntityDestruction();
		this->MainPlayer->Health -= this->HealtDecrementOutBounds;
	}
}


void Enemy::NotifySceneWasChanged()
{

}


void Enemy::SendObjectToScene()
{
	this->GameDataManager->AddNewObjectToScene(this);
}


Enemy::Enemy(Enums::EnemyClass EnemyLevel)
{
	this->SetClassName("Enemy");
	this->SendObjectToScene();
	this->EnemyLevel = EnemyLevel;
	this->ConstructEnemy();
}


const sf::Sprite& Enemy::GetEnemySprite()
{
	return this->EnemySprite;
}


const sf::Vector2f Enemy::GetSize()
{
	return this->Size;
}

