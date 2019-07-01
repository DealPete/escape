#pragma once

const int MAZE_WIDTH = 40;
const int MAZE_HEIGHT = 40;

enum Cell {
	WALL = 0,
	EMPTY,
	EXIT,
};

extern int directions[4][2];

class Maze {
	Cell maze[MAZE_WIDTH][MAZE_HEIGHT];

public:
	Cell get_cell(int x, int y) {
		return maze[x][y];
	}

	void draw(int x, int y, int direction);
	Maze();
};
