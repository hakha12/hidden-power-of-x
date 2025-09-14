#include "stateManager.hpp"

StateManager::StateManager(){

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

void StateManager::Add(const StateType& type, std::shared_ptr<State> state){
	state->Init();
	stateList.insert(std::make_pair(type, state));
}