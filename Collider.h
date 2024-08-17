#ifndef COLLIDER_H
#define COLLIDER_H

#include "glm/glm.hpp"
#include <vector>
#include "Transform.h"

enum class ColliderType {
    Circle,
    Box
};


class Collider 
{
public:
    Collider(Transform& transform,glm::vec2& pos,float rot,glm::vec2& sclVec);
    virtual ~Collider() = default;
    Transform& transform;
    glm::vec2 position;
    glm::vec2 positionOffset;
    float rotation;
    float rotationOffset;
    glm::vec2 scale;
    glm::vec2 scaleOffset;
    virtual void Translate(const glm::vec2& moveVec) = 0;
    virtual void Rotate(float angle) = 0;
    virtual void Scale(const glm::vec2& sclVec) = 0;
    virtual float GetArea() const = 0;
    virtual ColliderType GetType() const = 0;
};

#endif // COLLIDER_H
