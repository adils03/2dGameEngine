#ifndef WORLD_H
#define WORLD_H

#include "RigidBody.h"
#include "Collisions.h"
#include "Colliders.h"

class World
{
public:
	int bodyCount;

	std::vector<RigidBody> bodies;
	glm::vec2 gravity;

	World(float gravityAmount);
	void AddBody(RigidBody& body);
	void RemoveBody(RigidBody& body);

	void Update(float deltaTime);
	bool Collide(RigidBody& bodyA, RigidBody& bodyB, glm::vec2& normal, float& depth);


};


#endif // !WORLD_H





