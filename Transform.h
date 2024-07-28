#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Shader.h"
#include "Component.h"
#include <glm/ext/matrix_transform.hpp>

class Transform : public Component{
public:
	Shader& shader;
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;
	Transform(Shader& shader,glm::vec2 pos,float rot,glm::vec2 scl);
	void update() const override;
	void cleanup() const override;
	void Translate(glm::vec2 tVec);
	void Rotate(float rVal);
	void Scale(glm::vec2 sVec);
	void Teleport(glm::vec2 tVec);
	void RotateTo(float rVal);
	void ScaleTo(glm::vec2 sVec);
	void setTransform(glm::vec2 translate, float rotation, glm::vec2 scale) const;
};


#endif // !TRANSFORM_H
