#ifndef LEVEL_H
#define LEVEL_H

#include "./Engine/Entity.h"
#include "./Data/LevelLoader.h"
#include "./AssetManager.h"
#include "./EntityManager.h"

class LevelLoader;
class AssetManager;
class EntityManager;

class Level
{
private:
    int score = 0;
    Entity *player = nullptr;

    AssetManager *assetManager;
    EntityManager *entityManager;
    LevelLoader *loader;

public:

    Level();
    Level(AssetManager *assetManager, EntityManager *entityManager);
    ~Level();

    void Initialize();
    void SetPlayerCamera();
    void ProcessInput();
    void Update(float deltaTime);
    void Render();
    void Destroy();
    void HandleCameraMovement();
    void CheckCollisions();
};

#endif