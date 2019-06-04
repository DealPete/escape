#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Writer {
	sf::RenderWindow *window;
	sf::Font font;

	void write_text(int x, int y, const char *text, int font_size) {
		sf::Text string(text, font);
		string.setPosition(x, y);
		window->draw(string);
	}

public:
	Writer(sf::RenderWindow *main_window) {
		window = main_window;

		if (!font.loadFromFile("font/PrintChar21.ttf")) {
			cout << "Couldn't load font file. font/PrintChar21.ttf";
			exit(1);
		}
	}
	
	void write(int x, int y, const char *text) {
		write_text(x, y, text, 18);
	}

	void title(int x, int y, const char *text) {
		write_text(x, y, text, 30);
	}
};
