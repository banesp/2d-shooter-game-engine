#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "../Game.h"
#include "../Level.h"
#include "../EntityManager.h"
#include "../Engine/TextureAPI.h"
#include "../AssetManager.h"
#include "../States/PlayState.h"
#include "../Components/TransformComponent.h"
#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>

class ColliderComponent : public Component
{
public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    SDL_Texture *texture = nullptr;
    TransformComponent *transform = nullptr;
    bool showTexture;

    ColliderComponent(std::string colliderTag, int x, int y, int width, int height)
    {
        this->colliderTag = colliderTag;
        this->collider = {x, y, width, height};
    }

    ColliderComponent(std::string colliderTag, int x, int y, int width, int height, std::string assetTextureId)
    {
        this->colliderTag = colliderTag;
        this->collider = {x, y, width, height};
        SetTexture(assetTextureId);
    }

    void SetTexture(std::string assetTextureId)
    {
        // TODO
        //this->texture = Game::assetManager->GetTexture(assetTextureId);
    }

    void Initialize() override
    {
        if (owner->HasComponent<TransformComponent>())
        {
            showTexture = true;
            transform = owner->GetComponent<TransformComponent>();
            sourceRectangle = {0, 0, transform->width, transform->height};
            destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
        }
    }

    void Update(float deltaTime) override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);

        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;

        // TODO: Should pass in camera SDL_Rect instead of this
        destinationRectangle.x = collider.x - Game::camera.x;
        destinationRectangle.y = collider.y - Game::camera.y;

        // Toggle collider texture with the 'c' key
        // Just hardcoded for the moment.
        if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_c)
            {
                showTexture = !showTexture;
            }
        }
    }

    void Render() override
    {
        if (texture)
        {
            if (showTexture)
            {
                TextureAPI::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
            }
        }
    }
};

#endif