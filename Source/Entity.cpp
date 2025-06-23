#include "Entity.h"


void Entity::ConstructCollision(float SizeX, float SizeY, bool bRecenter)
{
	sf::Vector2f Size = { SizeX, SizeY };
	this->bHasCollision = true;
	this->CollisionSize = Size;
	
	this->CollisionRectangle = new sf::RectangleShape(Size);
	this->CollisionRectangle->setFillColor(this->CollisionColor);
	if (bRecenter)
	{
		this->CollisionRectangle->setOrigin(Size / 2.f);
	}
}


Entity::~Entity()
{

}


void Entity::UpdateEntity()
{
	this->KillOutsideOfWindow();
	if ((this->EntityLifeTime >= this->EntityMaxLifeTime && this->EntityMaxLifeTime != 0) || this->KillOutsideOfWindow())
	{
		this->CallEntityDestruction();
	}
}


void Entity::CallEntityDestruction()
{
	this->bDestroyEntity = true;
}


bool Entity::GetEntityIsNeedToDestroy()
{
	return this->bDestroyEntity;
}


sf::RectangleShape* Entity::GetCollision()
{
	return this->CollisionRectangle;
}

void Entity::PrintClassName(const std::string &Text)
{
	std::cout << Text << typeid(*this).name() << std::endl;
}


bool Entity::KillOutsideOfWindow()
{
	if (this->bUseScreenKillZone)
	{
		// Construct World Bounds
		sf::Rect<float> ConstructWindowBounds({ 0., 0. }, { this->WorldSize.x, this->WorldSize.y });
		if (!ConstructWindowBounds.contains(this->Position))
		{
			return true;
		}
		return false;
	}
}

