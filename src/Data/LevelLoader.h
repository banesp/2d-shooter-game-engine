#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "../AssetManager.h"
#include "../EntityManager.h"
#include "../Data/AssetParser.h"
#include "../Data/MapParser.h"
#include "../Data/EntityParser.h"
#include "../Engine/Entity.h"
#include "../../lib/glm/glm.hpp"
#include "../../lib/lua/sol.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>

class AssetParser;
class MapParser;
class EntityParser;

class LevelLoader
{
private:
    sol::state state;

    AssetParser *assetParser = nullptr;
    MapParser *mapParser = nullptr;
    EntityParser *entityParser = nullptr;

    std::vector<Asset *> loadedAssets;
    std::vector<Entity *> loadedEntities;
    std::vector<Entity *> loadedTiles;

public:
    LevelLoader(AssetManager *assetManager, EntityManager *entityManager);
    ~LevelLoader();

    void Load(std::string levelNumber);

    std::vector<Entity *> GetEntities();
    std::vector<Asset *> GetAssets();
    std::vector<Entity *> GetTiles();
};

#endif;