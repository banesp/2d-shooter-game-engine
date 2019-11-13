#ifndef ENTITY_H
#define ENTITY_H

#include "../Constants.h"
#include "../EntityManager.h"
#include "../Engine/Component.h"
#include <vector>
#include <string>
#include <map>

class EntityManager;
class Component;

class Entity
{
private:
    bool isActive;
    std::vector<Component *> components;
    std::vector<Entity *> entities;
    std::map<const std::type_info *, Component *> componentTypeMap;

public:
    std::string name;
    LayerType layer;

    Entity();
    Entity(std::string name, LayerType layer);

    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;
    void ListAllComponents() const;

    void AddEntity(Entity *entity)
    {
        entities.emplace_back(entity);
    }

    template <typename T, typename... TArgs>
    T &AddComponent(TArgs &&... args)
    {
        T *newComponent(new T(std::forward<TArgs>(args)...));
        newComponent->owner = this;
        components.emplace_back(newComponent);
        componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->Initialize();
        return *newComponent;
    }

    template <typename T>
    bool HasComponent() const
    {
        return componentTypeMap.count(&typeid(T));
    }

    template <typename T>
    T *GetComponent()
    {
        return static_cast<T *>(componentTypeMap[&typeid(T)]);
    }
};

#endif
