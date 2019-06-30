#include "draw.hpp"
#include "intro.hpp"
#include "maze.hpp"
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void draw(sf::RenderWindow &window, State state) {
	if (state.screen == Screen::INTRO) {
		show_intro(window, state.subscreen);
	}
}

void draw_map(sf::RenderWindow &window, Maze maze) {
	int cell_width = MAP_WINDOW_WIDTH / MAZE_WIDTH;
	int cell_height = MAP_WINDOW_HEIGHT / MAZE_HEIGHT;
	sf::RectangleShape rect(sf::Vector2f(cell_width, cell_height));
	rect.setFillColor(sf::Color(255, 255, 0));

	for (int x = 0; x < MAZE_WIDTH; x++ ) {
		for (int y = 0; y < MAZE_HEIGHT; y++ ) {
			if (maze.get_cell(x, y) == Cell::WALL) {
				rect.setPosition(x * cell_width, y * cell_height);
				window.draw(rect);
			}

			if (maze.get_cell(x, y) == Cell::EXIT) {
				rect.setFillColor(sf::Color(0, 128, 0));
				rect.setPosition(x * cell_width, y * cell_height);
				window.draw(rect);
				rect.setFillColor(sf::Color(255, 255, 0));
			}
		}
	}
}

sf::RenderWindow *Painter::window;
std::map<std::string, sf::Sprite*> Painter::image_map;

void Painter::draw(int x, int y) {
	sprite->setPosition(x, y);
	window->draw(*sprite);
}

void Painter::init(sf::RenderWindow &main_window) {
	sf::Texture *texture;
	sf::Sprite *sprite;

	window = &main_window;
	string images[1] = { "pass.png" };

	for (const string &image : images) {
		texture = new sf::Texture;
		sprite = new sf::Sprite;

		if (!texture->loadFromFile("images/" + image)) {
			cout << "Couldn't load file " << image << ".";
			exit(1);
		}

		sprite->setTexture(*texture);
		Painter::image_map[image] = sprite;
	}
}
