#include "../Data/LevelLoader.h"
#include "../Constants.h"
#include <fstream>

LevelLoader::LevelLoader(AssetManager *assetManager, EntityManager *entityManager)
{
    this->assetParser = new AssetParser();
    this->entityParser = new EntityParser(assetManager, entityManager);
    this->mapParser = new MapParser(assetManager);
}

LevelLoader::~LevelLoader()
{
    this->assetParser = nullptr;
    this->entityParser = nullptr;
    this->mapParser = nullptr;
}

void LevelLoader::Load(std::string levelName)
{
    state.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    state.script_file("./assets/scripts/" + levelName + ".lua");
    sol::optional<sol::table> opt = state[levelName];
    if (opt == sol::nullopt)
    {
        std::cerr << "Could not find root node for level: " << levelName << std::endl;
        return;
    }

    std::cout << "loading assets" << std::endl;
    loadedAssets = assetParser->Parse(state[levelName]["assets"]);

    std::cout << "loading map" << std::endl;
    loadedTiles = mapParser->Parse(state[levelName]["map"]);

    std::cout << "loading entities" << std::endl;
    loadedEntities = entityParser->Parse(state[levelName]["entities"]);

    std::cout << "loading finished" << std::endl;
}

std::vector<Entity *> LevelLoader::GetEntities()
{
    return loadedEntities;
}

std::vector<Asset *> LevelLoader::GetAssets()
{
    return loadedAssets;
}

std::vector<Entity *> LevelLoader::GetTiles()
{
    return loadedTiles;
}
