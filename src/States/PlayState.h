#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "./GameState.h"
#include "../Constants.h"
#include "../Level.h"

class Level;

class PlayState: public GameState
{
private:
    Level *level = nullptr;

public:
    PlayState();
    virtual ~PlayState();

    virtual void Initialize();
    virtual void ProcessInput();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void Destroy();

    virtual GameStateType GetStateID() const;
};

#endif