#include "../Data/LevelParser.h"
#include "../Constants.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TileComponent.h"
#include <fstream>

LevelParser::LevelParser()
{
    mapParser = new MapParser();
}

void LevelParser::LoadLevel(std::string levelName)
{
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    lua.script_file("./assets/scripts/" + levelName + ".lua");

    sol::optional<sol::table> opt = lua[levelName];

    if (opt == sol::nullopt)
    {
        std::cerr << "Could not find root node for level: " << levelName << std::endl;
        return;
    }

    std::cout << "Loading assets.." << std::endl;
    this->LoadAssets(lua[levelName]["assets"]);

    std::cout << "Loading map.." << std::endl;
    this->mapParser->Parse(lua[levelName]["map"]);

    std::cout << "Loading entities.." << std::endl;
    this->LoadEntities(lua[levelName]["entities"]);
}

void LevelParser::LoadAssets(sol::table node)
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

void LevelParser::LoadEntities(sol::table rootNode)
{
    sol::optional<sol::table> opt = rootNode;

    if (opt = sol::nullopt)
    {
        std::cerr << "Could not find root entities node" << std::endl;
        return;
    }

    for (int i = 0;; i++)
    {
        sol::optional<sol::table> opt = rootNode[i];

        if (opt == sol::nullopt)
        {
            break;
        }

        sol::table node = rootNode[i];

        Entity &entity(Game::entityManager->AddEntity(node["name"], static_cast<LayerType>(node["layer"])));

        sol::optional<sol::table> componentsNode = node["components"];

        if (componentsNode == sol::nullopt)
        {
            std::cout << "Entity does not have any components.." << std::endl;
            break;
        }

        sol::optional<sol::table> transformComponentNode = node["components"]["transform"];

        if (transformComponentNode != sol::nullopt)
        {
            //std::cout << "Adding TransformComponent to entity: " << entity.name << std::endl;

            sol::table transform = node["components"]["transform"];

            entity.AddComponent<TransformComponent>(
                static_cast<int>(transform["position"]["x"]),
                static_cast<int>(transform["position"]["y"]),
                static_cast<int>(transform["velocity"]["x"]),
                static_cast<int>(transform["velocity"]["x"]),
                static_cast<int>(transform["width"]),
                static_cast<int>(transform["height"]),
                static_cast<int>(transform["scale"]));
        }

        sol::optional<sol::table> spriteComponentNode = node["components"]["sprite"];

        if (spriteComponentNode != sol::nullopt)
        {
            //std::cout << "Adding SpriteComponent to entity: " << entity.name << std::endl;

            sol::table sprite = node["components"]["sprite"];

            if (sprite["animated"])
            {
                entity.AddComponent<SpriteComponent>(
                    sprite["textureAssetId"],
                    static_cast<int>(sprite["frameCount"]),
                    static_cast<int>(sprite["animationSpeed"]),
                    static_cast<bool>(sprite["hasDirections"]),
                    static_cast<bool>(sprite["fixed"]));
            }
            else
            {
                entity.AddComponent<SpriteComponent>(sprite["textureAssetId"], false);
            }
        }

        sol::optional<sol::table> colliderComponentNode = node["components"]["collider"];

        if (colliderComponentNode != sol::nullopt)
        {
            //std::cout << "Adding ColliderComponent to entity: " << entity.name << std::endl;

            sol::table collider = node["components"]["collider"];

            if (entity.HasComponent<TransformComponent>())
            {
                entity.AddComponent<ColliderComponent>(
                    collider["tag"],
                    entity.GetComponent<TransformComponent>()->position.x,
                    entity.GetComponent<TransformComponent>()->position.y,
                    entity.GetComponent<TransformComponent>()->width,
                    entity.GetComponent<TransformComponent>()->height,
                    "collision-texture" // Hardcoded for now
                );
            }
            else
            {
                std::cout << "Could not add ColliderComponent because entity does not contain a TransformComponent" << std::endl;
            }
        }

        sol::optional<sol::table> keyboardControlComponentNode = node["components"]["input"];
        sol::optional<sol::table> keyboardControlInnerComponentNode = node["components"]["input"]["keyboard"];

        if (keyboardControlComponentNode != sol::nullopt && keyboardControlInnerComponentNode != sol::nullopt)
        {
            sol::table keyboardControl = node["components"]["input"]["keyboard"];

            entity.AddComponent<KeyboardControlComponent>(
                keyboardControl["up"],
                keyboardControl["right"],
                keyboardControl["down"],
                keyboardControl["left"],
                keyboardControl["shoot"]);
        }

        sol::optional<sol::table> projectileEmitterComponentNode = node["components"]["projectileEmitter"];

        if (projectileEmitterComponentNode != sol::nullopt)
        {
            sol::table projectileEmitter = node["components"]["projectileEmitter"];

            Entity &projectileEntity(Game::entityManager->AddEntity("projectile", PROJECTILE_LAYER));
            entity.AddEntity(&projectileEntity);

            if (entity.HasComponent<TransformComponent>())
            {
                projectileEntity.AddComponent<TransformComponent>(
                    entity.GetComponent<TransformComponent>()->position.x + (entity.GetComponent<TransformComponent>()->width / 2),
                    entity.GetComponent<TransformComponent>()->position.y + (entity.GetComponent<TransformComponent>()->height / 2),
                    0,
                    0,
                    projectileEmitter["width"],
                    projectileEmitter["height"],
                    1);

                projectileEntity.AddComponent<ProjectileEmitterComponent>(
                    static_cast<int>(projectileEmitter["speed"]),
                    static_cast<int>(projectileEmitter["angle"]),
                    static_cast<int>(projectileEmitter["range"]),
                    static_cast<bool>(projectileEmitter["shouldLoop"]));

                std::string projectileTextureId = projectileEmitter["textureAssetId"];
                projectileEntity.AddComponent<SpriteComponent>(projectileTextureId);

                projectileEntity.AddComponent<ColliderComponent>(
                    "PROJECTILE",
                    entity.GetComponent<TransformComponent>()->position.x,
                    entity.GetComponent<TransformComponent>()->position.y,
                    static_cast<int>(projectileEmitter["width"]),
                    static_cast<int>(projectileEmitter["height"]));
            }
            else
            {
                std::cout << "Missing critical TransformComponent for ProjectileEmitter" << std::endl;
            }
        }

        sol::optional<sol::table> textLabelComponentNode = node["components"]["text"];

        if (textLabelComponentNode != sol::nullopt)
        {
            sol::table textLabel = node["components"]["text"];
            entity.AddComponent<TextLabelComponent>(
                static_cast<int>(textLabel["position"]["x"]),
                static_cast<int>(textLabel["position"]["y"]),
                textLabel["value"],
                textLabel["fontFamily"],
                WHITE_COLOR);
        }
    }
}
