#pragma once

#include "state.hpp"

class InGameState : public State {
public:
	InGameState();

	virtual void onEnter(State* prev);
	virtual void onLeave(State* next);
	inline virtual Entity* getCamera() { return _camera; }

private:
	Entity* _camera;
	Entity* _player;
	Entity* _floor;

	void _addLookAt();

	static void _registerImGUI(Entity& self, State& state);
};