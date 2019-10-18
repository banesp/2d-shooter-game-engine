#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <SDL2/SDL.h>
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../../lib/glm/glm.hpp"

class TileComponent: public Component {
    public:
        SDL_Texture *texture = nullptr;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        glm::vec2 position;

        // TODO: Pass in assetManager/texture rectangle instead of this
        TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId) {
            texture = Level::assetManager->GetTexture(assetTextureId);

            sourceRectangle.x = sourceRectX;
            sourceRectangle.y = sourceRectY;
            sourceRectangle.w = tileSize;
            sourceRectangle.h = tileSize;

            destinationRectangle.x = x;
            destinationRectangle.y = y;
            destinationRectangle.w = tileSize * tileScale;
            destinationRectangle.h = tileSize * tileScale;

            position.x = x;
            position.y = y;
        }

        ~TileComponent() {
            SDL_DestroyTexture(texture);
        }

        // TODO: Pass in camera rectangle instead of this
        void Update(float deltaTime) override {
            destinationRectangle.x = position.x - Level::camera.x;
            destinationRectangle.y = position.y - Level::camera.y;
        }

        void Render() override {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
        }
};

#endif
