#include "draw.hpp"
#include "intro.hpp"
#include "maze.hpp"
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void draw_map(sf::RenderWindow &window, Maze &maze) {
	int cell_width = MAP_VIEW_WIDTH / MAZE_WIDTH;
	int cell_height = MAP_VIEW_HEIGHT / MAZE_HEIGHT;
	int map_view_x = MAIN_WINDOW_WIDTH - MAP_VIEW_WIDTH;

	sf::RectangleShape rect(sf::Vector2f(cell_width, cell_height));
	rect.setFillColor(sf::Color(255, 255, 0));

	for (int x = 0; x < MAZE_WIDTH; x++ ) {
		for (int y = 0; y < MAZE_HEIGHT; y++ ) {
			if (maze.get_cell(x, y) == Cell::WALL) {
				rect.setPosition(map_view_x + x * cell_width, y * cell_height);
				window.draw(rect);
			}

			if (maze.get_cell(x, y) == Cell::EXIT) {
				rect.setFillColor(sf::Color(0, 128, 0));
				rect.setPosition(map_view_x + x * cell_width, y * cell_height);
				window.draw(rect);
				rect.setFillColor(sf::Color(255, 255, 0));
			}
		}
	}
}

void draw(sf::RenderWindow &window, State &state) {
	if (state.screen == Screen::INTRO) {
		show_intro(window, state.subscreen);
	} else {
		int maze_view_width = MAIN_WINDOW_WIDTH;
		if (state.map_open)
			maze_view_width -= MAP_VIEW_WIDTH;

		state.maze.draw(state.player_x, state.player_y, state.direction, maze_view_width);

		if (state.map_open) {
			draw_map(window, state.maze);
		}

		int text_view_y = MAIN_WINDOW_HEIGHT - TEXT_VIEW_HEIGHT; 
		Painter pass("pass.png");

		if (state.pass == Object::GOOD) {
			int padding = (TEXT_VIEW_HEIGHT - 100) / 2;
			pass.draw(padding, text_view_y + padding);
		}
		
		if (state.screen == Screen::MAN) {
			Painter man("red-hat.png");

			int maze_view_width = MAIN_WINDOW_WIDTH;

			if (state.map_open)
				maze_view_width -= MAP_VIEW_WIDTH;

			int man_x = (maze_view_width - MAN_WIDTH) / 2;
				
			man.draw(man_x, text_view_y - MAN_HEIGHT);
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
