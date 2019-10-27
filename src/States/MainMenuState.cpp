#include "../States/MainMenuState.h"
#include "../Engine/FontManager.h"
#include "../Constants.h"
#include <iostream>
#include <string>

MainMenuState::MainMenuState(GameStateChanger *gameStateChanger)
{
    this->gameStateChanger = gameStateChanger;
    this->font = FontManager::LoadFont("./assets/fonts/charriot.ttf", 16);
    if (!this->font)
    {
        std::cerr << "Could not load Charriot font: " << TTF_GetError() << std::endl;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, "", WHITE_COLOR);
    this->text = SDL_CreateTextureFromSurface(Game::renderer, surface);
}

MainMenuState::~MainMenuState()
{
    gameStateChanger = nullptr;    
    font = nullptr;
}

void MainMenuState::OnEnterState()
{
}

void MainMenuState::OnExitState()
{
}

void MainMenuState::ProcessInput(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
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
    SDL_Rect rect = SDL_Rect{x : 0, y : 0, w : 100, h : 100};
    SDL_RenderCopy(Game::renderer, this->text, NULL, &rect);
}

GameStateType MainMenuState::GetStateID() const
{
    return MAIN_MENU_STATE;
}
