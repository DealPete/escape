#pragma once
#include "maze.hpp"
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int MAIN_WINDOW_WIDTH = 2048;
const int MAIN_WINDOW_HEIGHT = 1080;
const int MAP_WINDOW_WIDTH = 1000;
const int MAP_WINDOW_HEIGHT = 520;

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
