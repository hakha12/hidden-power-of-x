#ifndef __TUTORIAL_HPP__
#define __TUTORIAL_HPP__

#include "common.hpp"
#include "state.hpp"
#include "stateManager.hpp"

class Tutorial : public State {
	public:
		Tutorial(std::shared_ptr<StateManager> manager):State(manager){}

		void Init() override;
		void Destroy() override {}

		void Awake() override;
		void Sleep() override {}

		void Update() override;
		void Render() override;
	
	private:
		void ResetCounter();

		std::string message;
		int frameCounter;
};

#endif