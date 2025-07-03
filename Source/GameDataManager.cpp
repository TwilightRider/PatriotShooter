#include "GameDataManager.h"
#include "Scene.h"


GameDataManager* GameDataManager::GameDataExchangePtr = nullptr;

void GameDataManager::AddNewObjectToScene(IEntity* InputEntity)
{
	if (this->GameScene != nullptr)
	{
		this->GameScene->AddObjectToScene(InputEntity);
	}
}


void GameDataManager::GetEntitiesByClassName(const std::string& Name, std::vector<IEntity*>& OutEntities)
{
	this->GameScene->ReturnEntitesByClassName(Name, OutEntities);

}



