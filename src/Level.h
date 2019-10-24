#ifndef LEVEL_H
#define LEVEL_H

#include "./Entity.h"
#include "./Loader.h"
#include "./AssetManager.h"
#include "./EntityManager.h"

class Loader;
class AssetManager;

class Level {
    private:
        int score = 0;
        Entity* player = nullptr;
        
        static Loader* loader;
        
    public:
        static SDL_Rect camera;
        static AssetManager* assetManager;
        static EntityManager* entityManager;

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