#include "Light.h"

Light::Light(glm::vec2 lPos, glm::vec3 lColor, float lRadius) : lightPos(lPos) , lightColor(lColor) , lightRadius(lRadius)
{

}

void Light::use(Shader& shader) const
{
	shader.setVec2("lightPos", lightPos);
	shader.setVec3("lightColor", lightColor);
	shader.setFloat("lightRadius", lightRadius);
}

void Light::move(glm::vec2 moveVec)
{
	lightPos += moveVec;
}

void Light::setColor(glm::vec3 color)
{
	lightColor = color;
}

void Light::setRadius(float radius)
{
	lightRadius = radius;
}

