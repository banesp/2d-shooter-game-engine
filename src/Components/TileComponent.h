#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "../Game.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>

class TileComponent : public Component
{
private:
    SDL_Texture *texture = nullptr;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    glm::vec2 position;

public:
    TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, SDL_Texture *texture);
    ~TileComponent();

    void Update(float deltaTime);
    void Render();
};

#endif
