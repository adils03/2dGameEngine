#include "Collider.h"

void Collider::update() const
{
}

void Collider::cleanup() const
{
}

Collider::Collider(Transform& transform, glm::vec2& position, const glm::vec2& sclVec) :
	transform(transform), position(position), scale(sclVec), rotation(0)
{
}
