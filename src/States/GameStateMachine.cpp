#include "../States/GameStateMachine.h"
#include "../States/MainMenuState.h"
#include "../States/PlayState.h"

// WIP: State swapping needs some tweaking to work optimally
// Should not initialize a new state if GSM already has that state in vector
void GameStateMachine::ChangeState(GameStateType t)
{
    std::cout << "Size of states vector: " << states.size() << std::endl;

    if (!states.empty())
    {
        if (states.back()->GetStateID() == t)
        {
            return;
        }

        states.back()->OnExitState();
        states.pop_back();
    }

    switch (t)
    {
    case MAIN_MENU_STATE:
        std::cout << "Changing state to MainMenuState" << std::endl;
        states.push_back(new MainMenuState(this));
        states.back()->OnEnterState();
        break;
    case PLAY_STATE:
        std::cout << "Changing state to PlayState" << std::endl;
        states.push_back(new PlayState(this));
        states.back()->OnEnterState();
        break;
    default:
        std::cout << "Changing state to default" << std::endl;
        break;
    }
}

void GameStateMachine::PushState(GameState *state)
{
    states.push_back(state);
    states.back()->OnEnterState();
}

void GameStateMachine::PopState()
{
    if (!states.empty())
    {
        states.back()->OnExitState();
        states.pop_back();
    }

    // TODO: Resume
}

void GameStateMachine::ProcessInput(SDL_Event event)
{
    if (!states.empty())
    {
        states.back()->ProcessInput(event);
    }
}

void GameStateMachine::Update(float deltaTime)
{
    if (!states.empty())
    {
        states.back()->Update(deltaTime);
    }
}

void GameStateMachine::Render()
{
    if (!states.empty())
    {
        states.back()->Render();
    }
}

void GameStateMachine::Destroy()
{
    if (!states.empty())
    {
        states.back()->OnExitState();
        delete states.back();
    }

    states.clear();
}