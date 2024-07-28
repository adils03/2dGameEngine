#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include "Shader.h"
#include "Component.h"
#include "Shader.h"

class Light : public Component
{
public:
	Light(Shader& shader,glm::vec2 lPos, glm::vec3 lColor, float lRadius);
	void update() const override;
	void cleanup() const override;
	void use(Shader& shader) const;
	void move(glm::vec2 moveVec);
	void setColor(glm::vec3 color);
	void setRadius(float radius);
private:
	Shader& shader;
	glm::vec2 lightPos;
	glm::vec3 lightColor;
	float lightRadius;
};


#endif // LIGHT_H

