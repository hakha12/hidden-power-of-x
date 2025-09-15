#ifndef __STATEMANAGER_HPP__
#define __STATEMANAGER_HPP__

#include "state.hpp"
#include "shared.hpp"

enum class StateType {
	INTRO = 1,
	TITLE,
	TUTORIAL,
	LEVEL,
};

class StateManager {
	public:
		StateManager(std::shared_ptr<SharedContext> shared);
		~StateManager(){}

		void Update();
		void Render();

		void Add(const StateType& type, std::shared_ptr<State> state);
		void SwitchTo(const StateType& type);

		std::shared_ptr<SharedContext> GetSharedContext();
	
	private:
		

		std::unordered_map<StateType, std::shared_ptr<State>> stateList;
		std::shared_ptr<State> currentState;

		std::shared_ptr<SharedContext> sharedContext;
};

#endif