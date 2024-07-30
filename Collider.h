#ifndef COLLIDER_H
#define COLLIDER_H

#include "glm/glm.hpp"
#include <vector>
#include "Component.h"
#include "Transform.h"

class Collider : public Component
{
public:
    Collider(Transform& transform);
    virtual ~Collider() = default;
    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
    std::vector<glm::vec2>* vertices = nullptr;

    void update() const override;
    void cleanup() const override;
    virtual void Translate(const glm::vec2& moveVec) = 0;
    virtual void Rotate(float angle) = 0;
    virtual void Scale(const glm::vec2& sclVec) = 0;
protected:
    Transform& transform;
};

#endif // COLLIDER_H
