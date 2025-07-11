#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "HelperFunctions.h"
#include "EntityInterface.h"


class Scene
{
private:
	std::vector<IEntity*> SceneEntities;
	std::string SceneName = "";
	std::string ScenePath = "";

public:
	// Constructor
	Scene(int MaxEnemies, int MaxProjectiles)
	{
		this->SceneEntities.reserve(30);
	}

	std::vector<IEntity*> GetEntities() const
	{
		return this->SceneEntities;
	}

	int GetObjectsCount()
	{
		//LOG("Objects in scene: ", std::to_string(SceneEntities.size()));
		return SceneEntities.size();
	}

	void UpdateScene()
	{
		for (unsigned i = 0; i < this->SceneEntities.size(); i++)
		{
			IEntity* Entity = this->SceneEntities[i];
			if (Entity != nullptr)
			{
				if (Entity->GetEntityIsNeedToDestroy())
				{
					this->RemoveFromScene(Entity);
					//LOG("Scene size", std::to_string(this->SceneEntities.size()));
				}
				else
				{
					Entity->UpdateEntity();
				}
			}
		}
	}

	void ReturnEntitesByClassName(const std::string& Name, std::vector<IEntity*>& OutEntities)
	{
		OutEntities.clear();
		for (IEntity* Entity : this->SceneEntities)
		{
			if (Entity->GetClassName() == Name)
			{
				OutEntities.push_back(Entity);
			}
		}
	}

	void NotifyEntitiesSceneStateChanged()
	{
		// Notify all entities that something was add
		for (IEntity* Entity : this->SceneEntities)
		{
			Entity->NotifySceneWasChanged();
		}
	}

	int GetCountByClassName(const std::string& Name)
	{
		int Count = 0;
		for (IEntity* Entity : this->SceneEntities)
		{
			if (Entity->GetClassName() == Name)
			{
				Count += 1;
			}
		}
		return Count;
	}

	void AddObjectToScene(IEntity* NewObject)
	{
		GetObjectsCount();
		SceneEntities.push_back(NewObject);
		this->NotifyEntitiesSceneStateChanged();
	}

	void RemoveFromScene(IEntity* ObjectToRemove)
	{
		GetObjectsCount();

		for (unsigned i = 0; i < SceneEntities.size(); i++)
		{
			IEntity* It = SceneEntities[i];
			if (It == ObjectToRemove)
			{
				delete SceneEntities[i];
				SceneEntities.erase(SceneEntities.begin() + i);
				this->NotifyEntitiesSceneStateChanged();
				break;
			}
		}
	}

	void ClearScene()
	{
		for (unsigned i = 0; i < this->SceneEntities.size(); i++)
		{
			if (SceneEntities[i] != nullptr)
			{
				delete SceneEntities[i];
			}
		}
		SceneEntities.clear();
	}
};


