#include "input.hpp"
#include "text.hpp"
#include <SFML/Window.hpp>

void show_intro(sf::Window &window, Writer &writer) {
	writer.title(295, 50, "Escape!"); 
	writer.write(50, 200, "This is a remake of the Apple ][ game");
	writer.write(50, 230, "Escape (1981), by Silas Warner (1949-2004)");

	more(window);
}
