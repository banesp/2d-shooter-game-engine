#ifndef PROJECTILE_EMITTER_COMPONENT_H
#define PROJECTILE_EMITTER_COMPONENT_H

#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"

class ProjectileEmitterComponent: public Component {
    private:
        TransformComponent* transform;
        glm::vec2 origin;
        int speed = 0;
        int range = 0;
        float angleRad = 0.0;
        bool shouldLoop = false;

        void ResetTransformPosition() const {
            transform->position.x = origin.x;
            transform->position.y = origin.y;
        }

    public:
        ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop) {
            this->speed = speed;
            this->range = range;
            this->shouldLoop = shouldLoop;
            this->angleRad = glm::radians(static_cast<float>(angleDeg));
        }
        
        void Initialize() override {
            this->transform = owner->GetComponent<TransformComponent>();

            this->origin = glm::vec2(
                transform->position.x, 
                transform->position.y
            );

            this->transform->velocity = glm::vec2(
                glm::cos(angleRad) * speed, 
                glm::sin(angleRad) * speed
            );
        }

        void Update(float deltaTime) override {
            if (glm::distance(transform->position, origin) > range) {
                if (shouldLoop) {
                    ResetTransformPosition();
                } else {
                    owner->Destroy();
                }
            }
        }

        void Render() override {
            
        }
};

#endif