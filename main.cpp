#include <iostream>
#include "SFML/Graphics.hpp"
#include "board.cpp"
#include "client.cpp"
#include "server.cpp"
// #include "grid.cpp"
#define OFFLINE 0
#define SERVER 1
#define CLIENT 2
using namespace sf;

int gamemode = OFFLINE;
Server* server;
Client* client;
int player_turn = 0;

int main() {
	
	// Create the game board
	Board board;
	int (*line)[4][3];
	
	// Initialize server and client
	if (gamemode == OFFLINE) {
		server = new Server(false);
	}
	else if (gamemode == SERVER) {
		server = new Server(true);
	}
	else if (gamemode == CLIENT) {
		client = new Client(true);
	}
	
	// Create the window
	RenderWindow window(VideoMode(800,600), "cubetac");
	
	// Set the window's framerate to the monitor's refresh rate
	window.setVerticalSyncEnabled(true);
	
	// Main loop
	while (window.isOpen()) {
		
		// Handle the window's events
		Event event;
		while (window.pollEvent(event)) {
			// If the window is closed
			if (event.type == Event::Closed) {
				// Free memory
				if (gamemode == OFFLINE) {
					server->deleteClient();
					delete server;
				}
				window.close();
			}
			// If a mouse button is pressed
			else if (event.type == Event::MouseButtonPressed) {
				// If the left mouse button is pressed
				if (event.mouseButton.button == Mouse::Left) {
					
				}
			}
		}
		
		// Clear the render window
		window.clear(Color::White);
		
		window.draw(board);

		// End the frame
		window.display();
		
	}
	
	return 0;
	
}