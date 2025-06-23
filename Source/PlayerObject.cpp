#include "PlayerObject.h"


void PlayerObject::InitVariables()
{


}

void PlayerObject::ForceSetPosition(const sf::Vector2f& Position)
{
	this->Position = Position;
	this->Sprite.setPosition(Position);
}


void PlayerObject::UpdateEntity()
{
	Entity::UpdateEntity();
	sf::Vector2f ToMouseDir = HelperFunctions::CalculateVector(this->Position, this->MousePosition);
	this->PlayerDirection = ToMouseDir * this->MovementSpeed;
	this->SetSpriteRotation();
}

// Constructor
PlayerObject::PlayerObject(const sf::Vector2f& Position)
{
	this->Position = Position;
	this->ConstructPlayer();
}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::ConstructPlayer()
{
	// Construct collision
	//this->ConstructCollision(this->ProjectileCollisionX, this->ProjectileCollisionY, true);
	//this->CollisionRectangle->setPosition(this->StartPosition);
	
	// Construct sprite and set rotation and position
	this->Sprite.setPosition(this->Position);

	// Set removal out of world
	this->bUseScreenKillZone = false;
	HelperFunctions::RecenterSprite(this->Sprite.getTexture(), this->Sprite);
	HelperFunctions::SetSpriteSizePixels(this->Sprite, this->PlayerSize.x, this->PlayerSize.y);
}


void PlayerObject::SetSpriteRotation()
{
	sf::Vector2f NormalizedDir = this->PlayerDirection.normalized();
	// Rotate sprite to direction vector
	sf::Vector2 UpDir = sf::Vector2f{ 0.f, 1.f };
	sf::Angle Degrees90 = sf::degrees(90);
	sf::Angle AngleToTarget = NormalizedDir.angle() + Degrees90;
	this->Sprite.setRotation(AngleToTarget);
	if (this->CollisionRectangle != nullptr)
	{
		this->CollisionRectangle->setRotation(AngleToTarget);
	}
}
