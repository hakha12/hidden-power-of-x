#ifndef __TITLE_HPP__
#define __TITLE_HPP__

#include "state.hpp"
#include "stateManager.hpp"
#include "background.hpp"

class Title : public State {
	public:
		Title(std::shared_ptr<StateManager> manager):State(manager){}

		void Init() override;
		void Destroy() override {}

		void Awake() override;
		void Sleep() override {}

		void Update() override;
		void Render() override;

	private:
		void ResetBackground();
		void BackToIntro();

		std::list<Background> backgrounds;

		Rectangle transitionRec;
		float transitionAlpha;
};

#endif