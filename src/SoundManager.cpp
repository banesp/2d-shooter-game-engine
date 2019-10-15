#include "./SoundManager.h"

Mix_Chunk* SoundManager::LoadSound(const char* filename) {
    return Mix_LoadWAV(filename);
}

void SoundManager::PlaySound(Mix_Chunk* chunk, int loop) {
    Mix_PlayChannel(-1, chunk, loop);
}