#include "../Engine/Entity.h"
#include <iostream>

Entity::Entity()
{
    this->isActive = true;
}

Entity::Entity(std::string name, LayerType layer) : name(name), layer(layer)
{
    this->isActive = true;
}

void Entity::Update(float deltaTime)
{
    for (auto &component : components)
    {
        component->Update(deltaTime);
    }
}

void Entity::Render()
{
    for (auto &component : components)
    {
        std::cout << "Render component: " << std::endl;
        component->Render();
    }
}

void Entity::Destroy()
{
    this->isActive = false;

    for (auto &entity : entities)
    {
        entity->Destroy();
    }

    for (auto &component : components)
    {
        component->Destroy();
    }

    entities.clear();
    components.clear();
    componentTypeMap.clear();
}

bool Entity::IsActive() const
{
    return this->isActive;
}

void Entity::ListAllComponents() const
{
    for (auto mapElement : componentTypeMap)
    {
        std::cout << "    Component<" << mapElement.first->name() << ">" << std::endl;
    }
}
