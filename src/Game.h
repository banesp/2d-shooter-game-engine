#ifndef GAME_H
#define GAME_H

#include "./AssetManager.h"
#include "./EntityManager.h"
#include "./States/GameStateMachine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class AssetManager;
class EntityManager;

class Game
{
private:
    bool isRunning = false;
    int ticksLastFrame = 0;

    SDL_Window *window = nullptr;
    GameStateMachine *gameStateMachine = nullptr;

public:
    static SDL_Rect camera;
    static AssetManager *assetManager;
    static EntityManager *entityManager;
    static SDL_Renderer *renderer;
    static SDL_Event event;

    Game();
    ~Game();

    bool IsRunning() const;
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};

#endif
