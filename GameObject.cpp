#include "GameObject.h"

GameObject::GameObject(Shader& shader, Transform& transform)
    : shader(shader), transform(transform)
{
    addComponent(&shader);
    shader.setPriority(0);
    addComponent(&transform);
    transform.setPriority(1);
}

GameObject::~GameObject()
{
  
}

void GameObject::update()
{
    for (const auto& component : components) {
        component->update();
    }
}

void GameObject::SortComponents()
{
    std::sort(components.begin(), components.end(),
        [](Component* a, Component* b) {
            return a->getPriority() < b->getPriority();
        });
}

void GameObject::addComponent(Component* component)
{
    components.push_back(component);
    SortComponents();
}

void GameObject::RemoveComponent(Component* component)
{
    components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

