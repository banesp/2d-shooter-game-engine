#include "../States/MainMenuState.h"
#include "../States/PlayState.h"
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
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_RETURN:
            std::cout << "Clicked the space key" << std::endl;
            this->gsm->ChangeState(new PlayState());
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
