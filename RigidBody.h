#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>
#include "Colliders.h"

class RigidBody : public virtual Component
{
public:
	glm::vec2 position;
	glm::vec2 linearVelocity;
	float angle;
	float angularVelocity;

	glm::vec2 force;

	const float density = 0;
	const float mass = 0;
	const float restitution = 0;

	const bool isStatic = false;

	void update() override;
	void cleanup() const override;
	void physicsUpdate(float deltaTime);
	RigidBody(Collider& collider, glm::vec2 position, const float density, const float restitution, const bool isStatic);


	void move(glm::vec2 moveVec);

	Collider& collider;
};


#endif // !RIGIDBODY_H



