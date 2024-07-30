#include "Collider.h"

Collider::Collider(Transform& transform)
    : transform(transform) {
    this->position = transform.position;
    this->rotation = transform.rotation;
    this->scale = transform.scale;
}

void Collider::update() const {
    // Implementation here
}

void Collider::cleanup() const {
    // Implementation here
}
