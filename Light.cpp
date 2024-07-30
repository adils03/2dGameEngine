#include "Light.h"

Light::Light(Shader& shader, glm::vec2 lPos, glm::vec3 lColor, float lRadius)
    : shader(shader), lightPos(lPos), lightColor(lColor), lightRadius(lRadius) {}

void Light::update()  {
    use();
}

void Light::cleanup() const {
    // Cleanup logic if necessary
}

void Light::use() const {
    shader.setVec2("lightPos", lightPos);
    shader.setVec3("lightColor", lightColor);
    shader.setFloat("lightRadius", lightRadius);
}

void Light::move(glm::vec2 moveVec) {
    lightPos += moveVec;
}

void Light::setColor(glm::vec3 color) {
    lightColor = color;
}

void Light::setRadius(float radius) {
    lightRadius = radius;
}
