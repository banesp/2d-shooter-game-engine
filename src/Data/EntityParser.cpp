#include "./EntityParser.h"

void EntityParser::AddComponentsToEntity(Entity *entity, sol::table node)
{
    sol::optional<sol::table> opt = node;
    if (opt == sol::nullopt)
    {
        return;
    }

    sol::optional<sol::table> transformComponentNode = node["components"]["transform"];
    if (transformComponentNode != sol::nullopt)
    {
        sol::table transform = node["components"]["transform"];
        entity->AddComponent<TransformComponent>(
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
        sol::table sprite = node["components"]["sprite"];
        if (sprite["animated"])
        {
            entity->AddComponent<SpriteComponent>(
                assetManager->GetTexture(sprite["textureAssetId"]),
                static_cast<int>(sprite["frameCount"]),
                static_cast<int>(sprite["animationSpeed"]),
                static_cast<bool>(sprite["hasDirections"]),
                static_cast<bool>(sprite["fixed"]));
        }
        else
        {
            entity->AddComponent<SpriteComponent>(
                assetManager->GetTexture(sprite["textureAssetId"]),
                false);
        }
    }

    sol::optional<sol::table> colliderComponentNode = node["components"]["collider"];
    if (colliderComponentNode != sol::nullopt)
    {
        sol::table collider = node["components"]["collider"];
        if (entity->HasComponent<TransformComponent>())
        {
            entity->AddComponent<ColliderComponent>(
                collider["tag"],
                entity->GetComponent<TransformComponent>()->position.x,
                entity->GetComponent<TransformComponent>()->position.y,
                entity->GetComponent<TransformComponent>()->width,
                entity->GetComponent<TransformComponent>()->height,
                "collision-texture" // Hardcoded for now, should be read from file
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
        entity->AddComponent<KeyboardControlComponent>(
            entityManager,
            keyboardControl["up"],
            keyboardControl["right"],
            keyboardControl["down"],
            keyboardControl["left"],
            keyboardControl["shoot"]);
    }

    sol::optional<sol::table> projectileEmitterComponentNode = node["components"]["projectileEmitter"];
    /*
        if (projectileEmitterComponentNode != sol::nullopt)
        {
            sol::table projectileEmitter = node["components"]["projectileEmitter"];
            Entity &projectileEntity(entityManager->AddEntity("projectile", PROJECTILE_LAYER));
            entity->AddEntity(projectileEntity);

            if (entity->HasComponent<TransformComponent>())
            {
                projectileEntity->AddComponent<TransformComponent>(
                    entity->GetComponent<TransformComponent>()->position.x + (entity->GetComponent<TransformComponent>()->width / 2),
                    entity->GetComponent<TransformComponent>()->position.y + (entity->GetComponent<TransformComponent>()->height / 2),
                    0,
                    0,
                    projectileEmitter["width"],
                    projectileEmitter["height"],
                    1);
                projectileEntity->AddComponent<ProjectileEmitterComponent>(
                    static_cast<int>(projectileEmitter["speed"]),
                    static_cast<int>(projectileEmitter["angle"]),
                    static_cast<int>(projectileEmitter["range"]),
                    static_cast<bool>(projectileEmitter["shouldLoop"]));
                projectileEntity->AddComponent<SpriteComponent>(assetManager->GetTexture(projectileEmitter["textureAssetId"]));
                projectileEntity->AddComponent<ColliderComponent>(
                    "PROJECTILE",
                    entity->GetComponent<TransformComponent>()->position.x,
                    entity->GetComponent<TransformComponent>()->position.y,
                    static_cast<int>(projectileEmitter["width"]),
                    static_cast<int>(projectileEmitter["height"]));
            }
            else
            {
                std::cout << "Missing critical TransformComponent for ProjectileEmitter" << std::endl;
            }
        }
        */

    sol::optional<sol::table> textLabelComponentNode = node["components"]["text"];

    if (textLabelComponentNode != sol::nullopt)
    {
        sol::table textLabel = node["components"]["text"];
        entity->AddComponent<TextLabelComponent>(
            static_cast<int>(textLabel["position"]["x"]),
            static_cast<int>(textLabel["position"]["y"]),
            textLabel["value"],
            textLabel["fontFamily"],
            WHITE_COLOR);
    }
}

EntityParser::EntityParser(AssetManager *assetManager, EntityManager *entityManager)
{
    this->assetManager = assetManager;
    this->entityManager = entityManager;
}

EntityParser::~EntityParser()
{
}

std::vector<Entity *> EntityParser::Parse(sol::table rootNode)
{
    std::vector<Entity *> entities;
    sol::optional<sol::table> opt = rootNode;
    if (opt = sol::nullopt)
    {
        std::cerr << "Could not find any root node for parsing entities" << std::endl;
        return entities;
    }

    for (int i = 0;; i++)
    {
        sol::optional<sol::table> opt = rootNode[i];
        if (opt == sol::nullopt)
        {
            break;
        }

        sol::table node = rootNode[i];
        Entity *entity = new Entity(node["name"], static_cast<LayerType>(node["layer"]));
        AddComponentsToEntity(entity, node["components"]);
        entities.push_back(entity);
    }

    std::cerr << "Successfully parsed " << entities.size() << " entities" << std::endl;

    return entities;
}