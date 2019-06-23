#include "draw.hpp"
#include "intro.hpp"
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void draw(sf::RenderWindow &window, State state) {
	if (state.screen == Screen::INTRO) {
		show_intro(window, state.subscreen);
	}
}

sf::RenderWindow *Painter::window;
std::map<std::string, sf::Sprite*> Painter::image_map;

void Painter::draw(int x, int y) {
	sprite->setPosition(x, y);
	window->draw(*sprite);
}

void Painter::init(sf::RenderWindow &main_window) {
	sf::Texture *texture;
	sf::Sprite *sprite;

	window = &main_window;
	string images[1] = { "pass.png" };

	for (const string &image : images) {
		texture = new sf::Texture;
		sprite = new sf::Sprite;

		if (!texture->loadFromFile("images/" + image)) {
			cout << "Couldn't load file " << image << ".";
			exit(1);
		}

		sprite->setTexture(*texture);
		Painter::image_map[image] = sprite;
	}
}
