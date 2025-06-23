#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class HelperFunctions
{
public:
	static const sf::Texture LoadImage(const std::string& Path);

	static sf::Sprite ConstructSprite(const sf::Texture& Texture);

	static const sf::Font LoadFont(const std::string& Path);

	static sf::Text ConstructText(const sf::Font& Font);

	static void RecenterSprite(const sf::Texture& InTexture, sf::Sprite& Sprite);

	static void SetSpriteSizePixels(sf::Sprite& InSprite, float TargetX, float TargetY);
};


