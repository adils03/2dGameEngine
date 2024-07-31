#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Shader.h"
#include "Component.h"
#include <glm/ext/matrix_transform.hpp>

class Transform : public virtual Component {
public:
    Transform(Shader& shader, glm::vec2 pos, float rot, glm::vec2 scl);
 
    void update()  override;
    void cleanup() const override;

    void Translate(const glm::vec2& tVec);
    void Rotate(float rVal);
    void Scale(const glm::vec2& sVec);

    void setTransform(const glm::vec2& translate, float rotation, const glm::vec2& scale) const;

    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
private:
    Shader& shader;
};

#endif // TRANSFORM_H
