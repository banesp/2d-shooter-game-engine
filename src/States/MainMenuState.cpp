#include "../States/MainMenuState.h"
#include "../Engine/SoundAPI.h"
#include "../Constants.h"
#include <iostream>
#include <string>

MainMenuState::MainMenuState(GameStateChanger *gameStateChanger)
{
    this->gameStateChanger = gameStateChanger;
    this->assetManager = new AssetManager();
    this->entityManager = new EntityManager();
    this->loader = new LevelLoader(this->assetManager, this->entityManager);
}

MainMenuState::~MainMenuState()
{
    gameStateChanger = nullptr;
}

void MainMenuState::OnEnterState()
{
    std::cout << "MainMenuState OnEnterState" << std::endl;

    this->loader->Load("MainMenu");

    for (auto &asset : this->loader->GetAssets())
    {
        if (asset->GetType().compare("texture") == 0)
        {
            this->assetManager->AddTexture(asset->GetId(), asset->GetFilePath().c_str());
        }
        else if (asset->GetType().compare("sound") == 0)
        {
            this->assetManager->AddSound(asset->GetId(), asset->GetFilePath().c_str());
            Mix_Chunk *sound = this->assetManager->GetSound(asset->GetId());
            SoundAPI::PlaySound(sound, 1);
        }
        else if (asset->GetType().compare("font") == 0)
        {
            this->assetManager->AddFont(asset->GetId(), asset->GetFilePath().c_str(), asset->GetFontSize());
        }
        else
        {
            std::cout << "Unknown asset type: " << asset->GetType() << std::endl;
        }
    }
}

void MainMenuState::OnExitState()
{
    std::cout << "MainMenuState OnExitState" << std::endl;
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
    std::cout << "Num entities: " << this->entityManager->GetEntityCount() << std::endl;

    this->entityManager->Update(deltaTime);
}

void MainMenuState::Render()
{
    this->entityManager->Render();
}

GameStateType MainMenuState::GetStateID() const
{
    return MAIN_MENU_STATE;
}
