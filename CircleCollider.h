#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "Collider.h"

class CircleCollider : public virtual Collider , public virtual Component
{
public:
    CircleCollider(Transform& transform, glm::vec2& pos, float rot, glm::vec2& sclVec, float radius);

    // Override virtual methods from Collider
    void update() override;
    void cleanup() const override;

    // Override virtual methods from Component
    void Translate(const glm::vec2& moveVec) override;
    void Rotate(float angle) override;
    void Scale(const glm::vec2& sclVec) override;

    // Additional methods specific to CircleCollider
    float getRadius() const { return radius; }
    void setRadius(float r) { radius = r; }
private:
    float radius; 
};

#endif // CIRCLE_COLLIDER_H
