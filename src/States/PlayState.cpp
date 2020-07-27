#include "../States/PlayState.h"
#include "../Constants.h"
#include <iostream>

PlayState::PlayState(GameStateChanger *gameStateChanger)
{
    this->assetManager = new AssetManager();
    this->entityManager = new EntityManager();
    this->gameStateChanger = gameStateChanger;
    this->level = new Level(this->assetManager, this->entityManager);
    this->level->Initialize();
}

PlayState::~PlayState()
{
    this->level->Destroy();
    this->level = nullptr;
    this->gameStateChanger = nullptr;
}

void PlayState::OnEnterState()
{
    std::cout << "PlayState::OnEnterState()" << std::endl;
}

void PlayState::OnExitState()
{
    std::cout << "PlayState::OnExitState()" << std::endl;
}

void PlayState::ProcessInput(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        std::cout << "Event type: " << event->type << std::endl;
        switch (event->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            std::cout << "Clicked the escape key from PlayState" << std::endl;
            this->gameStateChanger->ChangeState(MAIN_MENU_STATE);
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