#pragma once

#include <SDL2/SDL.h>
#include "lib/glad.h"
#include <glm/glm.hpp>
#include <exception>
#include <memory>
#include <cmath>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "lib/Remotery.h"

#include "io/texturemanager.hpp"
#include "io/meshloader.hpp"
#include "io/hidinput.hpp"
#include "io/textfactory.hpp"
#include "io/maploader.hpp"

#include "world/world.hpp"
#include "../src/world/system/system.hpp"
#include "state/state.hpp"

class Engine {
public:
	static Engine& getInstance() {
		static Engine instance;
		return instance;
	}

	Engine(Engine const&) = delete;
	void operator=(Engine const&) = delete;

	int run(bool vsync);

	inline unsigned int& getWidth() { return _width; }
	inline unsigned int& getHeight() { return _height; }
	inline SDL_Window* getWindow() { return _window; }

	inline std::shared_ptr<TextureManager> getTextureManager() { return _textureManager; }
	inline std::shared_ptr<MeshLoader> getMeshLoader() { return _meshLoader; }
	inline std::shared_ptr<MapLoader> getMapLoader() { return _mapLoader; }
	inline std::shared_ptr<HIDInput> getHIDInput() { return _hidInput; }
	inline std::shared_ptr<TextFactory> getTextFactory() { return _textFactory; }

	inline std::vector<std::unique_ptr<System>>& getSystems() { return _systems; }

	template <typename T>
	T* getSystem();

	inline Entity* getCamera() {
		State* s = getStatePtr();
		if (!s)
			return nullptr;
		return s->getCamera();
	}

	template <typename T>
	inline std::unordered_map<std::type_index, std::unique_ptr<State>>& getStates() {
		return _states;
	}

	inline State& getState() { return *_states[*_currentState]; }
	inline State* getStatePtr() { return _states[*_currentState].get(); }

	inline const std::type_index getStateType() { return *_currentState; }

	template <typename T>
	inline void setState() {
		*_nextState = std::type_index(typeid(T));
	}

	inline void quit() { *_nextState = std::type_index(typeid(nullptr)); }

private:
	unsigned int _width = 1280;
	unsigned int _height = 720;
	bool _vsync = true;

	Remotery* rmt;

	bool _quit;
	SDL_Window* _window;
	SDL_GLContext _context;

	std::shared_ptr<TextureManager> _textureManager;
	std::shared_ptr<MeshLoader> _meshLoader;
	std::shared_ptr<MapLoader> _mapLoader;
	std::shared_ptr<HIDInput> _hidInput;
	std::shared_ptr<TextFactory> _textFactory;

	std::vector<std::unique_ptr<System>> _systems;

	std::unique_ptr<std::type_index> _currentState;
	std::unique_ptr<std::type_index> _nextState;
	std::unordered_map<std::type_index, std::unique_ptr<State>> _states;

	Engine() {}
	virtual ~Engine();

	void _init(bool vsync);
	void _initSDL();
	void _initGL();
	void _initImGui();

	void _setupSystems();

	void _system_tick(float delta);
	void _system_resize(unsigned int width, unsigned int height);
};

template <typename T>
T* Engine::getSystem() {
	T* ptr = nullptr;

	int i = 0, size = _systems.size();
	while (ptr == nullptr && i < size) {
		ptr = dynamic_cast<T*>(_systems[i++].get());
	}

	if (ptr == nullptr)
		throw "system does not exist";

	return ptr;
}
