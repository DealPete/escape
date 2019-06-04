#include <SFML/Window.hpp>

void more(sf::Window &window) {
	bool on_page = true;

	while (on_page)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				on_page = false;
			}
		}

		window.display();
	}
}
