#ifndef SOUND_API_H
#define SOUND_API_H

#include <SDL2/SDL_mixer.h>

class SoundAPI
{
public:
    static Mix_Chunk *LoadSound(const char *filename);
    static void PlaySound(Mix_Chunk *chunk, int loop);
};

#endif