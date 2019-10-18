#include "./EntityManager.h"
#include "./Collision.h"
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

        // If entity is no longer active erase it from the EntityManager
        if (!entities[i]->IsActive())
        {
            // Clean up before erasing?
            std::cout << "Erasing" << std::endl;
            entities.erase(entities.begin() + i);
            std::cout << "Erased" << std::endl;
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

CollisionType EntityManager::CheckCollisions() const
{
    for (int i = 0; i < entities.size() - 1; i++) {
        if (!this->entities[i]->HasComponent<ColliderComponent>()) {
            continue;
        }

        ColliderComponent* thisCollider = this->entities[i]->GetComponent<ColliderComponent>();

        for (int j = i + 1; j < entities.size(); j++) {            
            if (!this->entities[j]->HasComponent<ColliderComponent>()) {
                continue;
            }

            ColliderComponent* otherCollider = this->entities[j]->GetComponent<ColliderComponent>();

            if (!Collision::CheckRectangleCollision(thisCollider->collider, otherCollider->collider)) {
                continue;
            }

            if ((thisCollider->colliderTag.compare("PLAYER") == 0 && otherCollider->colliderTag.compare("ENEMY") == 0) ||
                (thisCollider->colliderTag.compare("ENEMY") == 0 && otherCollider->colliderTag.compare("PLAYER") == 0)) {
                return PLAYER_ENEMY_COLLISION;
            }

            if ((thisCollider->colliderTag.compare("PLAYER") == 0 && otherCollider->colliderTag.compare("PROJECTILE") == 0) ||
                (thisCollider->colliderTag.compare("PROJECTILE") == 0 && otherCollider->colliderTag.compare("PLAYER") == 0)) {
                return PLAYER_PROJECTILE_COLLISION;
            }

            if ((thisCollider->colliderTag.compare("ENEMY") == 0 && otherCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0) ||
                (thisCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0 && otherCollider->colliderTag.compare("ENEMY") == 0)) {
                return ENEMY_PROJECTILE_COLLISION;
            }

            if ((thisCollider->colliderTag.compare("PLAYER") == 0 && otherCollider->colliderTag.compare("LEVEL_COMPLETE") == 0) ||
                (thisCollider->colliderTag.compare("LEVEL_COMPLETE") == 0 && otherCollider->colliderTag.compare("PLAYER") == 0)) {
                return PLAYER_LEVEL_COMPLETE_COLLISION;
            }
        }
    }

    return NO_COLLISION;
}
