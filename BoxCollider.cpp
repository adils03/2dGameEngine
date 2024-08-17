#include "BoxCollider.h"

BoxCollider::BoxCollider(Transform& transform, glm::vec2& pos, float rot, glm::vec2& sclVec, float width, float height)
	: Collider(transform, pos, rot, sclVec), width(width), height(height)
{
	positionOffset = transform.position - position;
	rotationOffset = transform.rotation - rotation;
	scaleOffset = transform.scale / scale;
	updateVertices();
}


void BoxCollider::update()
{
	position = transform.position - positionOffset;
	rotation = transform.rotation - rotationOffset;
	updateVertices();
}

void BoxCollider::cleanup() const
{
}

float BoxCollider::GetArea() const
{
	return width * height;
}

ColliderType BoxCollider::GetType() const
{
	return ColliderType::Box;
}

void BoxCollider::Translate(const glm::vec2& moveVec)
{
	positionOffset += moveVec;
	for (glm::vec2& vec : vertices) {
		vec += moveVec;
	}

}

void BoxCollider::Rotate(float angle)
{
	rotationOffset += angle;

	float radians = glm::radians(angle);

	float cosTheta = cos(radians);
	float sinTheta = sin(radians);

	for (glm::vec2& vec : vertices) {
		glm::vec2 relativePosition = vec - position;

		glm::vec2 rotatedPosition(
			relativePosition.x * cosTheta - relativePosition.y * sinTheta,
			relativePosition.x * sinTheta + relativePosition.y * cosTheta
		);

		vec = rotatedPosition + position;
	}
}

void BoxCollider::Scale(const glm::vec2& sclVec) {
	glm::vec2 pivot = glm::vec2(
		(vertices[0].x + vertices[2].x) / 2,
		(vertices[0].y + vertices[2].y) / 2
	);

	for (auto& vertex : vertices) {
		glm::vec2 offset = vertex - pivot;

		offset.x *= sclVec.x;
		offset.y *= sclVec.y;

		vertex = pivot + offset;
	}

	width *= sclVec.x;
	height *= sclVec.y;
}

void BoxCollider::updateVertices()
{
	std::vector<glm::vec2> boxVertices = {
	glm::vec2(position.x - width / 2, position.y - height / 2),
	glm::vec2(position.x - width / 2, position.y + height / 2),
	glm::vec2(position.x + width / 2, position.y + height / 2),
	glm::vec2(position.x + width / 2, position.y - height / 2)
	};
	vertices = boxVertices;
}
