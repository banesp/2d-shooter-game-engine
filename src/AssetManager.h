#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "./EntityManager.h"
#include "./Engine/FontManager.h"
#include "./Engine/TextureAPI.h"
#include "./Engine/SoundAPI.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

class AssetManager
{
private:
    std::map<std::string, SDL_Texture *> textures;
    std::map<std::string, TTF_Font *> fonts;
    std::map<std::string, Mix_Chunk *> sounds;

public:
    AssetManager();
    ~AssetManager();

    void ClearData();

    void AddTexture(std::string textureId, const char *filePath);
    SDL_Texture *GetTexture(std::string textureId);

    void AddFont(std::string fontId, const char *filePath, int fontSize);
    TTF_Font *GetFont(std::string fontId);

    void AddSound(std::string soundId, const char *filePath);
    Mix_Chunk *GetSound(std::string soundId);
};

#endif
