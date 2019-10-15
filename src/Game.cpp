#include "./Game.h"
#include "./Constants.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/TextLabelComponent.h"
#include "./Components/ProjectileEmitterComponent.h"
#include "../lib/glm/glm.hpp"
#include <iostream>

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;
Entity* player = NULL;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return;
    }
    if (TTF_Init() != 0) {        
        std::cerr << "Error initializing SDL TTF: " << TTF_GetError() << std::endl;
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        std::cerr << "Error initializing SDL Mixer: " << Mix_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(1);

    isRunning = true;

    return;
}

// Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber) {    
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    std::string levelName = "Level" + std::to_string(levelNumber);
    lua.script_file("./assets/scripts/" + levelName + ".lua");

    /*********************************************/
    /* LOADS ASSETS FROM LUA CONFIG FILE         */
    /*********************************************/
    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];
 
    for (int i = 0;; i++) {
        sol::optional<sol::table> node = levelAssets[i]; 
        
        if (node == sol::nullopt) {
            break;
        }

        std::string assetType       = levelAssets[i]["type"];
        std::string assetId         = levelAssets[i]["id"];
        std::string assetFilePath   = levelAssets[i]["file"];

        if (assetType.compare("texture") == 0) {
            assetManager->AddTexture(assetId, assetFilePath.c_str());
        } 
        else if (assetType.compare("font") == 0) {
            assetManager->AddFont(assetId, assetFilePath.c_str(), static_cast<int>(levelAssets[i]["fontSize"]));
        }
        else if (assetType.compare("sound") == 0) {
            assetManager->AddSound(assetId, assetFilePath.c_str());
        } else {
            std::cout << "Tried to load an asset with unknown type: " << assetType << std::endl;
        }
    }

    /*********************************************/
    /* LOADS MAP FROM LUA CONFIG FILE            */
    /*********************************************/
    map = new Map(
        levelData["map"]["textureAssetId"],
        static_cast<int>(levelData["map"]["scale"]),
        static_cast<int>(levelData["map"]["tileSize"])
    );
    map->LoadMap(
        levelData["map"]["file"],
        static_cast<int>(levelData["map"]["mapSizeX"]),
        static_cast<int>(levelData["map"]["mapSizeY"])
    );

    /*********************************************/
    /* LOADS ENTITIES FROM LUA CONFIG FILE       */
    /*********************************************/
    sol::table levelEntitiesNode = levelData["entities"];

    for (int i = 0; i < 40; i++) {
        
        sol::optional<sol::table> node = levelEntitiesNode[i];    
        if (node == sol::nullopt) {
            break;
        }
        
        Entity& entity(manager.AddEntity(
            levelEntitiesNode[i]["name"],
            static_cast<LayerType>(levelEntitiesNode[i]["layer"])
        ));

        // TODO: Sure ain't pretty
        if (entity.name == "player") {
            player = &entity;
        }

        sol::optional<sol::table> componentsNode = levelEntitiesNode[i]["components"];
        if (componentsNode == sol::nullopt) {
            std::cout << "Entity does not have any components.." << std::endl;
            break;
        }

        sol::optional<sol::table> transformComponentNode = levelEntitiesNode[i]["components"]["transform"];
        if (transformComponentNode != sol::nullopt) {
            std::cout << "Adding TransformComponent to entity: " << entity.name << std::endl;
            // TODO: Null check nested objects
            sol::table transform = levelEntitiesNode[i]["components"]["transform"];            
            entity.AddComponent<TransformComponent>(
                static_cast<int>(transform["position"]["x"]),
                static_cast<int>(transform["position"]["y"]),
                static_cast<int>(transform["velocity"]["x"]),
                static_cast<int>(transform["velocity"]["x"]),
                static_cast<int>(transform["width"]),
                static_cast<int>(transform["height"]),
                static_cast<int>(transform["scale"])
            );
        }

        sol::optional<sol::table> spriteComponentNode = levelEntitiesNode[i]["components"]["sprite"];
        if (spriteComponentNode != sol::nullopt) {
            std::cout << "Adding SpriteComponent to entity: " << entity.name << std::endl;
            sol::table sprite = levelEntitiesNode[i]["components"]["sprite"];

            if (sprite["animated"]) {
                entity.AddComponent<SpriteComponent>(
                    sprite["textureAssetId"], 
                    static_cast<int>(sprite["frameCount"]),
                    static_cast<int>(sprite["animationSpeed"]),
                    static_cast<bool>(sprite["hasDirections"]),
                    static_cast<bool>(sprite["fixed"])
                );
            } else {
                entity.AddComponent<SpriteComponent>(
                    sprite["textureAssetId"],
                    false
                );
            }
        }

        sol::optional<sol::table> colliderComponentNode = levelEntitiesNode[i]["components"]["collider"];
        if(colliderComponentNode != sol::nullopt) {
            std::cout << "Adding ColliderComponent to entity: " << entity.name << std::endl;

            sol::table collider = levelEntitiesNode[i]["components"]["collider"];

            if (entity.HasComponent<TransformComponent>()) {
                entity.AddComponent<ColliderComponent>(
                    collider["tag"],
                    entity.GetComponent<TransformComponent>()->position.x,
                    entity.GetComponent<TransformComponent>()->position.y,
                    entity.GetComponent<TransformComponent>()->width,
                    entity.GetComponent<TransformComponent>()->height,
                    "collision-texture" // Hardcoded for now
                );
            } else {
                std::cout << "Could not add ColliderComponent because entity does not contain a TransformComponent" << std::endl;
            }      
        }

        sol::optional<sol::table> keyboardControlComponentNode = levelEntitiesNode[i]["components"]["input"];
        sol::optional<sol::table> keyboardControlInnerComponentNode = levelEntitiesNode[i]["components"]["input"]["keyboard"];
        if (keyboardControlComponentNode != sol::nullopt && keyboardControlInnerComponentNode != sol::nullopt) {
            std::cout << "Adding KeyboardControlComponent to entity: " << entity.name << std::endl;
            sol::table keyboardControl = levelEntitiesNode[i]["components"]["input"]["keyboard"];
            entity.AddComponent<KeyboardControlComponent>(
                keyboardControl["up"],
                keyboardControl["right"],
                keyboardControl["down"],
                keyboardControl["left"],
                keyboardControl["shoot"]
            );
        }

        sol::optional<sol::table> projectileEmitterComponentNode = levelEntitiesNode[i]["components"]["projectileEmitter"];
        if (projectileEmitterComponentNode != sol::nullopt) {
            std::cout << "Adding ProjectileEmitterComponent to entity" << std::endl;

            sol::table projectileEmitter = levelEntitiesNode[i]["components"]["projectileEmitter"];

            Entity& projectileEntity(manager.AddEntity("projectile", PROJECTILE_LAYER));

            if (entity.HasComponent<TransformComponent>()) {
                projectileEntity.AddComponent<TransformComponent>(
                    entity.GetComponent<TransformComponent>()->position.x + (entity.GetComponent<TransformComponent>()->width / 2),
                    entity.GetComponent<TransformComponent>()->position.y + (entity.GetComponent<TransformComponent>()->height / 2),
                    0,
                    0,
                    projectileEmitter["width"],
                    projectileEmitter["height"],
                    1
                );

                projectileEntity.AddComponent<ProjectileEmitterComponent>(
                    static_cast<int>(projectileEmitter["speed"]),
                    static_cast<int>(projectileEmitter["angle"]),
                    static_cast<int>(projectileEmitter["range"]),
                    static_cast<bool>(projectileEmitter["shouldLoop"])
                );

                std::string projectileTextureId = projectileEmitter["textureAssetId"];
                projectileEntity.AddComponent<SpriteComponent>(projectileTextureId);

                projectileEntity.AddComponent<ColliderComponent>(
                    "PROJECTILE",
                    entity.GetComponent<TransformComponent>()->position.x,
                    entity.GetComponent<TransformComponent>()->position.y,
                    projectileEmitter["width"],
                    projectileEmitter["height"]
                );

            } else {
                std::cout << "Missing critical TransformComponent for ProjectileEmitter" << std::endl;
            }
        }
    }


    // PLAY SOUND
    // SoundManager::PlaySound(assetManager->GetSound("blades-sound"), -1);

    std::cout << "Finished loading: " << levelName << std::endl;
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
        }
        default: {
            break;
        }
    }
}

