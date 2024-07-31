#include "CircleCollider.h"
#include <iostream>

CircleCollider::CircleCollider(Transform& transform, glm::vec2& pos, float rot, glm::vec2& sclVec, float radius)
    : Collider(transform, pos, rot, sclVec), radius(radius)
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

