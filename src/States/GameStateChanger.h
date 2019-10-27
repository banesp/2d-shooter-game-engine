#ifndef GAME_STATE_CHANGER_H
#define GAME_STATE_CHANGER_H

#include "../Constants.h"

class GameStateChanger
{
public:
    virtual void ChangeState(GameStateType t) = 0;
};

#endif