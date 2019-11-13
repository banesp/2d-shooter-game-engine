#include "./Level.h"
#include "./Engine/Collision.h"
#include "./Components/TransformComponent.h"
#include "./Components/ColliderComponent.h"
#include <iostream>

// SDL_Rect Level::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

Level::Level(AssetManager *assetManager, EntityManager *entityManager)
{
    this->assetManager = assetManager;
    this->entityManager = entityManager;
    this->player = nullptr;
    this->loader = new LevelLoader(assetManager, entityManager);
}

Level::~Level()
{
    loader = nullptr;
    player = nullptr;
    assetManager = nullptr;
    entityManager = nullptr;
}

void Level::Initialize()
{
    loader->Load("Level1");
}

void Level::SetPlayerCamera()
{
    for (auto &entity : entityManager->GetEntities())
    {
        if (entity->name == "player")
        {
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
    //HandleCameraMovement();
    //CheckCollisions();
}

void Level::Render()
{
    entityManager->Render();
}

void Level::HandleCameraMovement()
{
    if (!player)
    {
        return;
    }

    TransformComponent *mainPlayerTransform = player->GetComponent<TransformComponent>();
    // TODO: This should be level instead
    Game::camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    Game::camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);
    Game::camera.x = Game::camera.x < 0 ? 0 : Game::camera.x;
    Game::camera.y = Game::camera.y < 0 ? 0 : Game::camera.y;
    Game::camera.x = Game::camera.x > Game::camera.w ? Game::camera.w : Game::camera.x;
    Game::camera.y = Game::camera.y > Game::camera.h ? Game::camera.h : Game::camera.y;
}

void Level::CheckCollisions()
{
    std::vector<Entity *> entities = entityManager->GetEntities();

    for (int i = 0; i < entities.size() - 1; i++)
    {
        if (!entities[i]->HasComponent<ColliderComponent>())
        {
            continue;
        }

        ColliderComponent *thisCollider = entities[i]->GetComponent<ColliderComponent>();

        for (int j = i + 1; j < entities.size(); j++)
        {
            if (!entities[j]->HasComponent<ColliderComponent>())
            {
                continue;
            }

            ColliderComponent *otherCollider = entities[j]->GetComponent<ColliderComponent>();

            if (!Collision::CheckRectangleCollision(thisCollider->collider, otherCollider->collider))
            {
                continue;
            }

            if ((thisCollider->colliderTag.compare("PLAYER") == 0 && otherCollider->colliderTag.compare("ENEMY") == 0))
            {
                // U ded
            }
            if ((thisCollider->colliderTag.compare("ENEMY") == 0 && otherCollider->colliderTag.compare("PLAYER") == 0))
            {
                // U ded
            }

            if ((thisCollider->colliderTag.compare("PLAYER") == 0 && otherCollider->colliderTag.compare("PROJECTILE") == 0))
            {
                // U half-ded
            }
            if ((thisCollider->colliderTag.compare("PROJECTILE") == 0 && otherCollider->colliderTag.compare("PLAYER") == 0))
            {
                // U half-ded
            }

            if ((thisCollider->colliderTag.compare("ENEMY") == 0 && otherCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0))
            {
                entities[i]->Destroy();
                entities[j]->Destroy();
                score += 100;
            }
            if ((thisCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0 && otherCollider->colliderTag.compare("ENEMY") == 0))
            {
                entities[i]->Destroy();
                entities[j]->Destroy();
                score += 100;
            }

            if ((thisCollider->colliderTag.compare("PLAYER") == 0 && otherCollider->colliderTag.compare("LEVEL_COMPLETE") == 0))
            {
            }
            if ((thisCollider->colliderTag.compare("LEVEL_COMPLETE") == 0 && otherCollider->colliderTag.compare("PLAYER") == 0))
            {
            }
        }
    }
}

void Level::Destroy()
{
    entityManager->ClearData();
    assetManager->ClearData();
}
