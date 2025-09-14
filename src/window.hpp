#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "common.hpp"

class Window {
	public:
		Window(int w, int h, const std::string& title);
		~Window();

		void PrepareRender(Color color);
		void StartRender();

		Vector2 GetInternalSize();
	
	private:
		void Init(int w, int h, const std::string& title);

		void UpdateScaling();
		void RenderSceneToWindow();

		RenderTexture2D target;
		Vector2 virtualMouse;
		float scale;
		int internalWidth;
		int internalHeight;	
};

#endif