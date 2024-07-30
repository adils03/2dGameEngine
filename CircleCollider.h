#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Collider.h"

class CircleCollider : public Collider {
public:
    CircleCollider(Transform& transform, const glm::vec2& pos, float r, const glm::vec2& sclVec);
    float radius;
    void Translate(const glm::vec2& moveVec) override;
    void Rotate(float angle) override;
    void Scale(const glm::vec2& sclVec) override;
};

#endif // !CIRCLECOLLIDER_H
