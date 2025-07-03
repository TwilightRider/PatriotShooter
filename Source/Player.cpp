
#include "Player.h"

void Player::InitVariables()
{
    //this->FireProjectile = false;
    this->Health = 100;
}


Player::Player()
{
    this->SetClassName("Player");
    this->InitVariables();
    // Construct needed objects
    this->PlayerController = new PlayerTurretController;

    this->PlayerTurret = new TurretObject(GameDataManager->PlayerStartPosition);
    // Set player entity important variables
    this->PlayerTurret->PosessedByPlayer = true;
    // Owner of turret
    this->PlayerTurret->EntityOwner = this;

    // Set entity class to player controller to operate with it
    this->PlayerController->PlayerTurret = this->PlayerTurret;
}


Player::~Player()
{
    delete this->PlayerController;
}


void Player::UpdateEntity()
{
    this->UpdatePlayerController();
}

void Player::NotifySceneWasChanged()
{

}


void Player::SendObjectToScene()
{

}


void Player::UpdatePlayerController()
{
    if (this->PlayerController == nullptr)
    {
        return;
    }
    this->PlayerController->UpdatePlayerController();
}