#include "../States/PlayState.h"
#include <iostream>

PlayState::PlayState()
{
    this->level = new Level();
}

PlayState::~PlayState()
{
    this->level = nullptr;
}

void PlayState::OnEnterState()
{
    std::cout << "PlayState::OnEnterState()" << std::endl;
    this->level->Initialize();
}

void PlayState::OnExitState()
{
    std::cout << "PlayState::OnExitState()" << std::endl;
    this->level->Destroy();
}

void PlayState::ProcessInput(SDL_Event event)
{
    level->ProcessInput();
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