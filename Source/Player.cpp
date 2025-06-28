
#include "Player.h"

void Player::InitVariables()
{
    this->FireProjectile = false;

}


void Player::SpawnProjectile()
{
    this->GameScene->AddObjectToScene(this->PlayerEntity->CurrentProjectile);
}


Player::Player()
{
    this->InitVariables();
    // Construct needed objects
    this->PlayerController = new PlayerTurretController;
    this->PlayerEntity = new TurretObject(GameDataManager->PlayerStartPosition);
    
    // Set player entity important variables
    this->PlayerEntity->PosessedByPlayer = true;

    // Set entity class to player controller to operate with it
    this->PlayerController->PlayerEntity = this->PlayerEntity;

    this->PlayerController->AssignToProjectileSpawn(std::bind(&Player::SpawnProjectile, this));

    // Declare delegate for firing projectile
    //std::function<void()> RegisterProjectileDelegate;
    //RegisterProjectileDelegate = RegisterProjectile;

    //RegisterProjectileDelegate = std::bind(&PlayerTurretController::FireProjectile, this, std::placeholders::_1);

    //this->RegisterProjectile(1, std::bind(&PlayerTurretController::FireProjectile, this, std::placeholders::_1));
    /*processData(15, std::bind(&MyClass::memberCallback, &obj, std::placeholders::_1));*/


}




Player::~Player()
{
    delete this->PlayerEntity;
    delete this->PlayerController;
}


void Player::SetNewProperties()
{


}


void Player::UpdatePlayer()
{
    this->UpdatePlayerController();

}



void Player::UpdatePlayerController()
{
    if (this->PlayerController == nullptr)
    {
        return;
    }
    this->PlayerController->UpdatePlayerController();
}