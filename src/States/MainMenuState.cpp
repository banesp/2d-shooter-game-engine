#include "../States/MainMenuState.h"
#include "../Constants.h"
#include <iostream>
#include <string>

MainMenuState::MainMenuState(GameStateMachine *gsm)
{
    this->gsm = gsm;
}

MainMenuState::~MainMenuState()
{
    gsm = nullptr;
}

void MainMenuState::OnEnterState()
{
    std::cout << "MainMenuState::OnEnterState()" << std::endl;
}

void MainMenuState::OnExitState()
{
    std::cout << "MainMenuState::OnExitState()" << std::endl;
}

void MainMenuState::ProcessInput(SDL_Event event)
{
    std::cout << "MainMenuState::ProcessInput" << std::endl;
    if (event.type == SDL_KEYDOWN)
    {
        std::cout << "MainMenuState::ProcessInput keydown" << std::endl;
        switch (event.key.keysym.sym)
        {
        case SDLK_RETURN:
            std::cout << "Clicked the return key from MainMenuState" << std::endl;
            this->gsm->ChangeState(PLAY_STATE);
            break;
        default:
            break;
        }
    }
}

void MainMenuState::Update(float deltaTime)
{
}

void MainMenuState::Render()
{
}

GameStateType MainMenuState::GetStateID() const
{
    return MAIN_MENU_STATE;
}
