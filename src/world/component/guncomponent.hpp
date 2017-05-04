#pragma once
#include "component.hpp"
#include "modelcomponent.hpp"
#include "glm/glm.hpp"

struct GunComponent : public Component {
	enum GunType : int { RAYGUN = 0, ENERGYGUN };

	virtual ~GunComponent();

	GunType type;
	int cooldown;
	int cooldownLength;
	bool shoot;

	void addGun(GunType inType, int inCooldown);
	void registerImGui() final;
	inline std::string name() final { return "GunComponent"; }
};
