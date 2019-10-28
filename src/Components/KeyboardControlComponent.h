#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include "../Level.h"
#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/ProjectileEmitterComponent.h"

class ColliderComponent;

class KeyboardControlComponent : public Component
{
public:
    std::string upKey;
    std::string downKey;
    std::string rightKey;
    std::string leftKey;
    std::string shootKey;
    TransformComponent *transform = nullptr;
    SpriteComponent *sprite = nullptr;

    KeyboardControlComponent()
    {
    }

    KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey)
    {
        this->upKey = GetSDLKeyStringCode(upKey);
        this->rightKey = GetSDLKeyStringCode(rightKey);
        this->downKey = GetSDLKeyStringCode(downKey);
        this->leftKey = GetSDLKeyStringCode(leftKey);
        this->shootKey = GetSDLKeyStringCode(shootKey);
    }

    std::string GetSDLKeyStringCode(std::string key)
    {
        if (key.compare("up") == 0)
            return "1073741906";
        if (key.compare("down") == 0)
            return "1073741905";
        if (key.compare("left") == 0)
            return "1073741904";
        if (key.compare("right") == 0)
            return "1073741903";
        if (key.compare("space") == 0)
            return "32";
        return std::to_string(static_cast<int>(key[0]));
    }

    void Initialize() override
    {
        transform = owner->GetComponent<TransformComponent>();
        sprite = owner->GetComponent<SpriteComponent>();
    }

    void Update(float deltaTime) override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);
            if (keyCode.compare(upKey) == 0)
            {
                transform->velocity.y = -40;
                transform->velocity.x = 0;
                sprite->Play("UpAnimation");
            }
            if (keyCode.compare(rightKey) == 0)
            {
                transform->velocity.y = 0;
                transform->velocity.x = 40;
                sprite->Play("RightAnimation");
            }
            if (keyCode.compare(downKey) == 0)
            {
                transform->velocity.y = 40;
                transform->velocity.x = 0;
                sprite->Play("DownAnimation");
            }
            if (keyCode.compare(leftKey) == 0)
            {
                transform->velocity.y = 0;
                transform->velocity.x = -40;
                sprite->Play("LeftAnimation");
            }
            if (keyCode.compare(shootKey) == 0)
            {
                // TODO: Should read projectile data from script file
                Entity &projectile(Game::entityManager->AddEntity("projectile", PROJECTILE_LAYER));

                int angle = 270;
                if (sprite->GetCurrentAnimationName().compare("RightAnimation") == 0)
                {
                    angle = 0;
                }
                else if (sprite->GetCurrentAnimationName().compare("DownAnimation") == 0)
                {
                    angle = 90;
                }
                else if (sprite->GetCurrentAnimationName().compare("LeftAnimation") == 0)
                {
                    angle = 180;
                }

                projectile.AddComponent<TransformComponent>(
                    transform->position.x + (transform->width / 2),
                    transform->position.y + (transform->height / 2),
                    0,
                    0,
                    4,
                    4,
                    1);

                projectile.AddComponent<SpriteComponent>("projectile-texture");

                projectile.AddComponent<ProjectileEmitterComponent>(100, angle, 1000, false);

                projectile.AddComponent<ColliderComponent>("FRIENDLY_PROJECTILE", transform->position.x, transform->position.y, 4, 4);
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);
            if (keyCode.compare(upKey) == 0)
            {
                transform->velocity.y = 0;
            }
            if (keyCode.compare(rightKey) == 0)
            {
                transform->velocity.x = 0;
            }
            if (keyCode.compare(downKey) == 0)
            {
                transform->velocity.y = 0;
            }
            if (keyCode.compare(leftKey) == 0)
            {
                transform->velocity.x = 0;
            }
        }
    }
};

#endif
