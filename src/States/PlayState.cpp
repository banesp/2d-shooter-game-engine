#include "../States/PlayState.h"

PlayState::PlayState()
{
    this->level = new Level();
}

PlayState::~PlayState()
{
    this->level = nullptr;
}

void PlayState::Initialize()
{
    this->level->Initialize();
}

void PlayState::ProcessInput()
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

void PlayState::Destroy()
{
    this->level->Destroy();
}


GameStateType PlayState::GetStateID() const
{
    return PLAY_STATE;
}