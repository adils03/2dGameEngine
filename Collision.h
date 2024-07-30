#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <vector>
#include <glm/glm.hpp>

class Collisions
{
private:
	static int FindClosestPointOnPolygon(glm::vec2& circleCenter, std::vector<glm::vec2>& vertices);
	static void ProjectCircle(glm::vec2& circle, float radius, glm::vec2& axis, float& min, float& max);
	static void ProjectVertices(const std::vector<glm::vec2>& vertices, glm::vec2& axis, float& min, float& max);
public:
	static bool IntersectCirclePolygon(glm::vec2& circleCenter, float circleRadius, glm::vec2& polygonCenter, std::vector<glm::vec2>& vertices, glm::vec2& normal, float& depth);
	static bool IntersectCircles(glm::vec2& centerA, glm::vec2& centerB, float radiusA, float radiusB, glm::vec2& normal, float& depth);
	static bool IntersectPolygons(const glm::vec2& centerA, const glm::vec2& centerB, const std::vector<glm::vec2>& a, const std::vector<glm::vec2>& b, glm::vec2& normal, float& depth);
};

#endif // COLLISIONS_H