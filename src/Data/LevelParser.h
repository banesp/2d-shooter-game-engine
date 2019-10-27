#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "../../lib/glm/glm.hpp"
#include "../../lib/lua/sol.hpp"
#include "../AssetManager.h"
#include "../EntityManager.h"
#include <stdio.h>
#include <iostream>

/**
 * Idea: Make this class fully 'static' loader.
 * And then return loaded assets, map, entities.
 * Or expose it through getters and clean up resources afterwards.
 */

class AssetManager;
class EntityManager;

class LevelParser
{
private:
    sol::state lua;
    AssetManager *assetManager = nullptr;
    EntityManager *entityManager = nullptr;

    void LoadAssets(sol::table node);
    void LoadMap(sol::table node);
    void LoadEntities(sol::table node);

public:
    LevelParser(AssetManager *assetManager, EntityManager *entityManager);
    void LoadLevel(std::string levelNumber);
};

#endif;