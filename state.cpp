#include "state.hpp"
#include <SFML/Window.hpp>

void State::move_player(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::Key::Left) {
		direction = (direction + 3) % 4;
	}
	else if (key.code == sf::Keyboard::Key::Right) {
		direction = (direction + 1) % 4;
	}
	else if (key.code == sf::Keyboard::Key::Up) {
		int new_x = player_x + directions[direction][0];
		int new_y = player_y + directions[direction][1];

		if (maze.get_cell(new_x, new_y) != Cell::WALL) {
			player_x = new_x;
			player_y = new_y;
		}
	}
	else if (key.code == sf::Keyboard::Key::Down) {
		direction = (direction + 2) % 4;
	}
}
