#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"
#include "Shader.h"

class Camera : public virtual Component {
public:
    Camera(Shader& shader, float width, float height);

    void update()  override;
    void cleanup() const override;

    void updateMatrix() const;
    glm::mat4 getViewProjection() const;

    void move(const glm::vec2& moveVec);
    void setPosition(const glm::vec2& pos);
    const glm::vec2& getPosition() const;

private:
    Shader& shader;
    glm::vec2 position;
    float width, height;
    mutable glm::mat4 view;
    mutable glm::mat4 projection;
    mutable glm::mat4 viewProjection;
};

#endif // CAMERA_H
