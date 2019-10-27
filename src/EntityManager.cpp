#include "./EntityManager.h"
#include "./Engine/Collision.h"
#include "./Components/ColliderComponent.h"
#include <iostream>
#include <stdio.h>

void EntityManager::ClearData()
{
    for (auto &entity : entities)
    {
        entity->Destroy();
    }

    entities.clear();
}

void EntityManager::Update(float deltaTime)
{
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->Update(deltaTime);

        if (!entities[i]->IsActive())
        {
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityManager::DestroyInactiveEntities()
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (!entities[i]->IsActive())
        {
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityManager::Render()
{
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++)
    {
        for (auto &entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
        {
            entity->Render();
        }
    }
}

bool EntityManager::HasNoEntities() const
{
    return entities.size() == 0;
}

unsigned int EntityManager::GetEntityCount() const
{
    return entities.size();
}

std::vector<Entity *> EntityManager::GetEntities() const
{
    return entities;
}

std::vector<Entity *> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
    std::vector<Entity *> selectedEntities;
    for (auto &entity : entities)
    {
        if (entity->layer == layer)
        {
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

void EntityManager::ListAllEntities() const
{
    unsigned int i = 0;
    for (auto &entity : entities)
    {
        std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
        entity->ListAllComponents();
        i++;
    }
}

Entity &EntityManager::AddEntity(std::string entityName, LayerType layer)
{
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}
