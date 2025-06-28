#include "PlayerTurretController.h"

        
PlayerTurretController::PlayerTurretController()
{
	this->InitVariables();
}


void PlayerTurretController::AssignToProjectileSpawn(std::function<void()> Function)
{
	this->CallBackProjectile = Function;
}


void PlayerTurretController::UpdatePlayerController()
{
	this->DeltaTime = GameDataManager->DeltaTime;
	this->MousePosition = GameDataManager->MousePositionView;

	if (this->PlayerEntity != nullptr)
	{
		// Update movement
		this->TrackInput();
		// Rotate turret
		this->PlayerEntity->TurretAngle = this->SetTurretAngles();
		this->PlayerEntity->UpdateEntity();
	}
}


void PlayerTurretController::InitVariables()
{
	this->bMousePressed = false;
	//this->DeltaTime = GameDataManager->DeltaTime;
	//this->MousePosition = GameDataManager->MousePositionView;
}


void PlayerTurretController::TrackInput()
{
	// Track keyboard
	// Move forward
	// Move left
	// Move right
	// Move backwards
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (!this->bMousePressed)
		{
			this->bMousePressed = true;
			this->PlayerEntity->FireProjectile();
			// Register projectile shoot
			if (this->CallBackProjectile)
			{
				this->CallBackProjectile();
			}
		}
	}
	else
	{
		this->bMousePressed = false;
	}

	float RotationSpeed = this->PlayerRotationSpeed;
	float MovementSpeed = 0.f;
	// Works as direction and mask for movement
	float MoveDir = -1.f;
	float RotationDirection = 0.f;

	// Rotate Base
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		RotationDirection = 1.f;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		RotationDirection = -1.f;
	}
	else
	{
		RotationDirection = 0.f;
	}

	// Continuos keyboard track
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		MoveDir = -1.f;
		MovementSpeed = this->ForwardMovementSpeed;
		RotationSpeed = this->PlayerRotationSpeed;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		MoveDir = 1.f;
		// Flip direction for correct backward movement
		RotationDirection *= -1.f;
		MovementSpeed = this->ForwardMovementSpeed * this->BackwardsMovementScalar;
		RotationSpeed = this->PlayerRotationSpeed * this->BackwardsMovementScalar;
	}
	else
	{
		MoveDir = 0.f;
	}
	
	this->PlayerAngle = sf::Angle(sf::radians(this->DeltaTime));
	this->PlayerDirection = this->PlayerDirection.rotatedBy(sf::Angle(sf::radians(this->DeltaTime * RotationDirection * RotationSpeed)));

	// Send direction to player
	this->PlayerEntity->MovementDiretion = this->PlayerDirection * MoveDir;
	this->PlayerEntity->MovementSpeed = MovementSpeed;
	this->PlayerEntity->BaseAngle = this->PlayerDirection.angle() - this->HalfPI;
}


void PlayerTurretController::FireProjectile()
{
	// Get correct offset position of turret sprite
	/*Projectile* SpawnedProjectile = new Projectile(this->PlayerEntity->TurretSprite.getPosition(), this->MousePosition);*/
	//this->GameScene->AddObjectToScene(SpawnedProjectile);
}


sf::Angle PlayerTurretController::SetTurretAngles()
{
	sf::Vector2f ToMouseDir = HelperFunctions::CalculateNormalizedVector(this->PlayerEntity->GetPosition(), this->MousePosition);
	sf::Vector2f NormalizedDir = ToMouseDir.normalized();
	// Rotate sprite to direction vector
	sf::Vector2 UpDir = sf::Vector2f{ 0.f, 1.f };
	sf::Angle Degrees90 = sf::degrees(90);
	return NormalizedDir.angle() + Degrees90;
}


