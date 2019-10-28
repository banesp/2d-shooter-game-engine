#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Components/TileComponent.h"
#include "../../lib/glm/glm.hpp"
#include "../../lib/lua/sol.hpp"
#include <iostream>
#include <fstream>

class TileComponent;

class MapParser
{
public:
    MapParser() {}
    ~MapParser() {}

    void Parse(sol::table node)
    {
        sol::optional<sol::table> opt = node;

        if (opt == sol::nullopt)
        {
            std::cerr << "Could not find root map node" << std::endl;
            return;
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

                Entity &newTile(Game::entityManager->AddEntity("Tile", TILEMAP_LAYER));
                newTile.AddComponent<TileComponent>(
                    sourceRectX,
                    sourceRectY,
                    x * (scale * tileSize),
                    y * (scale * tileSize),
                    tileSize,
                    scale,
                    Game::assetManager->GetTexture(textureId));

                mapFile.ignore();
            }
        }
        mapFile.close();
    }
};

#endif