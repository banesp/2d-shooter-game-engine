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
    std::vector<Asset *> Parse(sol::table node);
};

#endif