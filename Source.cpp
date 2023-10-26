#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__)
#define new DBG_NEW
#endif
#endif


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "Spawner.h"

using namespace std;

int main()
{
	// Detect for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Kool Particles");

	sf::Clock deltaSrc;

	int maxSpawners = 64;
    std::vector<Spawner> spawners;

	// set random seed
	srand(rand());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (spawners.size() < maxSpawners) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					sf::Vector2f worldPosition(mousePosition.x, mousePosition.y);

					// spawn one spawner at center
					auto newSpawner = Spawner(worldPosition, 32, 500, 32, 1);
					spawners.push_back(newSpawner);
				}
			}
		}
		
		// Extract deltatime
		sf::Time deltaTime = deltaSrc.restart();
		float delta = deltaTime.asSeconds();

		window.clear();
		
		// Update all the spawners
		for (int i = 0; i < spawners.size(); i++) {
			spawners[i].update(delta);
			spawners[i].draw(window);
		}

		// Clean up dead spawners
        for (int i = spawners.size()-1; i >= 0; i--) {
            auto curSpawner = spawners[i];
            if (curSpawner.isDead()) {
                spawners.erase(spawners.begin() + i);
            }
        }

		window.display();
	}

	return 0;
}