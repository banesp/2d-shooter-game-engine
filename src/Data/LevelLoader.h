#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "../Data/AssetParser.h"
#include "../Data/MapParser.h"
#include "../Data/EntityParser.h"
#include "../AssetManager.h"
#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include "../../lib/lua/sol.hpp"
#include <stdio.h>
#include <iostream>

class AssetManager;
class EntityManager;

class LevelLoader
{
private:
    sol::state state;

    AssetParser *assetParser = nullptr;
    MapParser *mapParser = nullptr;
    EntityParser *entityParser = nullptr;

public:
    LevelLoader() {}
    void Load(std::string levelNumber);
};

#endif;