#include "lifesystem.hpp"
#include "../component/lifecomponent.hpp"

void LifeSystem::update(World& world, float delta) {
	for (std::unique_ptr<Entity>& entity : world.getEntities()) {
		auto lifeComp = entity->getComponent<LifeComponent>();
		if (!lifeComp)
			continue;

		if (lifeComp->currHP <= 0)
			entity->makeDead();

		if (entity->getName() == "Projectile") {
			lifeComp->currHP -= 1 * delta;
		}
	}
}

void LifeSystem::registerImGui() {
	
}