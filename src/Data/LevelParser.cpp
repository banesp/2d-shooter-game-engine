#include "../Data/LevelParser.h"
#include "../Constants.h"
#include <fstream>

LevelParser::LevelParser()
{
    mapParser = new MapParser();
}

void LevelParser::LoadLevel(std::string levelName)
{
    state.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    state.script_file("./assets/scripts/" + levelName + ".lua");

    sol::optional<sol::table> opt = state[levelName];

    if (opt == sol::nullopt)
    {
        std::cerr << "Could not find root node for level: " << levelName << std::endl;
        return;
    }

    std::cout << "Loading assets.." << std::endl;
    this->assetParser->Parse(state[levelName]["assets"]);

    std::cout << "Loading map.." << std::endl;
    this->mapParser->Parse(state[levelName]["map"]);

    std::cout << "Loading entities.." << std::endl;
    this->entityParser->Parse(state[levelName]["entities"]);
}
