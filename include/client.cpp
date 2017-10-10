#include <iostream>
#include <string>
#include "SFML/Network.hpp"
#define MOVE 0
using namespace sf;
using namespace std;

class Client {
private:
	TcpSocket socket;
	int port = 53000;
	Board board;
	bool onlineMode;
	Server* server;
	int playerNumber;

public:
	bool myTurn = false;
	
	// If nothing is passed on creation, mode is assumed online
	Client(int playerN) {
		onlineMode = true;
		playerNumber = playerN;
		string ipAddress;
		cout << "Enter IP address to connect to server: " << endl;
		cin >> ipAddress;
		socket.connect(ipAddress, port);
		cout << "Connection established." << endl;
	}
	
	// If a reference to the server is passed, mode is assumed offline
	Client(int playerN, Server* ref) {
		onlineMode = false;
		playerNumber = playerN;
		server = ref;
		cout << "Offline connection established." << endl;
	}
	
	// Returns a reference to the board (to be drawn)
	Board* getBoard() { return &board; }
	
	void onMouseClick(Vector2f coord) {
		int val = board.getCellByCoord(coord);
		// If the click happened on an empty cell
		if (val == 0) {
			int i, j, k;
			board.getIndicesByCoord(i, j, k, coord);
			// Store the values in fixed size integers to send with the packet
			Int8 action = MOVE;
			Int8 iF = i;
			Int8 jF = j;
			Int8 kF = k;
			Packet packet;
			packet << action << iF << jF << kF;
			send(packet);
			myTurn = false;
		}
	}
	
	void send(Packet packet) {
		if (onlineMode) socket.send(packet);
		else server->receiveOffline(playerNumber, packet);
	}
	
	void receiveOffline(Packet packet) {
		alterBoard(packet);
	}
	
	void receiveOnline() {
		Packet packet;
		socket.receive(packet);
		alterBoard(packet);
	}
	
	void alterBoard(Packet packet) {
		Int8 action;
		packet >> action;
		if (action == MOVE) {
			Int8 iF, jF, kF, valF;
			packet >> iF >> jF >> kF >> valF;
			int i = iF;
			int j = jF;
			int k = kF;
			int val = valF;
			board.setCell(i, j, k, val);
			if (val != playerNumber+1) myTurn = true;
		}
	}
	
};