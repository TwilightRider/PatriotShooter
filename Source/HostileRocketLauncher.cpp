#include "HostileRocketLauncher.h"

void EHostileRocketLauncher::FireProjectile()
{
	//Projectile* NewProjectile = new Projectile(this->TurretSprite.getPosition(), this->GameDataManager->MousePositionView);
	//if (this->PosessedByPlayer && this->EntityOwner)
	//{
	//	NewProjectile->EntityOwner = this->EntityOwner;
	//}
	//else
	//{
	//	// if no owner set turret as owner
	//	NewProjectile->EntityOwner = this;
	//}
}

void EHostileRocketLauncher::SendObjectToScene()
{
	this->GameDataManager->AddNewObjectToScene(this);
}

void EHostileRocketLauncher::NotifySceneWasChanged()
{

}

void EHostileRocketLauncher::UpdateEntity()
{

}