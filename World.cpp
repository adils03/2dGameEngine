#include "World.h"

World::World(float gravityAmount) : bodyCount(0)
{
	gravity = glm::vec2(0, -gravityAmount);
}

void World::AddBody(RigidBody& body)
{
	bodies.push_back(body);
}

void World::RemoveBody(RigidBody& body)
{
	
}

void World::Update(float deltaTime)
{
	for (size_t i = 0; i < bodies.size();i++) {
		bodies[i].physicsUpdate(deltaTime);
	}
	for (size_t i = 0;i < bodies.size() - 1;i++) {
		RigidBody& bodyA = bodies[i];

		for (size_t j = i + 1;j < bodies.size();j++) {
			RigidBody& bodyB = bodies[j];

			glm::vec2 normal = glm::vec2();
			float depth = 0;

			if (Collide(bodyA, bodyB, normal, depth)) {
				bodyA.move(-normal * depth / 2.0f);
				bodyB.move(normal * depth / 2.0f);
			}
		}
	}
}

bool World::Collide(RigidBody& bodyA, RigidBody& bodyB, glm::vec2& normal, float& depth)
{
	normal = glm::vec2();
	depth = 0;

	ColliderType typeA = bodyA.collider.GetType();
	ColliderType typeB = bodyB.collider.GetType();

	Collider& colliderA = bodyA.collider;
	Collider& colliderB = bodyB.collider;

	if (typeA == ColliderType::Box) {
		if (typeB == ColliderType::Box) {
			const BoxCollider& a = dynamic_cast<const BoxCollider&>(colliderA);
			const BoxCollider& b = dynamic_cast<const BoxCollider&>(colliderB);
			return Collisions::IntersectPolygons(a.position,b.position,a.getVertices(),b.getVertices(), normal, depth);
		}
		else if (typeB == ColliderType::Circle) {
			const BoxCollider& a = dynamic_cast<const BoxCollider&>(colliderA);
			const CircleCollider& b = dynamic_cast<const CircleCollider&>(colliderB);
			return Collisions::IntersectCirclePolygon(b.position,b.getRadius(),a.position,a.getVertices(), normal, depth);
		}
	}
	else if (typeA == ColliderType::Circle) {
		if (typeB == ColliderType::Box) {
			const CircleCollider& a = dynamic_cast<const CircleCollider&>(colliderA);
			const BoxCollider& b = dynamic_cast<const BoxCollider&>(colliderB);
			return Collisions::IntersectCirclePolygon(a.position,a.getRadius(),b.position,b.getVertices(), normal, depth);
		}
		else if (typeB == ColliderType::Circle) {
			const CircleCollider& a = dynamic_cast<const CircleCollider&>(colliderA);
			const CircleCollider& b = dynamic_cast<const CircleCollider&>(colliderB);
			return Collisions::IntersectCircles(a.position,b.position,a.getRadius(),b.getRadius(), normal, depth);
		}
	}

	return false;
}
