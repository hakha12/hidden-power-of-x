#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include "state.hpp"
#include "stateManager.hpp"
#include "entity.hpp"
#include "background.hpp"


class Level : public State {
	public:
		Level(std::shared_ptr<StateManager> manager): State(manager){}

		void Init() override;
		void Destroy() override {}

		void Awake() override;
		void Sleep() override {}

		void Update() override;
		void Render() override;
	
	private:
		void ResetPlayer();
		void MovePlayer();
		void CheckPlayerCollision();

		void BoundCheck();
		void SpawnEnemy();
		void SpawnBackground();
		void MoveBackground(int speed);

		void ResetIntroBar();

		std::shared_ptr<Entity> player;
		std::list<std::shared_ptr<Entity>> enemyList;
		std::list<Background> backgrounds;
		Background topBarRec;
		Background botBarRec;

		int playerHP;
		int playerScore;

		bool isPaused;
		bool isGameOver;
};

#endif