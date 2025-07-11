#include "Projectile.h"
#include "Player.h"


void Projectile::UpdateEntity()
{
	Entity::UpdateEntity();
	this->UpdateProjectile();
}


void Projectile::SendObjectToScene()
{
	this->GameDataManager->AddNewObjectToScene(this);
}

void Projectile::NotifySceneWasChanged()
{
	this->GameDataManager->GetEntitiesByClassName("Enemy", this->pEnemies);
}


Projectile::Projectile(const sf::Vector2f& Start, const sf::Vector2f& End) 
{
	this->SendObjectToScene();
	this->SetClassName("Projectile");
	// Add projectile to scene
	this->StartPosition = Start;
	this->DestinationPosition = End;
	this->CollisionSize.x = this->ProjectileCollisionX;
	this->CollisionSize.y = this->ProjectileCollisionY;
	this->CollisionLocalOffset.y = ProjectileCollisionYOffset;
	this->ConstructProjectile();
}


void Projectile::ConstructProjectile()
{
	// Construct collision
	this->ConstructCollision(true);
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
	Entity::UpdateEntity();
	//Move to another position using direction vertor
	// And check for collision with enemy
	// Stop update for this projectile
	// Handle projectile removal in Game

	// Handle movement
	this->Sprite.move(this->ProjectileDirection);
	this->CollisionRectangle->move(this->ProjectileDirection);
	this->Position = this->Sprite.getPosition();

	// TODO find best location?

	for (IEntity* It : this->pEnemies)
	{
		Enemy* IterEnemy = static_cast<Enemy*>(It);

		// Enemy collision rectangle
		const sf::RectangleShape* CurrentEnemyCollision = IterEnemy->GetCollisionShape();
		const sf::RectangleShape* ProjectileCollision = this->GetCollisionShape();
		// Here successfull hit
		if (CurrentEnemyCollision->getGlobalBounds().findIntersection(ProjectileCollision->getGlobalBounds()))
		{
			// Send kill reward to player if was shoot from player
			if (this->EntityOwner)
			{
				// Ignore hit to owner
				if (this->EntityOwner == IterEnemy)
				{
					continue;
				}
				Player* AsPlayer = static_cast<Player*>(this->EntityOwner);
				AsPlayer->PlayerPoints += IterEnemy->KillReward;
			}
			// Send to enemy class that it was hit
			IterEnemy->bEntityHit = true;
			IterEnemy->CallEntityDestruction();
			// Remove projectile after hit
			this->bEntityHit = true;
			this->CallEntityDestruction();
			return;
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
