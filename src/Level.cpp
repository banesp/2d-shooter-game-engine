#include "./Level.h"
#include "./Components/TransformComponent.h"
#include <iostream>

EntityManager *Level::entityManager = new EntityManager();
AssetManager *Level::assetManager = new AssetManager();
Loader *Level::loader = new Loader(assetManager, entityManager);
SDL_Rect Level::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

Level::Level()
{
    this->player = nullptr;
}

Level::~Level()
{
    entityManager = nullptr;
    assetManager = nullptr;
    loader = nullptr;
    player = nullptr;
}

void Level::Initialize()
{
    loader->LoadLevel("Level1");

    // Set player camera
    for (auto& entity : entityManager->GetEntities()) {
        if (entity->name == "player") {
            player = entity;
            return;
        }
    }
}

void Level::ProcessInput()
{
}

void Level::Update(float deltaTime)
{
    entityManager->Update(deltaTime);
    HandleCameraMovement();
    CheckCollisions();
}

void Level::Render()
{
    if (entityManager->HasNoEntities())
    {
        return;
    }

    entityManager->Render();
}

void Level::HandleCameraMovement()
{
    if (!player)
    {
        std::cout << "Sorry bud! No player here :/" << std::endl;
        return;
    }

    TransformComponent *mainPlayerTransform = player->GetComponent<TransformComponent>();
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Level::CheckCollisions()
{
    switch (entityManager->CheckCollisions())
    {
    case NO_COLLISION:
        break;
    case PLAYER_ENEMY_COLLISION:
        std::cout << "PLAYER_ENEMY_COLLISION" << std::endl;
        // TODO: Level failed
        break;
    case PLAYER_PROJECTILE_COLLISION:
        std::cout << "PLAYER_PROJECTILE_COLLISION" << std::endl;
        // TODO: Level failed
        break;
    case ENEMY_PROJECTILE_COLLISION:
        std::cout << "ENEMY_PROJECTILE_COLLISION" << std::endl;
        break;
    case PLAYER_VEGETATION_COLLISION:
        std::cout << "PLAYER_VEGETATION_COLLISION" << std::endl;
        break;
    case PLAYER_LEVEL_COMPLETE_COLLISION:
        std::cout << "PLAYER_LEVEL_COMPLETE_COLLISION" << std::endl;
        // TODO: Level finished, transition to main menu or new level
        break;
    default:
        break;
    }
}

void Level::Destroy()
{
    entityManager->ClearData();
    assetManager->ClearData();
}
