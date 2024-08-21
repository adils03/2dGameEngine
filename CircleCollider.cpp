#include "CircleCollider.h"
#include <iostream>

CircleCollider::CircleCollider(Transform& transform)
    : Collider(transform, transform.position, transform.rotation, transform.scale), radius(std::max(transform.scale.x, transform.scale.y)/2-1)
{
    positionOffset = transform.position - position;
    rotationOffset = transform.rotation - rotation;
    scaleOffset = transform.scale / scale;
}


void CircleCollider::update() {
    position = transform.position - positionOffset;
    rotation = transform.rotation - rotationOffset;
}

void CircleCollider::cleanup() const {
    std::cout << "Cleaning up CircleCollider" << std::endl;
}

float CircleCollider::GetArea() const
{
    return glm::pi<float>() * radius *radius;
}

ColliderType CircleCollider::GetType() const
{
    return ColliderType::Circle;
}

void CircleCollider::Translate(const glm::vec2& moveVec) {
    positionOffset += moveVec;
}

void CircleCollider::Rotate(float angle) {
    rotationOffset += angle;
}

void CircleCollider::Scale(const glm::vec2& sclVec) {
    if (sclVec.x == sclVec.y) {
        radius *= sclVec.x;
    }
    else {
        float scl = std::max(sclVec.x, sclVec.y);
        radius *= scl;
    }
}

