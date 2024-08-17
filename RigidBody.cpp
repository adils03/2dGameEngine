#include "RigidBody.h"

RigidBody::RigidBody(Collider& collider, glm::vec2 position, const float density, const float restitution, const bool isStatic)
	: position(position), density(density), mass(density* collider.GetArea()), restitution(restitution), isStatic(isStatic), collider(collider)
{
	linearVelocity = glm::vec2();
	angle = 0;
	angularVelocity = 0;


	force = glm::vec2();
}

void RigidBody::move(glm::vec2 moveVec)
{
	collider.transform.Translate(moveVec);
}
void RigidBody::update()
{
}

void RigidBody::cleanup() const
{
}

void RigidBody::physicsUpdate(float deltaTime)
{
}


