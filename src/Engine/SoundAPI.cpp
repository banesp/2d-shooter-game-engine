#include "../Engine/SoundAPI.h"

Mix_Chunk *SoundAPI::LoadSound(const char *filename)
{
    return Mix_LoadWAV(filename);
}

void SoundAPI::PlaySound(Mix_Chunk *chunk, int loop)
{
    Mix_PlayChannel(-1, chunk, loop);
}