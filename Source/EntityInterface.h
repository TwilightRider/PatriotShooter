#pragma once
#include <string>


class IEntity
{
private:
	

protected:
	std::string ClassName = "DefaultClass";
	bool bDestroyEntity = false;

	virtual void SendObjectToScene() = 0;
	virtual void SetClassName(const std::string& InName);
	

public:
	IEntity* EntityOwner = nullptr;
	std::string GetClassName();
	bool GetEntityIsNeedToDestroy() const;
	void CallEntityDestruction();
	virtual void UpdateEntity() = 0;
	virtual void NotifySceneWasChanged() = 0;
};