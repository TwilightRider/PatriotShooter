#include "TurretObject.h"


void TurretObject::InitVariables()
{
	this->TurretAngle = sf::Angle(sf::degrees(0));
	this->BaseAngle = sf::Angle(sf::degrees(0));
}


void TurretObject::ForceSetPosition(const sf::Vector2f& Position)
{
	this->Position = Position;
	this->TurretSprite.setPosition(Position);
	this->BaseSprite.setPosition(Position);
}


void TurretObject::UpdateEntity()
{
	Entity::UpdateEntity();
	// Movement
	this->MoveTurret();

	// Rotate Sprite
	this->SetSpriteRotation(this->TurretSprite, this->TurretAngle);
}

void TurretObject::MoveTurret()
{
	// Get direction as movement from controller and save new position
	if (this->Movable || this->PosessedByPlayer)
	{
		this->TurretSprite.move(this->MovementDiretion * this->MovementSpeed * this->DeltaTime);
		this->BaseSprite.move(this->MovementDiretion * this->MovementSpeed * this->DeltaTime);
		// Update class position variable after movement
		this->Position = BaseSprite.getPosition();
	}
}


// Constructor
TurretObject::TurretObject(const sf::Vector2f& Position)
{
	this->Position = Position;
	this->ConstructTurret();
}

TurretObject::~TurretObject()
{

}

void TurretObject::ConstructTurret()
{
	// Construct collision
	//this->ConstructCollision(this->ProjectileCollisionX, this->ProjectileCollisionY, true);
	//this->CollisionRectangle->setPosition(this->StartPosition);
	// Construct sprite and set rotation and position
	this->TurretSprite.setPosition(this->Position);
	this->BaseSprite.setPosition(this->Position);

	// Set removal out of world
	this->bUseScreenKillZone = false;
	HelperFunctions::RecenterSprite(this->TurretSprite.getTexture(), this->TurretSprite);
	HelperFunctions::RecenterSprite(this->BaseSprite.getTexture(), this->BaseSprite);

	HelperFunctions::SetSpriteSizePixels(this->TurretSprite, this->PlayerSize.x, this->PlayerSize.y);
	HelperFunctions::SetSpriteSizePixels(this->BaseSprite, this->PlayerSize.x, this->PlayerSize.y);
}


void TurretObject::SetSpriteRotation(sf::Sprite &InSprite, const sf::Angle &Angle)
{
	InSprite.setRotation(this->TurretAngle);
	if (this->CollisionRectangle != nullptr)
	{
		this->CollisionRectangle->setRotation(TurretAngle);
	}
}
