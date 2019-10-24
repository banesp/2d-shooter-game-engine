#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState
{
private:
public:
    virtual ~GameState() {}
    virtual void Initialize() {}
    virtual void ProcessInput() {}
    virtual void Update(float deltaTime) {}
    virtual void Render() {}
    virtual void Destroy() {}
};

#endif