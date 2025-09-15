#include "tutorial.hpp"

#define TYPING_INTERVAL 15
#define TYPING_SPEED 2

void Tutorial::Init(){
	message = "ERROR	: enemy_hitbox() doesn't return the expected position.\nWARNING	: Expected care from player_movement().\n\nPress ENTER to begin.";

	ResetCounter();
}

void Tutorial::Awake(){
	ResetCounter();
}

void Tutorial::Update(){
	if (IsKeyPressed(KEY_ENTER)) stateManager->SwitchTo(StateType::LEVEL);

	frameCounter += TYPING_SPEED;
}

void Tutorial::Render(){
	ClearBackground(BLACK);
	DrawText(TextSubtext(message.c_str(), 0, frameCounter/10), stateManager->GetSharedContext()->window->GetInternalSize().x/8, 400, 40, RAYWHITE);
}

void Tutorial::ResetCounter(){
	frameCounter = 0;
}