#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../States/GameState.h"
#include "../States/GameStateChanger.h"
#include "../Data/LevelLoader.h"
#include "../Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class MainMenuState : public GameState
{
private:
    GameStateChanger *gameStateChanger;
    LevelLoader *loader;
    AssetManager *assetManager;
    EntityManager *entityManager;

public:
    MainMenuState(GameStateChanger *changer);
    virtual ~MainMenuState();

    virtual void OnEnterState();
    virtual void OnExitState();

    virtual void ProcessInput(SDL_Event *event);
    virtual void Update(float deltaTime);
    virtual void Render();

    virtual GameStateType GetStateID() const;
};

#endif