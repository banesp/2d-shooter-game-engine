#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "../States/GameState.h"
#include "../Level.h"

class Level;

class PlayState : public GameState
{
private:
    Level *level = nullptr;

public:
    PlayState();
    virtual ~PlayState();

    void Initialize();
    void ProcessInput();
    void Update(float deltaTime);
    void Render();
    void Destroy();
};

#endif