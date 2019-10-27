#include "./Game.h"
#include "./Constants.h"
#include "./States/PlayState.h"
#include "./States/MainMenuState.h"
#include <iostream>

SDL_Renderer *Game::renderer;
SDL_Event Game::event;

Game::Game()
{
    this->isRunning = false;
    this->gameStateMachine = new GameStateMachine();
}

Game::~Game()
{
    this->window = nullptr;
    this->gameStateMachine = nullptr;
    Game::renderer = nullptr;
}

bool Game::IsRunning() const
{
    return this->isRunning;
}

void Game::Initialize(int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return;
    }

    if (TTF_Init() != 0)
    {
        std::cerr << "Error initializing SDL TTF: " << TTF_GetError() << std::endl;
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
    {
        std::cerr << "Error initializing SDL Mixer: " << Mix_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    // TODO
    gameStateMachine->PushState(new MainMenuState(gameStateMachine));

    isRunning = true;
}

void Game::ProcessInput()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
    {
        isRunning = false;
        break;
    }
    default:
    {
        this->gameStateMachine->ProcessInput(event);
    }
    }
}

void Game::Update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME))
    {
    }

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    float clampTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();
    gameStateMachine->Update(clampTime);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    gameStateMachine->Render();
    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    gameStateMachine->Destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}
