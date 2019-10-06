#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../AssetManager.h"
#include "../TextureManager.h"

class TileComponent: public Component {
    public:
        SDL_Texture* texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        glm::vec2 position;

        TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId) {
            texture = Game::assetManager->GetTexture(assetTextureId);
            
            this->sourceRectangle.x = sourceRectX;
            this->sourceRectangle.y = sourceRectY;
            this->sourceRectangle.w = tileSize;
            this->sourceRectangle.h = tileSize;

            this->destinationRectangle.x = x;
            this->destinationRectangle.y = y;
            this->destinationRectangle.w = tileSize * tileScale;
            this->destinationRectangle.h = tileSize * tileScale;

            this->position.x = x;
            this->position.y = y;
        }

        ~TileComponent() {
            SDL_DestroyTexture(texture);
        }

        void Update(float deltaTime) override {            
            destinationRectangle.x = position.x - Game::camera.x;
            destinationRectangle.y = position.y - Game::camera.y;
        }

        void Render() override {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
        }
};

#endif