#pragma once

#include "component.hpp"

#include <glm/glm.hpp>

#include "../renderpass/lightingrenderpass.hpp"

struct PointLightComponent : public Component {
	PointLight pointLight;
	glm::vec3 offset;

	PointLightComponent() = default;
	PointLightComponent(const ComponentValues& value);
	virtual ~PointLightComponent();

	void registerImGui() final;
	inline std::string name() final { return "PointLightComponent"; }
};
