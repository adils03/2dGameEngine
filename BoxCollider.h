#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "Collider.h"
#include <vector>

class BoxCollider : public virtual Collider, public virtual Component
{
public:
	BoxCollider(Transform& transform, glm::vec2& pos, float rot, glm::vec2& sclVec, float width, float height);

	// Override virtual methods from Collider
	void update() override;
	void cleanup() const override;

	// Override virtual methods from Component
	void Translate(const glm::vec2& moveVec) override;
	void Rotate(float angle) override;
	void Scale(const glm::vec2& sclVec) override;


	std::vector<glm::vec2> getVertices() const { return vertices; }
private:
	void updateVertices();
	std::vector<glm::vec2> vertices;
	float height;
	float width;
};

#endif