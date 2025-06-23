#pragma once
class PlayerController
{
public:
	// Contructor Destructor
	PlayerController() {};
	~PlayerController() {};

	float DeltaTime = 0.f;
	void UpdateMovement();
};

