#include "PlayerTurretController.h"

        
PlayerTurretController::PlayerTurretController()
{
	this->InitVariables();
}


void PlayerTurretController::UpdateMovement()
{
	if (this->PlayerEntity != nullptr)
	{
		// Update movement
		this->TrackInput();
		// Rotate turret
		this->PlayerEntity->TurretAngle = this->SetTurretAngles();
	}
}


void PlayerTurretController::InitVariables()
{
	this->bMousePressed = false;
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
			this->FireProjectile();
		}
	}
	else
	{
		this->bMousePressed = false;
	}

	float MovementSpeed = 0.f;
	// Works as direction and mask for movement
	float MoveDir = -1.f;
	float RotationDirection = 0.f;

	// Rotate Base
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		RotationDirection = 1.f;
		//this->PlayerDirection = this->PlayerDirection.rotatedBy(sf::Angle(sf::degrees(this->DeltaTime * this->PlayerRotationSpeed)));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		RotationDirection = -1.f;
		//this->PlayerDirection = this->PlayerDirection.rotatedBy(sf::Angle(sf::degrees(this->DeltaTime * this->PlayerRotationSpeed)));
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

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		MoveDir = 1.f;
		// Flip direction for correct backward movement
		RotationDirection *= -1.f;
		MovementSpeed = this->ForwardMovementSpeed * this->BackwardsMovementScalar;
	}
	else
	{
		MoveDir = 0.f;
	}

	this->PlayerAngle = sf::Angle(sf::radians(this->DeltaTime));
	this->PlayerDirection = this->PlayerDirection.rotatedBy(sf::Angle(sf::radians(this->DeltaTime * RotationDirection * this->PlayerRotationSpeed)));

	// Send direction to player
	this->PlayerEntity->MovementDiretion = this->PlayerDirection * MoveDir;
	this->PlayerEntity->MovementSpeed = MovementSpeed;
	this->PlayerEntity->BaseAngle = this->PlayerDirection.angle() - this->HalfPI;
}


void PlayerTurretController::FireProjectile()
{
	// Get correct offset position of turret sprite
	Projectile* SpawnedProjectile = new Projectile(this->PlayerEntity->TurretSprite.getPosition(), this->MousePosition);
	SpawnedProjectile->WorldSize = this->WorldBounds;
	this->GameScene->AddObjectToScene(SpawnedProjectile);
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


