#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;

class Writer {
	static sf::RenderWindow *window;
	static sf::Font font;
	int font_size;

public:

	Writer() : font_size(36) {}
	Writer(int font_size) : font_size(font_size) {}

	static void init(sf::RenderWindow &main_window) {
		window = &main_window;

		if (!font.loadFromFile("font/PrintChar21.ttf")) {
			cout << "Couldn't load font file. font/PrintChar21.ttf";
			exit(1);
		}
	}

	void write(int x, int y, const char *);
	void title(int x, int y, const char *);
};
