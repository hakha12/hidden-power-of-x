#ifndef __SHARED_HPP__
#define __SHARED_HPP__

#include "common.hpp"
#include "window.hpp"
#include "audio.hpp"

struct SharedContext {
	SharedContext(std::shared_ptr<Window> win, std::shared_ptr<Audio> aud){
		window = win;
		audio = aud;
	}
	
	std::shared_ptr<Window> window;
	std::shared_ptr<Audio> audio;
};

#endif