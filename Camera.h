#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(float width, float height);

    void updateMatrix();
    glm::mat4 getViewProjection() const;

    void setPosition(const glm::vec2& pos);
    const glm::vec2& getPosition() const;

private:
    glm::vec2 position;
    float width, height;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 viewProjection;
};

#endif // CAMERA_H
