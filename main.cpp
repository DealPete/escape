#include "intro.hpp"
#include "draw.hpp"
#include "state.hpp"
#include "writer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

State state;

int main()
{
	sf::RenderWindow window(sf::VideoMode(2048, 1080), "Escape!");
	Painter::init(window);
	Writer::init(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				state.subscreen += 1;

				if (state.subscreen == 2) {
					state.screen = Screen::GAME;
				}
			}
		}

		window.clear();
		draw(window, state);
		window.display();
	}

	return 0;
}
