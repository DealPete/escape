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
	int player_x, player_y;

	State() {
		map_open = false;
		screen = INTRO;
		subscreen = 0;
		player_x = MAZE_WIDTH - 3;
		player_y = MAZE_HEIGHT - 3;
	}
};
