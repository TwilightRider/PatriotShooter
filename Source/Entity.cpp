#include "Entity.h"


void Entity::ConstructCollision(bool bRecenter)
{
	this->bHasCollision = true;
	
	if (this->CollisionRectangle == nullptr)
	{
		this->CollisionRectangle = new sf::RectangleShape(this->CollisionSize);
	}
	
	if (bRecenter)
	{
		this->CollisionRectangle->setOrigin(this->CollisionSize / 2.f + this->CollisionLocalOffset);
	}
	else
	{
		this->CollisionRectangle->setOrigin(this->CollisionLocalOffset);
	}

	this->CollisionRectangle->setFillColor(this->CollisionColor);
}


Entity::Entity()
{
	this->ClassName = typeid(*this).name();
	this->WorldBounds = this->GameDataManager->WorldBounds;
	//LOG("Base constructor called:", "");
}

Entity::~Entity()
{
	//LOG("Destruct Entity", "");
	delete this->CollisionRectangle;
}


void Entity::UpdateEntity()
{
	this->DeltaTime = this->GameDataManager->DeltaTime;
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

const sf::RectangleShape* Entity::GetCollisionShape()
{
	return this->CollisionRectangle;
}


bool Entity::GetEntityIsNeedToDestroy()
{
	return this->bDestroyEntity;
}


const sf::Vector2f Entity::GetPosition()
{
	return this->Position;
}

std::string Entity::GetClassName()
{
	return this->ClassName;
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
		sf::Rect<float> ConstructWindowBounds({ 0., 0. }, { this->WorldBounds.x, this->WorldBounds.y });
		if (!ConstructWindowBounds.contains(this->Position))
		{
			return true;
		}
	}
	return false;
}

