// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "buttoncomponent.hpp"

#include <glm/gtc/type_ptr.hpp>

ButtonComponent::ButtonComponent() {}

ButtonComponent::ButtonComponent(const ComponentValues& value) : ButtonComponent() {
	position = value.getVec3("position", {0, 0, 0});
	size = value.getVec3("size", {1, 1, 1});
}

ButtonComponent::~ButtonComponent() {}

void ButtonComponent::registerImGui() {
	ImGui::DragFloat3("Position", glm::value_ptr(position));
	ImGui::DragFloat3("Size", glm::value_ptr(size));
}
