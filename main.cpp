#include "intro.hpp"
#include "draw.hpp"
#include "state.hpp"
#include "writer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

State state;

int main()
{
	auto main_mode = sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	auto map_mode = sf::VideoMode(MAP_WINDOW_WIDTH, MAP_WINDOW_HEIGHT);

	
	sf::RenderWindow main_window(main_mode, "Escape!");
	sf::RenderWindow map_window;
	main_window.setVerticalSyncEnabled(true);
	map_window.setVerticalSyncEnabled(true);

	Architect::init(main_window);
	Painter::init(main_window);
	Writer::init(main_window);

	while (main_window.isOpen())
	{
		sf::Event event;
		while (main_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				main_window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (state.screen == Screen::INTRO) {
					state.subscreen += 1;

					if (state.subscreen == 2) {
						state.screen = Screen::GAME;
						state.map_open = true;
						map_window.create(map_mode, "Map");
					}
				}
				else {
					state.move_player(event.key);
				}
			}
		}

		if (state.map_open) {
			map_window.clear();
			draw_map(map_window, state.maze);
			map_window.display();
		}

		main_window.clear();
		draw(main_window, state);
		main_window.display();
	}

	return 0;
}
