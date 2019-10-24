#include "../States/GameStateMachine.h"

void GameStateMachine::ChangeState(GameState *state)
{
    if (!states.empty())
    {
        // TODO: Do nothing if back == state
        states.back()->Destroy();
        states.pop_back();
    }

    states.push_back(state);
    states.back()->Initialize();
}

void GameStateMachine::PushState(GameState *state)
{
    states.push_back(state);
    states.back()->Initialize();
}

void GameStateMachine::PopState()
{
    if (!states.empty())
    {
        states.back()->Destroy();
        states.pop_back();
    }

    // TODO: Resume
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
        states.back()->Destroy();
        delete states.back();
        states.clear();
    }
}