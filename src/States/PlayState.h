#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "./GameState.h"
#include "../Constants.h"
#include "../Level.h"
#include <SDL2/SDL.h>

class Level;

class PlayState: public GameState
{
private:
    Level *level = nullptr;

public:
    PlayState();
    virtual ~PlayState();

    virtual void OnEnterState();
    virtual void OnExitState();
    
    virtual void ProcessInput(SDL_Event event);
    virtual void Update(float deltaTime);
    virtual void Render();

    virtual GameStateType GetStateID() const;
};

#endif