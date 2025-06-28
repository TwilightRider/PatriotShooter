#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define LOG(logtype, msg) std::cout << logtype << msg << std::endl;

class HelperFunctions
{
public:
	static const sf::Texture LoadImage(const std::string& Path);

	static sf::Sprite ConstructSprite(const sf::Texture& Texture);

	static const sf::Font LoadFont(const std::string& Path);

	static sf::Text ConstructText(const sf::Font& Font);

	static void RecenterSprite(const sf::Texture& InTexture, sf::Sprite& Sprite);

	static void SetSpriteSizePixels(sf::Sprite& InSprite, float TargetX, float TargetY);

	static sf::Vector2f CalculateNormalizedVector(const sf::Vector2f& StartPosition, const sf::Vector2f& EndPosition);

	static bool CircleCollisionDetection(sf::Vector2f Position1, sf::Vector2f Position2, float Radius1, float Radius2);

	static float GetRadiusFromBounds(float XSize, float YSize);

};


