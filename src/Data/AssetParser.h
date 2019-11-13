#ifndef ASSET_PARSER_H
#define ASSET_PARSER_H

#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Data/Asset.h"
#include "../../lib/lua/sol.hpp"
#include <iostream>
#include <vector>

class AssetParser
{
public:
    std::vector<Asset*> Parse(sol::table node)
    {
        std::vector<Asset *> assets;
        sol::optional<sol::table> opt = node;

        if (opt == sol::nullopt)
        {
            std::cerr << "Could not find root asset node" << std::endl;
            return assets;
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
                assets.push_back(new Asset(assetType, assetId, assetFilePath.c_str()));
            }
            else if (assetType.compare("font") == 0)
            {
                int fontSize = static_cast<int>(node[i]["fontSize"]);
                assets.push_back(new Asset(assetType, assetId, assetFilePath.c_str(), fontSize));
            }
            else if (assetType.compare("sound") == 0)
            {
                assets.push_back(new Asset(assetType, assetId, assetFilePath.c_str()));
            }
            else
            {
                std::cerr << "Could not load asset with unknown type: " << assetType << std::endl;
            }
        }

        return assets;
    }
};

#endif