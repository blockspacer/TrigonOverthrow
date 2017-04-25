#pragma once
#include "component.hpp"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <glm/glm.hpp>

class RigidBodyComponent : public Component
{
public:
	RigidBodyComponent();
	virtual ~RigidBodyComponent();

	// Inherited via Component
	virtual std::string name() override;
	virtual void registerImGui() override;

	btRigidBody * getRigidBody();
	btMotionState * getMotionState();
	glm::vec3 getHitboxHalfSize();

	void setMass(btScalar mass);
	void setFriction(btScalar friction);
	void setHitboxHalfSize(const glm::vec3 & size);
	void setPosition(const glm::vec3& pos);

private:
	btRigidBody * rigidBody;

	btScalar friction;
	btScalar mass;
	btMotionState * state;
	btBoxShape * shape;

	glm::vec3 hitboxHalfSize;

};