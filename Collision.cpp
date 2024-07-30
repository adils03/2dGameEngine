#include "Collision.h"
#include <iostream>

int Collisions::FindClosestPointOnPolygon(glm::vec2& circleCenter, std::vector<glm::vec2>& vertices)
{
    return 0;
}

void Collisions::ProjectCircle(glm::vec2& circle, float radius, glm::vec2& axis, float& min, float& max)
{
}

void Collisions::ProjectVertices(const std::vector<glm::vec2>& vertices, glm::vec2& axis, float& min, float& max)
{
	min = std::numeric_limits<float>::max();
	max = std::numeric_limits<float>::min();

	for (size_t i = 0;i < vertices.size();i++) {
		glm::vec2 v = vertices[i];
		float proj = glm::dot(v, axis);

		if (proj < min) {
			min = proj;
		}
		if (proj > max) {
			max = proj;
		}
	}
}

bool Collisions::IntersectCirclePolygon(glm::vec2& circleCenter, float circleRadius, glm::vec2& polygonCenter, std::vector<glm::vec2>& vertices, glm::vec2& normal, float& depth)
{
    return false;
}

bool Collisions::IntersectCircles(glm::vec2& centerA, glm::vec2& centerB, float radiusA, float radiusB, glm::vec2& normal, float& depth)
{
	float distance = glm::distance(centerA, centerB);
	float radii = radiusA + radiusB;

	if (distance >= radii) {
		return false;
	}

	normal = glm::normalize(centerB - centerA);
	depth = radii - distance;
	return true;
}

bool Collisions::IntersectPolygons(const glm::vec2& centerA, const glm::vec2& centerB, const std::vector<glm::vec2>& verticesA, const std::vector<glm::vec2>& verticesB, glm::vec2& normal, float& depth)
{
	normal = glm::vec2();
	depth = std::numeric_limits<float>::max();

	for (size_t i = 0;i < verticesA.size();i++) {
		glm::vec2 va = verticesA[i];
		glm::vec2 vb = verticesA[(i + 1) % verticesA.size()];

		glm::vec2 edge = vb - va;
		glm::vec2 axis = glm::vec2(-edge.y, edge.x);
		axis = glm::normalize(axis);

		float minA = 0;
		float maxA = 0;

		float minB = 0;
		float maxB = 0;

		Collisions::ProjectVertices(verticesA, axis, minA, maxA);
		Collisions::ProjectVertices(verticesB, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA) {
			return false;
		}

		float axisDepth = std::min(maxB - minA, maxA - minB);

		if (axisDepth < depth) {
			depth = axisDepth;
			normal = axis;
		}
	}

	for (size_t i = 0;i < verticesB.size();i++) {
		glm::vec2 va = verticesB[i];
		glm::vec2 vb = verticesB[(i + 1) % verticesB.size()];

		glm::vec2 edge = vb - va;
		glm::vec2 axis = glm::vec2(-edge.y, edge.x);
		axis = glm::normalize(axis);

		float minA = 0;
		float maxA = 0;

		float minB = 0;
		float maxB = 0;

		Collisions::ProjectVertices(verticesA, axis, minA, maxA);
		Collisions::ProjectVertices(verticesB, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA) {
			return false;
		}

		float axisDepth = std::min(maxB - minA, maxA - minB);

		if (axisDepth < depth) {
			depth = axisDepth;
			normal = axis;
		}
	}


	glm::vec2 direction = centerB - centerA;

	if (glm::dot(direction, normal) < 0) {
		normal = -normal;
	}

	return true;
}
