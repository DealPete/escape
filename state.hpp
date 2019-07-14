#pragma once
#include "maze.hpp"
#include <SFML/Window.hpp>

enum Screen {
	INTRO,
	MAZE,
	MAN
};

class State {
public:
	bool map_open;
	Maze maze;
	Screen screen;
	int subscreen;

	int player_x, player_y;
	int direction;

	State() {
		map_open = false;
		screen = INTRO;
		subscreen = 0;
	}

	void init();
	bool move_player(sf::Event::KeyEvent key);
};
