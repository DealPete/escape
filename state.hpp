#pragma once
#include "maze.hpp"
#include <SFML/Window.hpp>

enum Screen {
	INTRO,
	MAZE,
	MAN,
};

enum Object {
	NONE,
	GOOD,
	BAD,
};

class State {
public:
	bool map_open;
	Maze maze;
	Screen screen;
	int subscreen;

	Object map = Object::NONE;
	Object pass = Object::GOOD;
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
