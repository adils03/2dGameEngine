#include "Transform.h"

Transform::Transform(Shader& shader, glm::vec2 pos, float rot, glm::vec2 scl)
    : shader(shader), position(pos), rotation(rot), scale(scl) {
    setTransform(position, rotation, scale);
}

void Transform::update() const {
    setTransform(position, rotation, scale);
}

void Transform::cleanup() const {
    // Cleanup logic if necessary
}

void Transform::Translate(const glm::vec2& tVec) {
    position += tVec;
}

void Transform::Rotate(float rVal) {
    rotation += rVal;
}

void Transform::Scale(const glm::vec2& sVec) {
    scale *= sVec;
}

void Transform::setTransform(const glm::vec2& translate, float rotation, const glm::vec2& scale) const {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(translate, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(scale, 1.0f));

    shader.setMat4("transform", transform);
}
