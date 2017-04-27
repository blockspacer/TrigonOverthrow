#include "projectilesystem.hpp"
#include "bulletphysicssystem.hpp"
#include "../component/projectilecomponent.hpp"
#include "../../engine.hpp"

void ProjectileSystem::update(World& world, float delta) {
	// maybe remove ghostcomponent and system.
	auto physWorld = Engine::getInstance().getSystem<BulletPhysicsSystem>()->getWorld();
	int numManifolds = physWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++) {
		btPersistentManifold* contactManifold = physWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();
		
		if (!static_cast<Entity*>(obA->getUserPointer())->getComponent<ProjectileComponent>()) {
			if (!static_cast<Entity*>(obB->getUserPointer())->getComponent<ProjectileComponent>())
				continue;
		}

		//printf("OHGODNOPLEASESTOP\n");
		int numContacts = contactManifold->getNumContacts();
		for (int j = 0; j < numContacts; j++) {
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance() < 0.f) {
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
				printf("Projectile collided with\n");
			}
		}
	}
}


void ProjectileSystem::registerImGui() {
	
}