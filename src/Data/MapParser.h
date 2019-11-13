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
    MapParser(AssetManager *assetManager)
    {
        this->assetManager = assetManager;
    }

    ~MapParser()
    {
        this->assetManager = nullptr;
    }

    std::vector<Entity *> Parse(sol::table node)
    {
        std::vector<Entity *> tiles;
        sol::optional<sol::table> opt = node;

        if (opt == sol::nullopt)
        {
            std::cerr << "Could not find root map node" << std::endl;
            return tiles;
        }

        std::string filePath = node["file"];
        std::string textureId = node["textureAssetId"];
        int mapSizeX = static_cast<int>(node["mapSizeX"]);
        int mapSizeY = static_cast<int>(node["mapSizeY"]);
        int tileSize = static_cast<int>(node["tileSize"]);
        int scale = static_cast<int>(node["scale"]);

        std::fstream mapFile;
        mapFile.open(filePath);

        for (int y = 0; y < mapSizeY; y++)
        {
            for (int x = 0; x < mapSizeX; x++)
            {
                char ch;
                mapFile.get(ch);
                int sourceRectY = atoi(&ch) * tileSize;
                mapFile.get(ch);
                int sourceRectX = atoi(&ch) * tileSize;

                int destRectX = x * (scale * tileSize);
                int destRectY = y * (scale * tileSize);

                Entity *tile = new Entity("Tile", TILEMAP_LAYER);

                tile->AddComponent<TileComponent>(sourceRectX, sourceRectY, destRectX, destRectY, tileSize, scale, assetManager->GetTexture(textureId));
                tiles.push_back(tile);
                mapFile.ignore();
            }
        }
        mapFile.close();

        return tiles;
    }
};

#endif