void Game::Update() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    float clampTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();

    manager.Update(clampTime);

    HandleCameraMovement();
    CheckCollisions();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement() {
    if (!player) {
        // std::cout << "Player not configured. Ignoring camera movement.." << std::endl;
        return;
    }

    TransformComponent* mainPlayerTransform = player->GetComponent<TransformComponent>();
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions() {    
    switch (manager.CheckCollisions())
    {
    case NO_COLLISION:
        //std::cout << "NO_COLLISION" << std::endl;
        break;
    case PLAYER_ENEMY_COLLISION:
        std::cout << "PLAYER_ENEMY_COLLISION" << std::endl;
        isRunning = false;
        break;
    case PLAYER_PROJECTILE_COLLISION:
        std::cout << "PLAYER_PROJECTILE_COLLISION" << std::endl;
        isRunning = false;
        break;
    case ENEMY_PROJECTILE_COLLISION:
        std::cout << "ENEMY_PROJECTILE_COLLISION" << std::endl;
        break;
    case PLAYER_VEGETATION_COLLISION:
        std::cout << "PLAYER_VEGETATION_COLLISION" << std::endl;
        break;
    case PLAYER_LEVEL_COMPLETE_COLLISION:
        isRunning = false;
        std::cout << "PLAYER_LEVEL_COMPLETE_COLLISION" << std::endl;
        break;
    default:
        break;
    }
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}
