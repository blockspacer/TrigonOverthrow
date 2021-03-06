// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "particlesystem.hpp"

#include "../component/particlecomponent.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../../engine.hpp"
#include "../component/guncomponent.hpp"
#include "../component/transformcomponent.hpp"

ParticleSystem::ParticleSystem() {
	// Creating shaders for each particle effect. Check particlecomponent.hpp for the enumeration.
	_programs.resize(5);
	_programs[ParticleComponent::ParticleEffect::INITIATE] = std::make_shared<ShaderProgram>();
	_programs[ParticleComponent::ParticleEffect::INITIATE]->bind().attach(std::make_shared<ShaderUnit>("assets/shaders/particles_init.comp", ShaderType::compute)).finalize();
	_programs[ParticleComponent::ParticleEffect::INITIATE]->bind().addUniform("delta");

	_programs[ParticleComponent::ParticleEffect::EXPLOSION] = std::make_shared<ShaderProgram>();
	_programs[ParticleComponent::ParticleEffect::EXPLOSION]->bind().attach(std::make_shared<ShaderUnit>("assets/shaders/particles_explosion.comp", ShaderType::compute)).finalize();
	_programs[ParticleComponent::ParticleEffect::EXPLOSION]->bind().addUniform("delta");

	_programs[ParticleComponent::ParticleEffect::SPEW] = std::make_shared<ShaderProgram>();
	_programs[ParticleComponent::ParticleEffect::SPEW]->bind().attach(std::make_shared<ShaderUnit>("assets/shaders/particles_spew.comp", ShaderType::compute)).finalize();
	_programs[ParticleComponent::ParticleEffect::SPEW]->bind().addUniform("delta");

	_programs[ParticleComponent::ParticleEffect::ORB] = std::make_shared<ShaderProgram>();
	_programs[ParticleComponent::ParticleEffect::ORB]->bind().attach(std::make_shared<ShaderUnit>("assets/shaders/particles_orb.comp", ShaderType::compute)).finalize();
	_programs[ParticleComponent::ParticleEffect::ORB]->bind().addUniform("delta").addUniform("spawnPos");

	_programs[ParticleComponent::ParticleEffect::TRIGON] = std::make_shared<ShaderProgram>();
	_programs[ParticleComponent::ParticleEffect::TRIGON]->bind().attach(std::make_shared<ShaderUnit>("assets/shaders/particles_trigon.comp", ShaderType::compute)).finalize();
	_programs[ParticleComponent::ParticleEffect::TRIGON]->bind().addUniform("delta").addUniform("spawnPos");
}

ParticleSystem::~ParticleSystem() {}

//#pragma omp parallel for schedule(dynamic, 128)
void ParticleSystem::update(World& world, float delta) {
	// Gotta change how this system works abit.
	// Main things to fix: All emitters with the different types should use the correct sh7ader.

	// remember to fix initiate particles.
	for (Entity * entity : world.getActiveComponents<ParticleComponent>()) {
		auto particleComp = entity->getComponent<ParticleComponent>();
		if (!particleComp)
			continue;
			
		_programs[particleComp->type]->bind()
			.setUniform("delta", delta);
		particleComp->ssbo[ParticleAttribute::position]->bindBase(ParticleAttribute::position);
		particleComp->ssbo[ParticleAttribute::velocity]->bindBase(ParticleAttribute::velocity);
		particleComp->ssbo[ParticleAttribute::life]->bindBase(ParticleAttribute::life);
		particleComp->ssbo[ParticleAttribute::color]->bindBase(ParticleAttribute::color);
		if (particleComp->type == ParticleComponent::ParticleEffect::ORB || particleComp->type == ParticleComponent::ParticleEffect::TRIGON)
			_programs[particleComp->type]->setUniform("spawnPos", entity->getComponent<TransformComponent>()->getPosition());
		glDispatchCompute((GLint)particleComp->nrOfParticles / 128, 1, 1);
	}
}

void ParticleSystem::registerImGui() {}
