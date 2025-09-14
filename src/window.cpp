#include "window.hpp"

#include <raymath.h>

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))



Window::Window(int w, int h, const std::string& title){
	internalWidth = 1920;
	internalHeight = 1080;

	Init(w, h, title);
}

Window::~Window(){
	UnloadRenderTexture(target);
    CloseWindow();
}

void Window::PrepareRender(Color color){
	UpdateScaling();

	BeginTextureMode(target);
	ClearBackground(color);
}

void Window::StartRender(){
	EndTextureMode();
	RenderSceneToWindow();
}

Vector2 Window::GetInternalSize(){
	return (Vector2){internalWidth, internalHeight};
}

void Window::UpdateScaling(){
    scale = MIN((float)GetScreenWidth()/internalWidth, (float)GetScreenHeight()/internalHeight);

    Vector2 mouse = GetMousePosition();
    
    virtualMouse.x = (mouse.x - (GetScreenWidth() - (internalWidth*scale))*0.5f)/scale;
    virtualMouse.y = (mouse.y - (GetScreenHeight() - (internalHeight*scale))*0.5f)/scale;
    virtualMouse = Vector2Clamp(virtualMouse, (Vector2){ 0, 0 }, (Vector2){ (float)internalWidth, (float)internalHeight });   

}

void Window::Init(int w, int h, const std::string& title){
	int min_width = w / 5;
	int min_height = h / 5;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(w, h, title.c_str());
    SetWindowMinSize(min_width, min_height);

    target = LoadRenderTexture(internalWidth, internalHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);	
}

void Window::RenderSceneToWindow(){
    BeginDrawing();

    Rectangle src = { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height };
    Rectangle dst = { (GetScreenWidth() - ((float)internalWidth*scale))*0.5f, (GetScreenHeight() - ((float)internalHeight*scale))*0.5f, (float)internalWidth*scale, (float)internalHeight*scale};
    Vector2 origin = {0, 0};
    ClearBackground(BLACK);
    DrawTexturePro(target.texture, src, dst, origin, 0.0f, RAYWHITE);

    EndDrawing();
}