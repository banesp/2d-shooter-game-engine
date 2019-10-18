#include "./AssetManager.h"
#include "./Components/TransformComponent.h"

AssetManager::AssetManager() {
}

void AssetManager::ClearData() {
    std::map<std::string, SDL_Texture*>::iterator textureIterator;
    for (textureIterator = textures.begin(); textureIterator != textures.end(); textureIterator++ ) {
        SDL_DestroyTexture(textureIterator->second);
        textureIterator->second = nullptr;
    }

    textures.clear();

    std::map<std::string, TTF_Font*>::iterator fontsIterator;
    for (fontsIterator = fonts.begin(); fontsIterator != fonts.end(); fontsIterator++ ) {    
        TTF_CloseFont(fontsIterator->second);
        fontsIterator->second = nullptr;
    }

    fonts.clear();

    std::map<std::string, Mix_Chunk*>::iterator soundsIterator;
    for (soundsIterator = sounds.begin(); soundsIterator != sounds.end(); soundsIterator++ ) {    
        Mix_FreeChunk(soundsIterator->second);
        fontsIterator->second = nullptr;
    }
    
    sounds.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return textures[textureId];
}

void AssetManager::AddFont(std::string fontId, const char* fileName, int fontSize) {
    fonts.emplace(fontId, FontManager::LoadFont(fileName, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontId) {
    return fonts[fontId];
}

void AssetManager::AddSound(std::string soundId, const char* filePath) {
    sounds.emplace(soundId, SoundManager::LoadSound(filePath));
}

Mix_Chunk* AssetManager::GetSound(std::string soundId) {
    return sounds[soundId];
}
