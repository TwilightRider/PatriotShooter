#include "Projectile.h"


void Projectile::UpdateEntity()
{
	Entity::UpdateEntity();
	this->UpdateProjectile();
}

void Projectile::ConstructProjectile()
{
	// Construct collision
	this->ConstructCollision(this->ProjectileCollisionX, this->ProjectileCollisionY, true);
	this->CollisionRectangle->setPosition(this->StartPosition);

	// Construct sprite and set rotation and position
	this->Sprite.setPosition(this->StartPosition);

	// Set removal out of world
	this->bUseScreenKillZone = true;
	HelperFunctions::RecenterSprite(this->Sprite.getTexture(), this->Sprite);
	HelperFunctions::SetSpriteSizePixels(this->Sprite, this->ProjectileSizeX, this->ProjectileSizeY);

	sf::Vector2f ToMouseDir = HelperFunctions::CalculateNormalizedVector(this->StartPosition, this->DestinationPosition);
	this->ProjectileDirection = ToMouseDir * this->ProjectileSpeed;
	this->SetSpriteRotation();
}

void Projectile::UpdateProjectile()
{
	//Move to another position using direction vertor
	// And check for collision with enemy
	// Stop update for this projectile
	// Handle projectile removal in Game

	// Handle movement
	this->Sprite.move(this->ProjectileDirection);
	this->CollisionRectangle->move(this->ProjectileDirection);
	this->Position = this->Sprite.getPosition();

	for (Entity* IterEnemy : this->pEnemies)
	{
		if (IterEnemy == nullptr)
		{
			continue;
		}
		// Enemy collision rectangle
		sf::RectangleShape* CurrentEnemyShape = IterEnemy->GetCollision();
		const sf::RectangleShape& ProjectileCollision = *this->CollisionRectangle;
		if (CurrentEnemyShape == nullptr)
		{
			continue;
		}
		// Here successfull hit
		if (CurrentEnemyShape->getGlobalBounds().findIntersection(ProjectileCollision.getGlobalBounds()))
		{
			this->bProjectileHit = true;
			// Send to enemy class that it was hit
			IterEnemy->CallEntityDestruction();
			break;
		}
	}
}


void Projectile::SetSpriteRotation()
{
	// Rotate sprite to direction vector
	sf::Vector2 UpDir = sf::Vector2f{ 0.f, 1.f };
	sf::Angle Degrees90 = sf::degrees(90);
	sf::Angle AngleToTarget = this->ProjectileDirection.angle() + Degrees90;
	this->Sprite.setRotation(AngleToTarget);
	if (this->CollisionRectangle != nullptr)
	{
		this->CollisionRectangle->setRotation(AngleToTarget);
	}
}


void Projectile::SetEnemiesInScene(std::vector<Enemy*> InEnemyList)
{
	this->pEnemies = InEnemyList;
}


// Constructor
Projectile::Projectile(const sf::Vector2f& Start, const sf::Vector2f& End)
{	
	this->StartPosition = Start;
	this->DestinationPosition = End;
	this->ConstructProjectile();
}
