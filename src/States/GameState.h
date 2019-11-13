#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../Constants.h"
#include <SDL2/SDL.h>

class GameState
{
private:
public:
    virtual ~GameState() {}

    virtual void OnEnterState() = 0;
    virtual void OnExitState() = 0;

    virtual void ProcessInput(SDL_Event *event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

    virtual GameStateType GetStateID() const = 0;
};

#endif