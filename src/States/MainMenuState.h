#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "../States/GameState.h"
#include "../States/GameStateChanger.h"
#include "../Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class MainMenuState : public GameState
{
private:
    GameStateChanger *gameStateChanger;
    TTF_Font *font;
    SDL_Texture *text;

public:
    MainMenuState(GameStateChanger *changer);
    virtual ~MainMenuState();

    virtual void OnEnterState();
    virtual void OnExitState();

    virtual void ProcessInput(SDL_Event event);
    virtual void Update(float deltaTime);
    virtual void Render();

    virtual GameStateType GetStateID() const;
};

#endif