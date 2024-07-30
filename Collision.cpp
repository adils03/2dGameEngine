#include "Collision.h"

int Collisions::FindClosestPointOnPolygon(glm::vec2& circleCenter, std::vector<glm::vec2>& vertices)
{
    return 0;
}

void Collisions::ProjectCircle(glm::vec2& circle, float radius, glm::vec2& axis, float& min, float& max)
{
}

void Collisions::ProjectVertices(std::vector<glm::vec2>& vertices, glm::vec2& axis, float& min, float& max)
{
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

bool Collisions::IntersectPolygons(glm::vec2& centerA, glm::vec2& centerB, std::vector<glm::vec2>& a, std::vector<glm::vec2>& b, glm::vec2& normal, float& depth)
{
    return false;
}
