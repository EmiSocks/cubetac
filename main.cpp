#include <iostream>
#include "SFML/Graphics.hpp"
#include "board.cpp"
#include "server.cpp"
#include "client.cpp"
// #include "grid.cpp"
#define OFFLINE 0
#define SERVER 1
#define CLIENT 2
using namespace sf;
using namespace std;

// This disaster is because I didn't use header files
void Server::broadcast(Packet packet) {
	for (int n=0; n<2; n++) {
		if (isOnlineClient[n]) clientSocket[n].send(packet);
		else clients[n]->receiveOffline(packet);
	}
}

int gamemode;
int player_turn = 0;
Server* server;
Client* client1;
Client* client2;

int main() {
	
	// Create the game board
	int (*line)[4][3];
	
	cout << "Enter gamemode (0=OFFLINE, 1=SERVER, 2=CLIENT): " << endl;
	cin >> gamemode;
	
	// Initialize server and client
	if (gamemode == OFFLINE) {
		server = new Server();
		client1 = new Client(0, server);
		client2 = new Client(1, server);
		server->addClient(0, client1);
		server->addClient(1, client2);
		client1->myTurn = true;
	}
	else if (gamemode == SERVER) {
		server = new Server();
		client1 = new Client(0, server);
		server->addClient(0, client1);
		server->addClient(1);
		client1->myTurn = true;
	}
	else if (gamemode == CLIENT) {
		client2 = new Client(1);
	}
	
	// Create the window
	RenderWindow window(VideoMode(800,600), "cubetac");
	
	// Set the window's framerate to the monitor's refresh rate
	window.setVerticalSyncEnabled(true);
	
	// Main loop
	while (window.isOpen()) {
		
		// Handle network events
		if (gamemode == SERVER && !client1->myTurn) {
			server->receiveOnline(1);
		}
		else if (gamemode == CLIENT && !client2->myTurn) {
			client2->receiveOnline();
		}
		
		// Clear the render window
		window.clear(Color::White);
		
		if (gamemode == SERVER || gamemode == OFFLINE) {
			Board* board = client1->getBoard();
			window.draw(*board);
		}
		else if (gamemode == CLIENT) {
			Board* board = client2->getBoard();
			window.draw(*board);
		}

		// End the frame
		window.display();
		
		// Handle the window's events
		Event event;
		while (window.pollEvent(event)) {
			
			// If a mouse button is pressed
			if (event.type == Event::MouseButtonPressed) {
				// If the left mouse button is pressed
				if (event.mouseButton.button == Mouse::Left) {
					if (gamemode == SERVER && client1->myTurn) {
						client1->onMouseClick(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (gamemode == CLIENT && client2->myTurn) {
						client2->onMouseClick(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (gamemode == OFFLINE) {
						if (client1->myTurn) client1->onMouseClick(Vector2f(event.mouseButton.x, event.mouseButton.y));
						else if (client2->myTurn) client2->onMouseClick(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
			}
			
			// If the window is closed
			if (event.type == Event::Closed) {
				// Free memory
				if (gamemode == OFFLINE) {
					delete server;
					delete client1;
					delete client2;
				} else if (gamemode == SERVER) {
					delete server;
					delete client1;
				} else if (gamemode == CLIENT) {
					delete client2;
				}
				window.close();
			}
			
		}
		
	}
	
	return 0;
	
}