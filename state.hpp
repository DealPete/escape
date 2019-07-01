#pragma once
#include "maze.hpp"
#include <SFML/Window.hpp>

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
	int direction;

	State() {
		map_open = false;
		screen = INTRO;
		subscreen = 0;
		player_x = MAZE_WIDTH - 3;
		player_y = MAZE_HEIGHT - 3;
		if (maze.get_cell(player_x - 1, player_y) == Cell::WALL) {
			direction = 3;
		} else {
			direction = 2;
		}
	}

	void move_player(sf::Event::KeyEvent key);
};
