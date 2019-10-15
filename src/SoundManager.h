#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL2/SDL_mixer.h>
#include "./Game.h"

class SoundManager {
    public:
        static Mix_Chunk* LoadSound(const char* filename);
        static void PlaySound(Mix_Chunk* chunk, int loop);
};

#endif