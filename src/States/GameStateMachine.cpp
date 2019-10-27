#include "../States/GameStateMachine.h"

/**
 * Not a big fan of passing in state instances like this.
 * Shpuld use constant enum type instead. And do lazy-loading 
 * internally in the GSM.
 */
void GameStateMachine::ChangeState(GameState *state)
{
    if (!states.empty())
    {
        // TODO: Do nothing if back == state
        states.back()->OnEnterState();
        states.pop_back();
    }

    states.push_back(state);
    states.back()->OnEnterState();
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