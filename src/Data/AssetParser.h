#ifndef ASSET_PARSER_H
#define ASSET_PARSER_H

#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../../lib/lua/sol.hpp"
#include <iostream>

class AssetParser
{
public:
    void Parse(sol::table node)
    {
        sol::optional<sol::table> opt = node;

        if (opt == sol::nullopt)
        {
            std::cerr << "Could not find root asset node" << std::endl;
            return;
        }

        for (int i = 0;; i++)
        {

            sol::optional<sol::table> opt = node[i];

            if (opt == sol::nullopt)
            {
                break;
            }

            std::string assetType = node[i]["type"];
            std::string assetId = node[i]["id"];
            std::string assetFilePath = node[i]["file"];

            if (assetType.compare("texture") == 0)
            {
                Game::assetManager->AddTexture(assetId, assetFilePath.c_str());
            }
            else if (assetType.compare("font") == 0)
            {
                Game::assetManager->AddFont(assetId, assetFilePath.c_str(), static_cast<int>(node[i]["fontSize"]));
            }
            else if (assetType.compare("sound") == 0)
            {
                Game::assetManager->AddSound(assetId, assetFilePath.c_str());
            }
            else
            {
                std::cerr << "Could not load asset with unknown type: " << assetType << std::endl;
            }
        }
    }
};

#endif