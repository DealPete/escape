#include "writer.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

sf::RenderWindow *Writer::window;
sf::Font Writer::font;

void Writer::write(int x, int y, const char *text) {
	sf::Text string(text, font);
	string.setCharacterSize(font_size);
	string.setPosition(x, y);
	window->draw(string);
}
