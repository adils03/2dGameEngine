#include "Camera.h"

Camera::Camera(float width, float height)
    : position(0.0f, 0.0f), width(width), height(height) {
    updateMatrix();
}


void Camera::updateMatrix() {
    view = glm::translate(glm::mat4(1.0f), -glm::vec3(position, 0.0f));
    projection = glm::ortho(0.0f, width, 0.0f, height);
    viewProjection = projection * view;
}

glm::mat4 Camera::getViewProjection() const {
    return viewProjection;
}

void Camera::setPosition(const glm::vec2& pos) {
    position = pos;
    updateMatrix();
}

const glm::vec2& Camera::getPosition() const {
    return position;
}
