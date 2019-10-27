#include "./Level.h"
#include "./Collision.h"
#include "./Components/TransformComponent.h"
#include "./Components/ColliderComponent.h"
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
    HandleCameraMovement();
    // CheckCollisions();
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
    std::vector<Entity *> entities = entityManager->GetEntities();
    std::cout << "Number of entities: " << entities.size() << std::endl;

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
