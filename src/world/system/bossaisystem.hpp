#pragma once
#include "system.hpp"
#include "../component/bossaicomponent.hpp"

class BossAISystem : public System {
public:
	BossAISystem();
	virtual ~BossAISystem();
	void update(World& world, float delta) final;
	void registerImGui() final;
	inline std::string name() final { return "BossAISystem"; }
	void setCentre(glm::vec3 centre) { _centre = centre; }
private:
	bool _walkToMiddle;
	void _doPhase(Entity* boss, float delta);
	glm::vec3 _calculateForceDirection(glm::vec3 inDir, float time);
	glm::vec3 _centre;
	void _moveMiddle(Entity* entity);
};