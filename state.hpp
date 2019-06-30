#pragma once
#include "maze.hpp"

enum Screen {
	INTRO,
	GAME,
};

class State {
public:
	bool map_open;
	Maze maze;
	Screen screen;
	int subscreen;

	State() {
		map_open = false;
		screen = INTRO;
		subscreen = 0;
	}
};
