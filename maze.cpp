#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "draw.hpp"
#include "maze.hpp"

int directions[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

bool on_map(int x, int y) {
	return (x >= 1 && x < MAZE_WIDTH - 1 && y >= 1 && y <= MAZE_HEIGHT - 2);
}

Maze::Maze() {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> rnd2_distribution(0, 1);
	std::uniform_int_distribution<int> rnd4_distribution(0, 3);
	auto rnd2 = std::bind ( rnd2_distribution, generator );
	auto rnd4 = std::bind ( rnd4_distribution, generator );

	bool carving_maze = true, dir_chosen = false;
	int direction;
	int x = 1, y = 1;

	while (carving_maze) {
		maze[x][y] = Cell::EMPTY;

		if (!dir_chosen) {
			direction = rnd4();
		}

		dir_chosen = false;

		int x_step = directions[direction][0];
		int y_step = directions[direction][1];
		int x_dest = x + 2 * x_step;
		int y_dest = y + 2 * y_step;
		bool found_wall = false;

		if (on_map(x_dest, y_dest) && maze[x_dest][y_dest] == Cell::WALL) {
			found_wall = true;
		}
		else {
			x_step *= -1;
			y_step *= -1;
			x_dest = x + 2 * x_step;
			y_dest = y + 2 * y_step;
			
			if (on_map(x_dest, y_dest) && maze[x_dest][y_dest] == Cell::WALL) {
				found_wall = true;
			}
		}
		
		if (found_wall) {
			maze[x + x_step][y + y_step] = Cell::EMPTY;
			maze[x + 2 * x_step][y + 2 * y_step] = Cell::EMPTY;
			x += 2 * x_step;
			y += 2 * y_step;
		}
		else {
			int new_x = x, new_y = y;

			while (true) {
				new_x += 2;

				if (new_x > MAZE_WIDTH - 2) {
					new_x = 1;
					new_y += 2;

					if (new_y > MAZE_HEIGHT - 3) {
						new_y = 1;
					}
				}

				if (new_x == x && new_y == y) {
					carving_maze = false;
					break;
				}

				if (maze[new_x][new_y] == Cell::WALL) {

					for (int dir = 0; dir < 4; dir++) {
						int adj_x = new_x + 2 * directions[dir][0];
						int adj_y = new_y + 2 * directions[dir][1];

						if (on_map(adj_x, adj_y) && maze[adj_x][adj_y] == Cell::EMPTY) {
							direction = (dir + 2) % 4;
							dir_chosen = true;
						}
					}

					if (dir_chosen) {
						int dir_x = directions[direction][0];
						int dir_y = directions[direction][1];
						x = new_x - 2 * dir_x;
						y = new_y - 2 * dir_y;

						maze[new_x - dir_x][new_y - dir_y] = Cell::EMPTY;

						break;
					}
				}
			}
		}
	}

	for (int x = 1; x < MAZE_WIDTH - 2; x += 2) {
		if (rnd2() == 1) maze[x][MAZE_HEIGHT - 2] = Cell::EMPTY;
	}

	for (int y = 1; y < MAZE_HEIGHT - 2; y += 2) {
		if (rnd2() == 1) maze[MAZE_WIDTH - 2][y] = Cell::EMPTY;
	}

	maze[1][0] = Cell::EXIT;
}

void Maze::draw() {
	sf::Vector2f center(MAIN_WINDOW_WIDTH / 2, MAIN_WINDOW_HEIGHT / 2);

	Architect::draw_triangle(
		WHITE,
		sf::Vector2f(0, 0),
		sf::Vector2f(MAIN_WINDOW_WIDTH, 0),
		center
	);
	
	Architect::draw_triangle(
		LIGHT_GREEN,
		sf::Vector2f(0, 0),
		sf::Vector2f(0, MAIN_WINDOW_HEIGHT),
		center
	);

	Architect::draw_triangle(
		LIGHT_GREEN,
		sf::Vector2f(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT),
		sf::Vector2f(MAIN_WINDOW_WIDTH, 0),
		center
	);

	Architect::draw_triangle(
		DARK_GREEN,
		sf::Vector2f(0, MAIN_WINDOW_HEIGHT),
		sf::Vector2f(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT),
		center
	);
}
