#include "draw.hpp"
#include "intro.hpp"
#include "maze.hpp"
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void draw(sf::RenderWindow &window, State state) {
	if (state.screen == Screen::INTRO) {
		show_intro(window, state.subscreen);
	} else {
		state.maze.draw(state.player_x, state.player_y, state.direction);
		
		if (state.screen == Screen::MAN) {
			Painter man("red-hat.png");
			int man_x = (MAZE_VIEW_WIDTH - MAN_WIDTH) / 2;
			man.draw(man_x, MAZE_VIEW_HEIGHT - MAN_HEIGHT);
		}
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

void Architect::init(sf::RenderWindow &main_window) {
	window = &main_window;
}

void Architect::draw_triangle(sf::Color color, sf::Vector2f vertex1, sf::Vector2f vertex2, sf::Vector2f vertex3) {
	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, vertex1);
	triangle.setPoint(1, vertex2);
	triangle.setPoint(2, vertex3);
	triangle.setFillColor(color);
	window->draw(triangle);
}

void Architect::draw_rectangle(sf::Color color, sf::Vector2f top_left, float width, float height) {
	sf::RectangleShape rectangle(sf::Vector2f(width, height));
	rectangle.setPosition(top_left);
	rectangle.setFillColor(color);
	window->draw(rectangle);
}

sf::RenderWindow *Painter::window;
sf::RenderWindow *Architect::window;
std::map<std::string, sf::Sprite*> Painter::image_map;

void Painter::draw(int x, int y) {
	sprite->setPosition(x, y);
	window->draw(*sprite);
}

void Painter::init(sf::RenderWindow &main_window) {
	sf::Texture *texture;
	sf::Sprite *sprite;

	window = &main_window;
	std::string images[5] =
	{
		"pass.png",
		"green-hat.png",
		"red-hat.png",
		"dark-blue-hat.png",
		"med-blue-hat.png",
	};

	for (const std::string &image : images) {
		texture = new sf::Texture;
		sprite = new sf::Sprite;

		if (!texture->loadFromFile("images/" + image)) {
			std::cout << "Couldn't load file " << image << ".\n";
			exit(1);
		}

		sprite->setTexture(*texture);
		Painter::image_map[image] = sprite;
	}
}
