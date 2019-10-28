#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "../Data/MapParser.h"
#include "../AssetManager.h"
#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include "../../lib/lua/sol.hpp"
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

    MapParser *mapParser = nullptr;

    void LoadAssets(sol::table node);
    void LoadMap(sol::table node);
    void LoadEntities(sol::table node);

public:
    LevelParser();
    void LoadLevel(std::string levelNumber);
};

#endif;