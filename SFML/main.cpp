#include<SFML/Graphics.hpp>
#include<game-runner.h>
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 450, 32), "SUPER GRA");

	int x = testMethod();
	std::cout << x << std::endl;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear(sf::Color::Magenta);
		window.display();
	}

	return 0;
}