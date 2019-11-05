#ifndef LEVEL_H
#define LEVEL_H

#include "./Engine/Entity.h"
#include "./Data/LevelLoader.h"
#include "./AssetManager.h"
#include "./EntityManager.h"

class LevelLoader;
class AssetManager;

class Level
{
private:
    int score = 0;
    Entity *player = nullptr;

    static LevelLoader *loader;

public:
/*
    static AssetManager *assetManager;
    static EntityManager *entityManager;
*/

    Level();
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