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

	sf::Vector2f MoveDir;
	//const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();

	// Continuos keyboard track
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		MoveDir = sf::Vector2f({ 0.f, -1.f });

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		MoveDir = sf::Vector2f({ 0.f, 1.f });
	}
	else
	{
		MoveDir = sf::Vector2f({ 0.f, 0.f });
	}
	// Send direction to player
	this->PlayerEntity->MovementDiretion = MoveDir;
	this->PlayerEntity->MovementSpeed = 40.f;
}


void PlayerTurretController::FireProjectile()
{
	Projectile* SpawnedProjectile = new Projectile(this->PlayerEntity->GetPosition(), this->MousePosition);
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


