#include "PlayerTurretController.h"

        
PlayerTurretController::PlayerTurretController()
{
	this->InitVariables();
}


void PlayerTurretController::UpdatePlayerController()
{
	this->DeltaTime = GameDataManager->DeltaTime;
	this->MousePosition = GameDataManager->MousePositionView;

	if (this->PlayerTurret != nullptr)
	{
		// Update movement
		this->TrackInput();
		// Rotate turret
		this->PlayerTurret->TurretAngle = this->SetTurretAngles();
		//this->PlayerTurret->UpdateEntity();
	}
}


void PlayerTurretController::InitVariables()
{
	this->bMousePressed = false;
	this->ReceiveInput = true;
	this->TurretAngle = sf::Angle(sf::radians(0));
	this->PlayerAngle = sf::Angle(sf::radians(0));
	this->PlayerDirection = sf::Vector2f({ 0.f, 1.f });
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
			this->PlayerTurret->FireProjectile();
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
	this->PlayerTurret->MovementDiretion = this->PlayerDirection * MoveDir;
	this->PlayerTurret->MovementSpeed = MovementSpeed;
	this->PlayerTurret->BaseAngle = this->PlayerDirection.angle() - this->HalfPI;
}


sf::Angle PlayerTurretController::SetTurretAngles()
{
	sf::Vector2f ToMouseDir = HelperFunctions::CalculateNormalizedVector(this->PlayerTurret->GetPosition(), this->MousePosition);
	sf::Vector2f NormalizedDir = ToMouseDir.normalized();
	// Rotate sprite to direction vector
	sf::Vector2 UpDir = sf::Vector2f{ 0.f, 1.f };
	sf::Angle Degrees90 = sf::degrees(90);
	return NormalizedDir.angle() + Degrees90;
}


