#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Components/TileComponent.h"
#include "../../lib/glm/glm.hpp"
#include "../../lib/lua/sol.hpp"
#include <vector>
#include <iostream>
#include <fstream>

class AssetManager;
class EntityManager;
class TileComponent;

class MapParser
{
private:
    AssetManager *assetManager;

public:
    MapParser(AssetManager *assetManager);
    ~MapParser();

    std::vector<Entity *> Parse(sol::table node);
};

#endif