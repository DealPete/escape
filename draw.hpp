#pragma once
#include "maze.hpp"
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>

const sf::Color RED = sf::Color(0xdd, 0, 0x33);          // COLOR = 1
const sf::Color DARK_BLUE = sf::Color(0, 0, 0x99);       // COLOR = 2
const sf::Color DARK_GREEN = sf::Color(0, 0x77, 0x22);   // COLOR = 4
const sf::Color DARK_GRAY = sf::Color(0x55, 0x55, 0x55); // COLOR = 5
const sf::Color MED_BLUE = sf::Color(0x22, 0x22, 0xff);  // COLOR = 6
const sf::Color BROWN = sf::Color(0x88, 0x55, 0);        // COLOR = 8
const sf::Color PINK = sf::Color(0xff, 0x99, 0x88);      // COLOR = 11
const sf::Color LIGHT_GREEN = sf::Color(0x11, 0xdd, 0);  // COLOR = 12
const sf::Color WHITE = sf::Color(255, 255, 255);        // COLOR = 15

const int MAIN_WINDOW_WIDTH = 2048;
const int MAIN_WINDOW_HEIGHT = 1080;
const int TEXT_VIEW_HEIGHT = 200;
const int MAN_WIDTH = 1280;
const int MAN_HEIGHT = 960;
const int MAP_VIEW_WIDTH = MAIN_WINDOW_HEIGHT - TEXT_VIEW_HEIGHT;
const int MAP_VIEW_HEIGHT = MAP_VIEW_WIDTH;

class Architect {
private:
	static sf::RenderWindow *window;

public:
	static void init(sf::RenderWindow &main_window);
	static void draw_triangle(sf::Color color, sf::Vector2f, sf::Vector2f, sf::Vector2f);
	static void draw_rectangle(sf::Color color, sf::Vector2f top_left, float width, float height);
};

class Painter {
private:
	static std::map<std::string, sf::Sprite*> image_map;
	static sf::RenderWindow *window;
	sf::Sprite* sprite;

public:
	Painter(std::string sprite_name) {
		sprite = image_map[sprite_name];
	}

	static void init(sf::RenderWindow &main_window);
	void draw(int x, int y);
};

void draw(sf::RenderWindow &window, State &state);
