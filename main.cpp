#include <iostream>
#include "SFML/Graphics.hpp"

int main() {
	
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800,600), "cubetac");
	
	// Set the window's framerate to the monitor's refresh rate
	window.setVerticalSyncEnabled(true);
	
	// Main loop
	while (window.isOpen()) {
		
		// Handle the window's events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		// Clear the render window
		window.clear(sf::Color::Black);
		
		// End the frame
		window.display();
		
	}
	
	return 0;
	
}