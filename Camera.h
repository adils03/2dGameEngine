#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"
#include "Shader.h"

class Camera : public Component{
public:
    Camera(Shader& shader,float width, float height);

    void update() const override;
    void cleanup() const override;

    void updateMatrix();
    glm::mat4 getViewProjection() const;

    void setPosition(const glm::vec2& pos);
    const glm::vec2& getPosition() const;

private:
    Shader& shader;
    glm::vec2 position;
    float width, height;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 viewProjection;
};

#endif // CAMERA_H
