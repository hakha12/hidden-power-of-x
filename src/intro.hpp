#ifndef __INTRO_HPP__
#define __INTRO_HPP__

#include "state.hpp"
#include "stateManager.hpp"

class Intro : public State {
	public:
		Intro(std::shared_ptr<StateManager> manager):State(manager){}

		void Init() override;
		void Destroy() override {}

		void Awake() override;
		void Sleep() override {}

		void Update() override;
		void Render() override;
	
	private:
		void Reset();

		Vector2 logoPosition;
		int frameCounter;
		int letterCount;

		int topRecWidth;
		int leftRecHeight;

		int botRecWidth;
		int rightRecHeight;

		int state;
		float alpha;
};

#endif