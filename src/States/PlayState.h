#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "../States/GameState.h"
#include "../States/GameStateChanger.h"
#include "../Constants.h"
#include "../AssetManager.h"
#include "../EntityManager.h"
#include "../Level.h"
#include <SDL2/SDL.h>

class Level;
class AssetManager;
class EntityManager;

class PlayState : public GameState
{
private:
    GameStateChanger *gameStateChanger = nullptr;
    Level *level = nullptr;
    
    EntityManager *entityManager = nullptr;
    AssetManager *assetManager = nullptr;

public:    
    PlayState(GameStateChanger *gameStateChanger);
    virtual ~PlayState();

    virtual void OnEnterState();
    virtual void OnExitState();

    virtual void ProcessInput(SDL_Event *event);
    virtual void Update(float deltaTime);
    virtual void Render();

    virtual GameStateType GetStateID() const;
};

#endif