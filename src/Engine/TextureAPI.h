#ifndef TEXTURE_API_H
#define TEXTURE_API_H

#include "../Game.h"
#include <SDL2/SDL.h>

class TextureAPI
{
public:
    static SDL_Texture *LoadTexture(const char *fileName);
    static void Draw(SDL_Texture *texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip);
};

#endif
