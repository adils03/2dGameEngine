#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Shader.h"
#include "Component.h"
#include <vector>
#include <algorithm>
#include "Transform.h"

class GameObject
{
public:
	GameObject(Shader& shader,Transform& transform);
	void update();
	void SortComponents();
	void addComponent(Component* component);
	void RemoveComponent(Component* component);
private:
	Shader& shader;
	Transform& transform;
	std::vector<Component*> components;
};


#endif // GAMEOBJECT_H