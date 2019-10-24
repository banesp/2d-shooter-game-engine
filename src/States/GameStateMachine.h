#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "../States/GameState.h"
#include <vector>

class GameStateMachine
{
private:
    std::vector<GameState *> states;
public:
    GameStateMachine() {}
    ~GameStateMachine() {}
    
    void ChangeState(GameState *state);
    void PushState(GameState *state);
    void PopState();

    void Update(float deltaTime);
    void Render();
    void Destroy();
};

#endif