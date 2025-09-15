#include "intro.hpp"

void Intro::Init(){
	logoPosition.x = stateManager->GetSharedContext()->window->GetInternalSize().x/2 - 128;
	logoPosition.y = stateManager->GetSharedContext()->window->GetInternalSize().y/2 - 128;

	Reset();
}

void Intro::Awake(){
	Reset();
}

void Intro::Update(){
	// I just pasted this from raylib examples cuz I'm lazsy

	 if (state == 0)                 // State 0: Small box blinking
        {
            frameCounter++;

            if (frameCounter == 120)
            {
                state = 1;
                frameCounter = 0;      // Reset counter... will be used later...
            }
        }
        else if (state == 1)            // State 1: Top and left bars growing
        {
            topRecWidth += 4;
            leftRecHeight += 4;

            if (topRecWidth == 256) state = 2;
        }
        else if (state == 2)            // State 2: Bottom and right bars growing
        {
            botRecWidth += 4;
            rightRecHeight += 4;

            if (botRecWidth == 256) state = 3;
        }
        else if (state == 3)            // State 3: Letters appearing (one by one)
        {
            frameCounter++;

            if (frameCounter/12)       // Every 12 frames, one more letter!
            {
                letterCount++;
                frameCounter = 0;
            }

            if (letterCount >= 10)     // When all letters have appeared, just fade out everything
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        }
        else if (state == 4)            // State 4: Reset and Replay
        {
            stateManager->SwitchTo(StateType::TITLE);
        }
}

void Intro::Render(){
	ClearBackground(RAYWHITE);

            if (state == 0)
            {
                if ((frameCounter/15)%2) DrawRectangle(logoPosition.x, logoPosition.y, 16, 16, BLACK);
            }
            else if (state == 1)
            {
                DrawRectangle(logoPosition.x, logoPosition.y, topRecWidth, 16, BLACK);
                DrawRectangle(logoPosition.x, logoPosition.y, 16, leftRecHeight, BLACK);
            }
            else if (state == 2)
            {
                DrawRectangle(logoPosition.x, logoPosition.y, topRecWidth, 16, BLACK);
                DrawRectangle(logoPosition.x, logoPosition.y, 16, leftRecHeight, BLACK);

                DrawRectangle(logoPosition.x + 240, logoPosition.y, 16, rightRecHeight, BLACK);
                DrawRectangle(logoPosition.x, logoPosition.y + 240, botRecWidth, 16, BLACK);
            }
            else if (state == 3)
            {
                DrawRectangle(logoPosition.x, logoPosition.y, topRecWidth, 16, Fade(BLACK, alpha));
                DrawRectangle(logoPosition.x, logoPosition.y + 16, 16, leftRecHeight - 32, Fade(BLACK, alpha));

                DrawRectangle(logoPosition.x + 240, logoPosition.y + 16, 16, rightRecHeight - 32, Fade(BLACK, alpha));
                DrawRectangle(logoPosition.x, logoPosition.y + 240, botRecWidth, 16, Fade(BLACK, alpha));

                //DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

                DrawText(TextSubtext("raylib", 0, letterCount), stateManager->GetSharedContext()->window->GetInternalSize().x/2 - 44, stateManager->GetSharedContext()->window->GetInternalSize().y/2 + 48, 50, Fade(BLACK, alpha));
            }
            else if (state == 4)
            {
                
            }
}

void Intro::Reset(){
	frameCounter = 0;
	letterCount = 0;

	topRecWidth = 16;
	leftRecHeight = 16;
	botRecWidth = 16;
	rightRecHeight = 16;

	state = 0;
	alpha = 1.0f;
}