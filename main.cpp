#include "intro.hpp"
//#include "game.hpp"
#include "text.hpp"
#include <SFML/Window.hpp>
#include <vector>

std::vector<int> maze;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Escape!");
	Writer writer(&window);

	show_intro(window, writer);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.display();
	}

	return 0;
}
