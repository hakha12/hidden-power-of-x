#ifndef __STATE_HPP__
#define __STATE_HPP__

#include "common.hpp"

class StateManager;

class State {
	public:
		State(std::shared_ptr<StateManager> manager): stateManager(manager){}

		virtual void Init() = 0;
		virtual void Destroy() = 0;

		virtual void Awake() = 0;
		virtual void Sleep() = 0;

		virtual void Update() = 0;
		virtual void Render() = 0;
	
	protected:
		std::shared_ptr<StateManager> stateManager;
};

#endif