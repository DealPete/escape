#include <SFML/Graphics.hpp>
#include "random.hpp"
#include "draw.hpp"
#include "maze.hpp"

int directions[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

bool on_map(int x, int y) {
	return (x >= 1 && x < MAZE_WIDTH - 1 && y >= 1 && y <= MAZE_HEIGHT - 2);
}

void Maze::init() {
	bool carving_maze = true, dir_chosen = false;
	int direction;
	int x = 1, y = 1;

	while (carving_maze) {
		maze[x][y] = Cell::EMPTY;

		if (!dir_chosen) {
			direction = rnd(0, 3);
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
		if (rnd(0, 1) == 1) maze[x][MAZE_HEIGHT - 2] = Cell::EMPTY;
	}

	for (int y = 1; y < MAZE_HEIGHT - 2; y += 2) {
		if (rnd(0, 1) == 1) maze[MAZE_WIDTH - 2][y] = Cell::EMPTY;
	}

	maze[1][0] = Cell::EXIT;
}

void Maze::draw(int x, int y, int direction) {
	sf::Vector2f center(MAZE_VIEW_WIDTH / 2.f, MAZE_VIEW_HEIGHT / 2.f);

	Architect::draw_triangle(
		WHITE,
		sf::Vector2f(0, 0),
		sf::Vector2f(MAZE_VIEW_WIDTH, 0),
		center
	);
	
	Architect::draw_triangle(
		LIGHT_GREEN,
		sf::Vector2f(0, 0),
		sf::Vector2f(0, MAZE_VIEW_HEIGHT),
		center
	);

	Architect::draw_triangle(
		LIGHT_GREEN,
		sf::Vector2f(MAZE_VIEW_WIDTH, MAZE_VIEW_HEIGHT),
		sf::Vector2f(MAZE_VIEW_WIDTH, 0),
		center
	);

	Architect::draw_triangle(
		DARK_GREEN,
		sf::Vector2f(0, MAZE_VIEW_HEIGHT),
		sf::Vector2f(MAZE_VIEW_WIDTH, MAZE_VIEW_HEIGHT),
		center
	);

	int left_dir = (direction + 3) % 4;
	int right_dir = (direction + 1) % 4;
	int depth = 0;
	int draw_x = x;
	int draw_y = y;
	int left_x = x + directions[left_dir][0];
	int left_y = y + directions[left_dir][1];
	int right_x = x + directions[right_dir][0];
	int right_y = y + directions[right_dir][1];

	while (maze[draw_x][draw_y] != Cell::WALL) {
		if (maze[left_x][left_y] != Cell::WALL) {
			Architect::draw_rectangle(
				BROWN,
				sf::Vector2f(
					MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
					MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				),
				MAZE_VIEW_WIDTH / ((depth + 1.f) * (depth + 2.f) * 2.f),
				MAZE_VIEW_HEIGHT / (depth + 2.f)
			);

			Architect::draw_triangle(
				WHITE,
				sf::Vector2f(
					MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
					MAZE_VIEW_HEIGHT * depth/(2.f * (depth + 1.f))
				),
				sf::Vector2f(
					MAZE_VIEW_WIDTH * (depth + 1.f)/(2.f * (depth + 2.f)),
					MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				),
				sf::Vector2f(
					MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
					MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				)
			);

			Architect::draw_triangle(
				DARK_GREEN,
				sf::Vector2f(
					MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
					MAZE_VIEW_HEIGHT - MAZE_VIEW_HEIGHT * depth/(2.f * (depth + 1.f))
				),
				sf::Vector2f(
					MAZE_VIEW_WIDTH * (depth + 1.f)/(2.f * (depth + 2.f)),
					MAZE_VIEW_HEIGHT - MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				),
				sf::Vector2f(
					MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
					MAZE_VIEW_HEIGHT - MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				)
			);
		}

		if (maze[right_x][right_y] != Cell::WALL) {
			Architect::draw_rectangle(
				BROWN,
				sf::Vector2f(
					MAZE_VIEW_WIDTH * (depth + 3.f)/(2.f * (depth + 2.f)),
					MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				),
				MAZE_VIEW_WIDTH / ((depth + 1.f) * (depth + 2.f) * 2.f),
				MAZE_VIEW_HEIGHT / (depth + 2.f)
			);

			Architect::draw_triangle(
				WHITE,
				sf::Vector2f(
					MAZE_VIEW_WIDTH - MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
					MAZE_VIEW_HEIGHT * depth/(2.f * (depth + 1.f))
				),
				sf::Vector2f(
					MAZE_VIEW_WIDTH - MAZE_VIEW_WIDTH * (depth + 1.f)/(2.f * (depth + 2.f)),
					MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				),
				sf::Vector2f(
					MAZE_VIEW_WIDTH - MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
					MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				)
			);

			Architect::draw_triangle(
				DARK_GREEN,
				sf::Vector2f(
					MAZE_VIEW_WIDTH - MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
					MAZE_VIEW_HEIGHT - MAZE_VIEW_HEIGHT * depth/(2.f * (depth + 1.f))
				),
				sf::Vector2f(
					MAZE_VIEW_WIDTH - MAZE_VIEW_WIDTH * (depth + 1.f)/(2.f * (depth + 2.f)),
					MAZE_VIEW_HEIGHT - MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				),
				sf::Vector2f(
					MAZE_VIEW_WIDTH - MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
					MAZE_VIEW_HEIGHT - MAZE_VIEW_HEIGHT * (depth + 1.f)/(2.f * (depth + 2.f))
				)
			);
		}

		draw_x += directions[direction][0];
		draw_y += directions[direction][1];
		left_x += directions[direction][0];
		left_y += directions[direction][1];
		right_x += directions[direction][0];
		right_y += directions[direction][1];
		depth += 1;
	}

	Architect::draw_rectangle(
		BROWN,
		sf::Vector2f(
			MAZE_VIEW_WIDTH * depth/(2.f * (depth + 1.f)),
			MAZE_VIEW_HEIGHT * depth/(2.f * (depth + 1.f))
		),
		MAZE_VIEW_WIDTH/(depth + 1.f),
		MAZE_VIEW_HEIGHT/(depth + 1.f)
	);
}
