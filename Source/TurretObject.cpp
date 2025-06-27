#include "TurretObject.h"


void TurretObject::InitVariables()
{
	this->TurretAngle = sf::Angle(sf::degrees(0));
	this->BaseAngle = sf::Angle(sf::degrees(0));
}


void TurretObject::ForceSetPosition(const sf::Vector2f& Position)
{
	this->Position = Position;
	//this->TurretSprite.setPosition(Position);
	this->BaseSprite.setPosition(Position);
}


void TurretObject::UpdateEntity()
{
	Entity::UpdateEntity();
	// Movement
	this->MoveTurret();
}


void TurretObject::MoveTurret()
{
	// Get direction as movement from controller and save new position
	if (this->Movable || this->PosessedByPlayer)
	{
		//this->TurretSprite.move(this->MovementDiretion * this->MovementSpeed * this->DeltaTime);
		this->BaseSprite.move(this->MovementDiretion * this->MovementSpeed * this->DeltaTime);
		// Rotate Base
		this->BaseSprite.setRotation(this->BaseAngle);

		if (this->CollisionRectangle != nullptr)
		{
			this->CollisionRectangle->setRotation(TurretAngle);
		}

		// Update class position variable after movement
		this->Position = BaseSprite.getPosition();
		// Get Base Xform
		const sf::Transform& BaseXform = this->BaseSprite.getTransform();
		// Appy World transformation
		sf::Vector2f TurretPosition = BaseXform * this->TurretLocalOffset;
		this->TurretSprite.setPosition(TurretPosition);
	}
	this->TurretSprite.setRotation(this->TurretAngle);
}


// Constructor
TurretObject::TurretObject(const sf::Vector2f& Position)
{
	//LOG("Child turret constructor called:", "");
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
	this->BaseSprite.setPosition(this->Position);

	// Set removal out of world
	this->bUseScreenKillZone = false;
	HelperFunctions::SetSpriteSizePixels(this->TurretSprite, this->TurretSize.x, this->TurretSize.y);
	HelperFunctions::SetSpriteSizePixels(this->BaseSprite, this->BaseSize.x, this->BaseSize.y);
	// Set local offset for turret
	HelperFunctions::RecenterSprite(this->TurretSprite.getTexture(), this->TurretSprite);
	HelperFunctions::RecenterSprite(this->BaseSprite.getTexture(), this->BaseSprite);

	// Add pivot of base to turret local offset
	this->TurretLocalOffset += this->BaseSprite.getOrigin();
}