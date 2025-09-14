#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__

#include "common.hpp"

#define BACKGROUND_MIN_SIZE 200
#define BACKGROUND_MAX_SIZE 400
#define BACKGROUND_MIN_COLOR 50
#define BACKGROUND_MAX_COLOR 175

struct Background {
	Rectangle rec;
	Color color;
};

#endif