#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "../States/GameState.h"
#include "../States/GameStateMachine.h"
#include "../Constants.h"
#include "../Callback.h"
#include <SDL2/SDL.h>

class MainMenuState : public GameState
{
private:
    GameStateMachine *gsm;

public:
    MainMenuState(GameStateMachine *gsm);
    virtual ~MainMenuState();

    virtual void OnEnterState();
    virtual void OnExitState();

    virtual void ProcessInput(SDL_Event event);
    virtual void Update(float deltaTime);
    virtual void Render();

    virtual GameStateType GetStateID() const;
};

#endif