
#include "Player.h"

void Player::InitVariables()
{
    //this->FireProjectile = false;
    this->Health = 100;
    this->PlayerLevel = 1;
    this->PlayerPoints;
}


Player::Player()
{
    this->SetClassName("Player");
    SendObjectToScene();
    this->InitVariables();
    // Construct needed objects
    this->PlayerController = new PlayerTurretController;

    this->PlayerTurret = new TurretObject (GameDataManager->PlayerStartPosition, true);
    // Set player entity important variables
    this->PlayerTurret->PosessedByPlayer = true;
    // Owner of turret
    this->PlayerTurret->EntityOwner = this;

    // Set entity class to player controller to operate with it
    this->PlayerController->PlayerTurret = this->PlayerTurret;
}


Player::~Player()
{
    LOG("player destructor", "");
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
    this->GameDataManager->AddNewObjectToScene(this);
}


void Player::UpdatePlayerController()
{
    if (this->PlayerController == nullptr)
    {
        return;
    }
    this->PlayerController->UpdatePlayerController();
}