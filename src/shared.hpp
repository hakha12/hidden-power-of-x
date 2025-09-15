#ifndef __SHARED_HPP__
#define __SHARED_HPP__

#include "common.hpp"
#include "window.hpp"

struct SharedContext {
	SharedContext(std::shared_ptr<Window> win){
		window = win;
	}
	
	std::shared_ptr<Window> window;
};

#endif