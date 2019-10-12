#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Components/TransformComponent.h"

class ColliderComponent: public Component {
    public:
        std::string assetTextureId;
        std::string colliderTag;
		std::string toggleKey;
        SDL_Rect collider;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        SDL_Texture* texture;
		bool showTexture;
        TransformComponent* transform;

        ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
            this->colliderTag = colliderTag;
            this->collider = { x, y, width, height };
			this->toggleKey = toggleKey;
        }

        ColliderComponent(std::string colliderTag, int x, int y, int width, int height, std::string assetTextureId) {
            this->colliderTag = colliderTag;
            this->collider = { x, y, width, height };
            SetTexture(assetTextureId);
        }

        void SetTexture(std::string assetTextureId) {
			this->assetTextureId = assetTextureId;
            this->texture = Game::assetManager->GetTexture(assetTextureId);
        }

        void Initialize() override {
            if (owner->HasComponent<TransformComponent>()) {
				showTexture = true;
                transform = owner->GetComponent<TransformComponent>();
                sourceRectangle = { 0, 0, transform->width, transform->height };
                destinationRectangle = { collider.x, collider.y, collider.w, collider.h };
            }            
        }

        void Update(float deltaTime) override {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);

            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;

            destinationRectangle.x = collider.x - Game::camera.x;
            destinationRectangle.y = collider.y - Game::camera.y;

			// Toggle collider texture with the 'c' key
			// Just hardcoded for the moment.
			if (Game::event.type == SDL_KEYDOWN) {
				if (Game::event.key.keysym.sym == SDLK_c) {				
					showTexture = !showTexture;
                }
			}
        }

        void Render() override {
            if (texture) {
				//printf("sourceRectangle { x: %i, y: %i, w: %i, h: %i }\n", sourceRectangle.x, sourceRectangle.y, sourceRectangle.w, sourceRectangle.h);
				printf("%s --> { x: %i, y: %i, w: %i, h: %i }\n", owner->name.c_str(), collider.x, collider.y, collider.w, collider.h);

				if (showTexture) {
                	TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
				}
            }
        }
};

#endif