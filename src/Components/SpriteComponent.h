#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../Game.h"
#include "../AssetManager.h"
#include "../Level.h"
#include "../States/PlayState.h"
#include "../Engine/TextureAPI.h"
#include "../Engine/Animation.h"
#include <SDL2/SDL.h>

class SpriteComponent : public Component
{
private:
    TransformComponent *transform = nullptr;
    SDL_Texture *texture = nullptr;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    bool isAnimated;
    int numFrames;
    int animationSpeed;
    bool isFixed;
    std::map<std::string, Animation> animations;
    std::string currentAnimationName;
    unsigned int animationIndex = 0;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(SDL_Texture *texture)
    {
        this->texture = texture;
        this->isFixed = false;
        this->isAnimated = false;
    }

    SpriteComponent(SDL_Texture *texture, bool isFixed)
    {
        this->texture = texture;
        this->isFixed = isFixed;
        this->isAnimated = false;
    }

    SpriteComponent(SDL_Texture *texture, int numFrames, int animationSpeed, bool hasDirections, bool isFixed)
    {
        this->isAnimated = true;
        this->numFrames = numFrames;
        this->animationSpeed = animationSpeed;
        this->isFixed = isFixed;

        if (hasDirections)
        {
            Animation downAnimation = Animation(0, numFrames, animationSpeed);
            Animation rightAnimation = Animation(1, numFrames, animationSpeed);
            Animation leftAnimation = Animation(2, numFrames, animationSpeed);
            Animation upAnimation = Animation(3, numFrames, animationSpeed);
            animations.emplace("DownAnimation", downAnimation);
            animations.emplace("RightAnimation", rightAnimation);
            animations.emplace("LeftAnimation", leftAnimation);
            animations.emplace("UpAnimation", upAnimation);
            this->animationIndex = 0;
            this->currentAnimationName = "DownAnimation";
        }
        else
        {
            Animation singleAnimation = Animation(0, numFrames, animationSpeed);
            animations.emplace("SingleAnimation", singleAnimation);
            this->animationIndex = 0;
            this->currentAnimationName = "SingleAnimation";
        }

        Play(this->currentAnimationName);
        this->texture = texture;
    }

    void Play(std::string animationName)
    {
        numFrames = animations[animationName].numFrames;
        animationIndex = animations[animationName].index;
        animationSpeed = animations[animationName].animationSpeed;
        currentAnimationName = animationName;
    }

    void Initialize() override
    {
        transform = owner->GetComponent<TransformComponent>();
        sourceRectangle.x = 0;
        sourceRectangle.y = 0;
        sourceRectangle.w = transform->width;
        sourceRectangle.h = transform->height;
    }

    void Update(float deltaTime) override
    {
        if (isAnimated)
        {
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
        }
        sourceRectangle.y = animationIndex * transform->height;
        destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x); // TODO: Wrong camera
        destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y); // TODO: Wrong camera
        destinationRectangle.w = transform->width * transform->scale;
        destinationRectangle.h = transform->height * transform->scale;
    }

    void Render() override
    {
        TextureAPI::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
    }

    std::string GetCurrentAnimationName()
    {
        return this->currentAnimationName;
    }
};

#endif
