#ifndef ENTITY_PARSER_H
#define ENTITY_PARSER_H

#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TileComponent.h"
#include "../Constants.h"
#include "../../lib/lua/sol.hpp"
#include <iostream>
#include <vector>

class AssetManager;
class EntityManager;

class EntityParser
{
private:
    AssetManager *assetManager;
    EntityManager *entityManager;
    void AddComponentsToEntity(Entity *entity, sol::table node);

public:
    EntityParser(AssetManager *assetManager, EntityManager *entityManager);
    ~EntityParser();
    std::vector<Entity *> Parse(sol::table rootNode);
};

#endif