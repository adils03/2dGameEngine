#include "CircleCollider.h"
#include <iostream>

CircleCollider::CircleCollider(Transform& transform, glm::vec2& pos, float rot, glm::vec2& sclVec, float radius)
    : Collider(transform, pos, rot, sclVec), radius(radius)
{
    
}

void CircleCollider::update() {
    position = transform.position;
    rotation = transform.rotation;
}

void CircleCollider::cleanup() const {
    std::cout << "Cleaning up CircleCollider" << std::endl;
}

void CircleCollider::Translate(const glm::vec2& moveVec) {
    transform.Translate(moveVec);
}

void CircleCollider::Rotate(float angle) {
    transform.Rotate(angle);
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

