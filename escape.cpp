#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
using namespace std;

vector<int> maze;

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "Escape!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	return 0;
}
