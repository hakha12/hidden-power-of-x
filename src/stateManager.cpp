#include "stateManager.hpp"

StateManager::StateManager(std::shared_ptr<SharedContext> shared){
	sharedContext = shared;
}

void StateManager::Update(){
	if (!currentState) return;

	currentState->Update();
}

void StateManager::Render(){
	if (!currentState) return;

	currentState->Render();
}

void StateManager::SwitchTo(const StateType& type){
	auto it = stateList.find(type);

	if (it == stateList.end()) return;

	if (currentState) currentState->Sleep();

	currentState = it->second;
	currentState->Awake();
}

std::shared_ptr<SharedContext> StateManager::GetSharedContext(){
	return sharedContext;
}

void StateManager::Add(const StateType& type, std::shared_ptr<State> state){
	state->Init();
	stateList.insert(std::make_pair(type, state));
}