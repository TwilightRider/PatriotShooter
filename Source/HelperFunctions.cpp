#include "HelperFunctions.h"


const sf::Texture HelperFunctions::LoadImage(const std::string& Path)
{
	sf::Texture Texture;
	bool TextureLoaded = Texture.loadFromFile(Path);
	if (!TextureLoaded)
	{
		//std::cout << "HELPERFUNCTIONS:: cannot load texture: " << Path << std::endl;
		LOG("HELPERFUNCTIONS::", "cannot load texture")
	}
	return Texture;
}

sf::Sprite HelperFunctions::ConstructSprite(const sf::Texture& Texture)
{
	/*
		Pass texture by reference!
	*/
	sf::Sprite Sprite(Texture);
	return Sprite;
}

const sf::Font HelperFunctions::LoadFont(const std::string& Path)
{
	sf::Font Font;
	bool FontLoaded = Font.openFromFile(Path);
	if (!FontLoaded)
	{
		//std::cout << "HELPERFUNCTIONS:: cannot load font: " << Path << std::endl;
		LOG("HELPERFUNCTIONS::", " cannot load font")
	}
	return Font;
}

sf::Text HelperFunctions::ConstructText(const sf::Font& Font)
{
	return sf::Text(Font);
}

void HelperFunctions::RecenterSprite(const sf::Texture& InTexture, sf::Sprite& Sprite)
{
	sf::Vector2u TextureSize = InTexture.getSize();
	sf::Vector2f ImageOrigin = static_cast<sf::Vector2f>(TextureSize);
	ImageOrigin.x = TextureSize.x / 2.f;
	ImageOrigin.y = TextureSize.y / 2.f;
	Sprite.setOrigin(ImageOrigin);
}

void HelperFunctions::SetSpriteSizePixels(sf::Sprite &InSprite, float TargetX, float TargetY)
{
	sf::Vector2f Scale;
	sf::Vector2u TextureSize = InSprite.getTexture().getSize();
	sf::Vector2f ImageSize = static_cast<sf::Vector2f>(TextureSize);
	Scale.x = (float)TargetX / ImageSize.x;
	Scale.y = (float)TargetY / ImageSize.y;
	InSprite.setScale(Scale);
}

sf::Vector2f HelperFunctions::CalculateNormalizedVector(const sf::Vector2f& StartPosition, const sf::Vector2f& EndPosition)
{
	sf::Vector2f DirectionVector;
	DirectionVector.x = EndPosition.x - StartPosition.x;
	DirectionVector.y = EndPosition.y - StartPosition.y;

	float VectorLength = DirectionVector.length();
	DirectionVector.x /= VectorLength;
	DirectionVector.y /= VectorLength;

	return DirectionVector;
}

sf::Vector2f HelperFunctions::RandomPointInCircle(float Radius, sf::Vector2f& InitialPosition)
{
	sf::Vector2f Position;
	float randomRadius = Radius * sqrt(Random());
	float theta = Random() * 2 * M_PI;
	Position.x = InitialPosition.x + randomRadius * cos(theta);
	Position.y = InitialPosition.y + randomRadius * sin(theta);
	return Position;
}

float HelperFunctions::Random()
{
	return ((float)rand() / RAND_MAX);
}
