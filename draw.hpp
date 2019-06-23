#pragma once
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

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
