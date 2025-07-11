#include "Entity.h"
#include "Scene.h"


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
	//this->GameScene = Scene;
	this->WorldBounds = this->GameDataManager->WorldBounds;
	//LOG("Base constructor called:", "");
}


Entity::~Entity()
{
	//LOG("Destruct Entity", "");
	if (this->CollisionRectangle != nullptr)
	{
		delete this->CollisionRectangle;
	}
}


void Entity::UpdateEntity()
{
	this->DeltaTime = this->GameDataManager->DeltaTime;
	this->EntityLifeTime += this->DeltaTime;
	this->KillOutsideOfWindow();
	if ((this->EntityLifeTime >= this->EntityMaxLifeTime && this->EntityMaxLifeTime != 0) || this->KillOutsideOfWindow())
	{
		this->CallEntityDestruction();
	}
}


const sf::RectangleShape* Entity::GetCollisionShape()
{
	return this->CollisionRectangle;
}


const sf::Vector2f Entity::GetPosition() const
{
	return this->Position;
}


void Entity::PrintClassName(const std::string &Text)
{
	std::cout << Text << typeid(*this).name() << std::endl;
}


bool Entity::KillOutsideOfWindow() const
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

