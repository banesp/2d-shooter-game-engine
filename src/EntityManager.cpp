#include <iostream>
#include <stdio.h>
#include "./EntityManager.h"
#include "./Collision.h"
#include "./Components/ColliderComponent.h"

void EntityManager::ClearData() {
    for (auto& entity: entities) {
        entity->Destroy();
    }
}

void EntityManager::Update(float deltaTime) {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->Update(deltaTime);

        // If entity is no longer active erase it from the EntityManager
        if (!entities[i]->IsActive()) {
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityManager::DestroyInactiveEntities() {
    for (int i = 0; i < entities.size(); i++) {
        if (!entities[i]->IsActive()) {
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityManager::Render() {
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
        for (auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
            entity->Render();
        }
    }
}

bool EntityManager::HasNoEntities() const {
    return entities.size() == 0;
}

unsigned int EntityManager::GetEntityCount() const {
    return entities.size();
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
    std::vector<Entity*> selectedEntities;
    for (auto& entity: entities) {
        if (entity->layer == layer) {
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

void EntityManager::ListAllEntities() const {
    unsigned int i = 0;
    for (auto& entity: entities) {
        std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
        entity->ListAllComponents();
        i++;
    }
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

CollisionType EntityManager::CheckCollisions() const {
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

            printf("thisCollider tag: %s\n", thisCollider->colliderTag.c_str());
            printf("otherCollider tag: %s\n", otherCollider->colliderTag.c_str());

            if (!Collision::CheckRectangleCollision(thisCollider->collider, otherCollider->collider)) {
                continue;
            }

            printf("Collided %b %b\n", thisCollider->colliderTag.compare("PLAYER"), otherCollider->colliderTag.compare("ENEMY"));

            // TODO: Room for improvement right here
            // Sort or use another datastructure so we dont have to check both i, j for colliderTag?

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
