#pragma once
#include "maze.hpp"
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
using namespace std;

const sf::Color DARK_GREEN = sf::Color(0, 163, 96);   // COLOR = 4
const sf::Color BROWN = sf::Color(96, 114, 3);        // COLOR = 8
const sf::Color LIGHT_GREEN = sf::Color(20, 245, 60); // COLOR = 12
const sf::Color WHITE = sf::Color(255, 255, 255);     // COLOR = 15

const int MAIN_WINDOW_WIDTH = 2048;
const int MAIN_WINDOW_HEIGHT = 1080;
const int MAP_WINDOW_WIDTH = 1000;
const int MAP_WINDOW_HEIGHT = 520;
const int MAZE_VIEW_WIDTH = MAIN_WINDOW_WIDTH;
const int MAZE_VIEW_HEIGHT = MAIN_WINDOW_HEIGHT - 200;

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
	Painter(string sprite_name) {
		sprite = image_map[sprite_name];
	}

	static void init(sf::RenderWindow &main_window);
	void draw(int x, int y);
};

void draw(sf::RenderWindow &window, State state);
void draw_map(sf::RenderWindow &window, Maze maze);
