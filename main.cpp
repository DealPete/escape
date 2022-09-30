#include "intro.hpp"
#include "draw.hpp"
#include "men.hpp"
#include "random.hpp"
#include "state.hpp"
#include "writer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

State state;

int main()
{
	auto main_mode = sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	
	sf::RenderWindow main_window(main_mode, "Escape!");
	main_window.setVerticalSyncEnabled(true);

	Architect::init(main_window);
	Painter::init(main_window);
	Writer::init(main_window);

	state.init();

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
						state.screen = Screen::MAZE;
						state.subscreen = 0;
					}
				}
				else if (state.screen == Screen::MAZE) {
					if (event.key.code == sf::Keyboard::Key::M) {
						state.map_open = !state.map_open;
					}

					if (state.move_player(event.key)) {
						if (rnd(1, 10) == 1) {
							state.screen = Screen::MAN;
							encounter_man(state);
						}
					}
				}
			}
		}

		main_window.clear();
		draw(main_window, state);
		main_window.display();
	}

	return 0;
}
