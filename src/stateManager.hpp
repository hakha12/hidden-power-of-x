#ifndef __STATEMANAGER_HPP__
#define __STATEMANAGER_HPP__

#include "state.hpp"

enum class StateType {
	INTRO = 1,
	TITLE,
	TUTORIAL,
	LEVEL,
};

class StateManager {
	public:
		StateManager();
		~StateManager(){}

		void Update();
		void Render();

		void Add(const StateType& type, std::shared_ptr<State> state);
		void SwitchTo(const StateType& type);
	
	private:
		

		std::unordered_map<StateType, std::shared_ptr<State>> stateList;
		std::shared_ptr<State> currentState;
};

#endif