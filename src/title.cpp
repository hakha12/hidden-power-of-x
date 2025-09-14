#include "title.hpp"

#define MAX_BACKGROUND 70

void Title::Init(){
	transitionRec = (Rectangle){0, 0, 1920, 1080};
	transitionAlpha = 1.0f;

	ResetBackground();
}

void Title::Awake(){
	transitionAlpha = 1.0f;
	ResetBackground();
}

void Title::Update(){
	for (auto &i: backgrounds) i.rec.y -= 5;

	if (backgrounds.front().rec.y < 540) {
		BackToIntro();

		return;
	}

	if (transitionAlpha > 0.0f) transitionAlpha -= 0.01f;

	if (IsKeyPressed(KEY_ENTER)) stateManager->SwitchTo(StateType::LEVEL);


}

void Title::Render(){
	for (auto &i: backgrounds) DrawRectangleRec(i.rec, i.color);

	DrawText("HIDDEN POWER OF X", 1920/6, 450, 100, BLACK);
	DrawText("Press ENTER to START", 1920/6, 575, 25, BLACK);
	DrawRectangleRec(transitionRec, Fade(WHITE, transitionAlpha));

	
}

void Title::ResetBackground(){
	if (!backgrounds.empty()) backgrounds.clear();

	for (int i=0; i < MAX_BACKGROUND; i++){
		int colorValue = GetRandomValue(BACKGROUND_MIN_COLOR, BACKGROUND_MAX_COLOR);
		int sizeValue = GetRandomValue(BACKGROUND_MIN_SIZE, BACKGROUND_MAX_SIZE);

		Background bg = (Background){(Rectangle){GetRandomValue(-BACKGROUND_MIN_SIZE/2, 1920 - BACKGROUND_MIN_SIZE), 6500 - 100*i, sizeValue, sizeValue}, (Color){colorValue, colorValue, colorValue, 255}};
	
		backgrounds.push_back(bg);
	}
}

void Title::BackToIntro(){
	transitionAlpha += 0.01f;

	if (transitionAlpha >= 1.0f) stateManager->SwitchTo(StateType::INTRO);
}