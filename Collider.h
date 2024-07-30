#ifndef COLLIDER_H
#define COLLIDER_H

#include "glm/glm.hpp"
#include <vector>
#include "Transform.h"

class Collider 
{
public:
    Collider(Transform& transform,glm::vec2& pos,float rot,glm::vec2& sclVec);
    virtual ~Collider() = default;
    Transform& transform;
    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
    virtual void Translate(const glm::vec2& moveVec) = 0;
    virtual void Rotate(float angle) = 0;
    virtual void Scale(const glm::vec2& sclVec) = 0;
};

#endif // COLLIDER_H
