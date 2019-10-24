#ifndef MAIN_MENU_STATE
#define MAIN_MENU_STATE

#include "../States/GameState.h"

class MainMenuState : public GameState
{
private:
public:
    MainMenuState();
    ~MainMenuState();

    void Initialize();
    void ProcessInput();
    void Update(float deltaTime);
    void Render();
    void Destroy();
};

#endif