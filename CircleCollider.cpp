#include "CircleCollider.h"

CircleCollider::CircleCollider(Transform& transform, glm::vec2& pos, float r, glm::vec2& sclVec)
    : Collider(transform,pos,sclVec),radius(r)
{
    
}

void CircleCollider::Translate(const glm::vec2& moveVec) 
{
    position += moveVec;
    transform.Translate(moveVec);
}

void CircleCollider::Rotate(float angle) 
{
}

void CircleCollider::Scale(const glm::vec2& sclVec) 
{
    scale *= sclVec;
    transform.Scale(sclVec);

}
