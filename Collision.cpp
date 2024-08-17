#include "Collisions.h"
#include <iostream>


bool Collisions::IntersectCirclePolygon(const glm::vec2& circleCenter, const float circleRadius, const glm::vec2& polygonCenter, const std::vector<glm::vec2>& vertices, glm::vec2& normal, float& depth)
{
	normal = glm::vec2();
	depth = std::numeric_limits<float>::max();

	glm::vec2 axis = glm::vec2();
	float axisDepth = 0;
	float minA = 0, maxA = 0, minB = 0, maxB = 0;

	for (size_t i = 0;i < vertices.size();i++) {
		glm::vec2 va = vertices[i];
		glm::vec2 vb = vertices[(i + 1) % vertices.size()];

		glm::vec2 edge = vb - va;
		glm::vec2 axis = glm::vec2(-edge.y, edge.x);
		axis = glm::normalize(axis);

		Collisions::ProjectVertices(vertices, axis, minA, maxA);
		Collisions::ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA) {
			return false;
		}

		axisDepth = std::min(maxB - minA, maxA - minB);

		if (axisDepth < depth) {
			depth = axisDepth;
			normal = axis;
		}
	}

	int cpIndex = Collisions::FindClosestPointOnPolygon(circleCenter, vertices);
	glm::vec2 cp = vertices[cpIndex];

	axis = cp - circleCenter;
	axis = glm::normalize(axis);

	Collisions::ProjectVertices(vertices, axis, minA, maxA);
	Collisions::ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);

	if (minA >= maxB || minB >= maxA) {
		return false;
	}

	axisDepth = std::min(maxB - minA, maxA - minB);

	if (axisDepth < depth) {
		depth = axisDepth;
		normal = axis;
	}

	glm::vec2 direction = circleCenter - polygonCenter;

	if (glm::dot(direction, normal) < 0) {
		normal = -normal;
	}

	return true;
}

void Collisions::ProjectCircle(const glm::vec2& circle, const float radius, const glm::vec2& axis, float& min, float& max)
{
	glm::vec2 direction = glm::normalize(axis);
	glm::vec2 directionAndRadius = direction * radius;

	glm::vec2 p1 = circle + directionAndRadius;
	glm::vec2 p2 = circle - directionAndRadius;

	min = glm::dot(p1, axis);
	max = glm::dot(p2, axis);

	if (min > max) {
		float t = min;
		min = max;
		max = t;
	}
}

int Collisions::FindClosestPointOnPolygon(const glm::vec2& circleCenter, const std::vector<glm::vec2>& vertices)
{
	int result = -1;
	float minDistance = std::numeric_limits<float>::max();

	for (size_t i = 0; i < vertices.size(); i++) {
		glm::vec2 v = vertices[i];
		float distance = glm::distance(v, circleCenter);

		if (distance < minDistance) {
			minDistance = distance;
			result = static_cast<int>(i);
		}
	}

	return result;
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
bool Collisions::IntersectCircles(const glm::vec2& centerA, const glm::vec2& centerB, float radiusA, float radiusB, glm::vec2& normal, float& depth)
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