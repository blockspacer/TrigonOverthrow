// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "lookatcomponent.hpp"
#include "../../engine.hpp"
#include <glm/gtc/type_ptr.hpp>

LookAtComponent::LookAtComponent(const ComponentValues& value) : LookAtComponent() {
	followMode = (FollowMode)value.getInt("followMode", 2);
	target = Engine::getInstance().getState().getPlayer();
}

LookAtComponent::~LookAtComponent() {}

void LookAtComponent::registerImGui() {
	ImGui::Text("Targeting:");
	ImGui::SameLine();
	if (target)
		ImGui::Text(target->getName().c_str());
	else
		ImGui::Text("**NULL**");

	ImGui::Text("Follow by: ");
	ImGui::SameLine();
	ImGui::RadioButton("Distance", (int*)&followMode, (int)FollowMode::followByDistance);
	ImGui::SameLine();
	ImGui::RadioButton("Offset", (int*)&followMode, (int)FollowMode::followByOffset);
	ImGui::SameLine();
	ImGui::RadioButton("Static", (int*)&followMode, (int)FollowMode::staticPosition);

	if (followMode == FollowMode::followByDistance) {
		ImGui::DragFloat("Min distance", &minDistance);
		ImGui::DragFloat("Max distance", &maxDistance);
	} else
		ImGui::DragFloat3("Offset from target", glm::value_ptr(offsetFromTarget));
}
