#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "../States/GameState.h"
#include "../States/GameStateChanger.h"
#include "../Constants.h"
#include <SDL2/SDL.h>
#include <vector>

class GameStateMachine : public GameStateChanger
{
private:
    std::vector<GameState *> states;

public:
    GameStateMachine() {}
    ~GameStateMachine() {}

    void ChangeState(GameStateType t);

    void PushState(GameState *state);
    void PopState();

    void ProcessInput(SDL_Event event);
    void Update(float deltaTime);
    void Render();
    void Destroy();
};

#endif