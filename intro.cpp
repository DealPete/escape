#include "draw.hpp"
#include "writer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void show_intro(sf::RenderWindow &window, int subscreen) {
	Writer title(100);
	title.write(674, 100, "Escape!");

	Writer text;

	if (subscreen == 0) {
		text.write(100, 300, "This is a remake of the Apple ][ game");
		text.write(100, 350, "Escape (1981), by Silas Warner (1949-2004)");
		text.write(100, 450, "<Press any key>");
	}
	else {
		Painter pass("pass.png");
		pass.draw(700, 800);

		text.write(100, 300, "Use the arrow keys to move around.");
		text.write(100, 400, "I am not allowed to show you the way out of the building.");
		text.write(100, 450, "Ask the people you meet the way out.");

		text.write(100, 550, "Some of them will tell you the truth,");
		text.write(100, 600, "some of them will always lie, and");
		text.write(100, 650, "some may do either one.");
		text.write(100, 700, "This is all I am allowed to tell you.");
		text.write(100, 800, "Here is a pass.");
		text.write(100, 850, "You may need it.");
		text.write(100, 950, "<Press any key>");
	}
}
