#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../Constants.h"

class GameState
{
private:
public:
    GameState()
    {
    }

    virtual ~GameState() {}

    virtual void Initialize() = 0;
    virtual void ProcessInput() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;

    virtual GameStateType GetStateID() const = 0;
};

#endif