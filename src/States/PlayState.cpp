#include "../States/PlayState.h"
#include "../Constants.h"
#include <iostream>

PlayState::PlayState(GameStateMachine *gsm)
{
    this->gsm = gsm;
    this->level = new Level();
    this->level->Initialize();
}

PlayState::~PlayState()
{
    this->level->Destroy();
    this->level = nullptr;
    this->gsm = nullptr;
}

void PlayState::OnEnterState()
{
    std::cout << "PlayState::OnEnterState()" << std::endl;
    //this->level->Initialize();
}

void PlayState::OnExitState()
{
    std::cout << "PlayState::OnExitState()" << std::endl;
    //this->level->Destroy();
}

void PlayState::ProcessInput(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "Clicked the escape key from PlayState" << std::endl;
            this->gsm->ChangeState(MAIN_MENU_STATE);
            break;
        default:
            level->ProcessInput();
            break;
        }
    }    
}

void PlayState::Update(float deltaTime)
{
    this->level->Update(deltaTime);
}

void PlayState::Render()
{
    this->level->Render();
}

GameStateType PlayState::GetStateID() const
{
    return PLAY_STATE;
}