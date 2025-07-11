#include "EntityInterface.h"

std::string IEntity::GetClassName()
{
    return this->ClassName;
}

bool IEntity::GetEntityIsNeedToDestroy() const
{
    return this->bDestroyEntity;
}

void IEntity::CallEntityDestruction()
{
    this->bDestroyEntity = true;
}


void IEntity::SetClassName(const std::string& InName)
{
    this->ClassName = InName;
}