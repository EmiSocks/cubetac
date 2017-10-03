#include <iostream>
#include "SFML/Graphics.hpp"
#include "grid.cpp"
using namespace sf;

int main() {
	
	// Create the window
	RenderWindow window(VideoMode(800,600), "cubetac");
	
	// Set the window's framerate to the monitor's refresh rate
	window.setVerticalSyncEnabled(true);
	
	Grid grid;
	
	grid.setPosition(100, 100);
	
	// Main loop
	while (window.isOpen()) {
		
		// Handle the window's events
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		
		// Clear the render window
		window.clear(Color::White);
		
		window.draw(grid);

		// End the frame
		window.display();
		
	}
	
	return 0;
	
}