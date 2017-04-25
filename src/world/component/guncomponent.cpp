#include "guncomponent.hpp"


void GunComponent::addGun(GunComponent::GunType inType, int inCooldown) {
	type = inType;
	cooldownLength = inCooldown;
	cooldown = 0;
	shoot = false;
}

void GunComponent::registerImGui() {
	
}