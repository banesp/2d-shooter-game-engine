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
    // this->level->Initialize();
}

void PlayState::OnExitState()
{
    std::cout << "PlayState::OnExitState()" << std::endl;
    // this->level->Destroy();
}

void PlayState::ProcessInput(SDL_Event *event)
{
    std::cout << "1" << std::endl;
    std::cout << "2" << std::endl;
    std::cout << "3" << std::endl;

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
    std::cout << "PlayState::Update" << std::endl;
    this->level->Update(deltaTime);
}

void PlayState::Render()
{
    std::cout << "PlayState::Render" << std::endl;
    this->level->Render();
}

GameStateType PlayState::GetStateID() const
{
    return PLAY_STATE;
}