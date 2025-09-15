#include "window.hpp"
#include "entity.hpp"
#include "stateManager.hpp"
#include "intro.hpp"
#include "title.hpp"
#include "level.hpp"
#include "shared.hpp"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define GAME_TITLE "Hidden Power of X"
#define TARGET_FPS 60

std::shared_ptr<Window> window;
std::shared_ptr<StateManager> stateManager;

static void UpdateDrawFrame();

int main(int argc, char** argv){
    window = std::make_shared<Window>(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_TITLE);

	std::shared_ptr<SharedContext> sharedContext = std::make_shared<SharedContext>(window);
	stateManager = std::make_shared<StateManager>(sharedContext);

	std::shared_ptr<Intro> intro = std::make_shared<Intro>(stateManager);
	std::shared_ptr<Title> title = std::make_shared<Title>(stateManager);
	std::shared_ptr<Level> level = std::make_shared<Level>(stateManager);
	stateManager->Add(StateType::INTRO, intro);
	stateManager->Add(StateType::TITLE, title);
	stateManager->Add(StateType::LEVEL, level);

	stateManager->SwitchTo(StateType::INTRO);

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else
        SetTargetFPS(TARGET_FPS);

        while (!WindowShouldClose()){
            UpdateDrawFrame();
        }
    #endif
}

static void UpdateDrawFrame(){
	stateManager->Update();

	window->PrepareRender(RAYWHITE);
	stateManager->Render();
	window->StartRender();
}