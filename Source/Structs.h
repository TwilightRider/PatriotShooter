#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Texture.hpp"


namespace gamestructs
{
	struct EnemyPreset
	{
		sf::Texture Texture;
		sf::Vector2f Size;
		float DownMovementSpeed = 1.f;
		unsigned KillReward = 1;
		unsigned Health = 1;
		bool bIsBoss = false;
	};

	struct ProjectilePreset
	{
		sf::Texture Texture;
		sf::Vector2f Size;
		float MovementSpeed = 1.f;
		unsigned Damage = 1;
	};

	struct PlayerPreset
	{
		ProjectilePreset* Projectile = nullptr;
	};

	struct Level
	{

	};
}



// here player preset struct?