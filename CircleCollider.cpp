#include "CircleCollider.h"

CircleCollider::CircleCollider(Transform& transform, const glm::vec2& pos, float r, const glm::vec2& sclVec)
    : Collider(transform), radius(r) {

}

void CircleCollider::Translate(const glm::vec2& moveVec) {
    transform.Translate(moveVec);
}

void CircleCollider::Rotate(float angle) {
    transform.Rotate(angle);
}

void CircleCollider::Scale(const glm::vec2& sclVec) {
    transform.Scale(sclVec);
}
