#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "../States/GameState.h"
#include "../Constants.h"

class MainMenuState: public GameState
{
private:
public:
    MainMenuState();
    virtual ~MainMenuState();

    virtual GameStateType GetStateID() const;

    virtual void Initialize();
    virtual void ProcessInput();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void Destroy();
};

#endif