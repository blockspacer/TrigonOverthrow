// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "camerasystem.hpp"
#include "../component/transformcomponent.hpp"
#include "../component/cameracomponent.hpp"
#include <glm/gtx/transform.hpp>

CameraSystem::~CameraSystem() {}

void CameraSystem::update(World& world, float delta) {
	for (std::unique_ptr<Entity>& entity : world.getEntities()) {
		auto cameraComponent = entity->getComponent<CameraComponent>();
		if (!cameraComponent)
			continue;

		auto transformComponent = entity->getComponent<TransformComponent>();
		if (!transformComponent)
			continue;

		// glm::vec3 lookDir = transformComponent->getDirection();

		static const glm::vec3 y(0, 1, 0);
		cameraComponent->viewMatrix = glm::lookAt(transformComponent->position, transformComponent->position + transformComponent->getDirection(), y);
	}
}

void CameraSystem::registerImGui() {}
