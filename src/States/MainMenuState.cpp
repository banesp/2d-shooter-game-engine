#include "../States/MainMenuState.h"
#include "../Constants.h"
#include <iostream>
#include <string>

MainMenuState::MainMenuState(GameStateChanger *gameStateChanger)
{
    this->gameStateChanger = gameStateChanger;
}

MainMenuState::~MainMenuState()
{
    gameStateChanger = nullptr;
}

void MainMenuState::OnEnterState()
{
}

void MainMenuState::OnExitState()
{
}

void MainMenuState::ProcessInput(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RETURN:
            this->gameStateChanger->ChangeState(PLAY_STATE);
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
