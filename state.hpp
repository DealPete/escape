#pragma once
#include "maze.hpp"

enum Screen {
	INTRO,
	GAME,
};

class State {
public:
	Maze maze;
	Screen screen;
	int subscreen;

	State() {
		screen = INTRO;
		subscreen = 0;
	}
};
