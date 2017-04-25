#pragma once
#include "component.hpp"
#include <glm/glm.hpp>

// Note! When making changes here add them also to FloorTransformComponent

struct TransformComponent : public Component {
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::mat4 matrix = glm::mat4();

	virtual ~TransformComponent();

	void recalculateMatrix();
	glm::vec3 getDirection();

	virtual void registerImGui();

	virtual std::string name() { return "TransformComponent"; }
};
