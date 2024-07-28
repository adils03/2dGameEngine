#include "Transform.h"

Transform::Transform(Shader& shader, glm::vec2 pos, float rot, glm::vec2 scl) : shader(shader), position(pos), rotation(rot), scale(scl)
{
	setTransform(position, rotation, scale);
}

void Transform::update() const
{
	setTransform(position, rotation, scale);
}

void Transform::cleanup() const
{
}

void Transform::Translate(glm::vec2 tVec)
{
	position += tVec;
	/*glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position, 0.0f));
	shader.setMat4("transform", transform);*/
}


void Transform::Rotate(float rVal)
{
	rotation += rVal;
	/*glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.setMat4("transform", transform);*/
}

void Transform::Scale(glm::vec2 sVec)
{
	scale *= sVec;
	/*glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::scale(transform, glm::vec3(scale, 1.0f));

	shader.setMat4("transform", transform);*/
}

void Transform::Teleport(glm::vec2 tVec)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(tVec, 0.0f));

	shader.setMat4("transform", transform);
}

void Transform::RotateTo(float rVal)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(rVal), glm::vec3(0.0f, 0.0f, 1.0f));

	shader.setMat4("transform", transform);
}

void Transform::ScaleTo(glm::vec2 sVec)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::scale(transform, glm::vec3(sVec, 1.0f));

	shader.setMat4("transform", transform);
}

void Transform::setTransform(glm::vec2 translate, float rotation, glm::vec2 scale) const
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(translate,0.0f));
	transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(scale, 1.0f));

	shader.setMat4("transform", transform);
}
