#pragma once
#include "component.hpp"
#include "transformcomponent.hpp"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <glm/glm.hpp>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

struct GhostObjectComponent : public Component {
public:
	GhostObjectComponent();
	GhostObjectComponent(const ComponentValues& value);
	virtual ~GhostObjectComponent();
	// Inherited via Component
	inline std::string name() final { return "GhostObjectComponent"; }
	void registerImGui() final;

	glm::vec3 hitboxHalfSize;
	btPairCachingGhostObject* getGhostObject();
	glm::vec3 getHitboxHalfSize();

	void setFriction(btScalar friction);
	void setHitboxHalfSize(const glm::vec3& size);

private:
	btPairCachingGhostObject* _ghostObject;

	btScalar _friction;
	btBoxShape* _shape;
};
