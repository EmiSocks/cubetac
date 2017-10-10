#include <iostream>
#include "SFML/Network.hpp"
#define MOVE 0
using namespace sf;
using namespace std;

class Server {
private:
	bool onlineMode;
	TcpListener listener;
	TcpSocket clientSocket[2];
	int port = 53000;
	int playerTurn = 0;
	Client* clients[2];
	bool isOnlineClient[2];
	Board board;

public:
	Server() {
		listener.listen(port);
	}
	
	// If nothing is passed, mode is assumed online
	addClient(int playerNumber) {
		cout << "Awaiting connection on port " << port << "..." << endl;
		listener.accept(clientSocket[playerNumber]);
		cout << "Connection established." << endl;
		isOnlineClient[playerNumber] = true;
	}
	
	addClient(int playerNumber, Client* client) {
		clients[playerNumber] = client;
		cout << "Offline connection established." << endl;
		isOnlineClient[playerNumber] = false;
	}
	
	void receiveOffline(int playerNumber, Packet packet) {
		if (playerNumber == playerTurn) {
			alterBoard(playerNumber, packet);
			nextPlayerTurn();
		}
	}
	
	void receiveOnline(int playerNumber) {
		Packet packet;
		clientSocket[playerNumber].receive(packet);
		if (playerNumber == playerTurn) {
			alterBoard(playerNumber, packet);
			nextPlayerTurn();
		}
	}
	
	void alterBoard(int playerNumber, Packet packet) {
		Int8 action;
		packet >> action;
		if (action == MOVE) {
			Int8 iF, jF, kF;
			packet >> iF >> jF >> kF;
			int i = iF;
			int j = jF;
			int k = kF;
			if (board.getCell(i,j,k) == 0) {
				int val = playerNumber+1;
				board.setCell(i, j, k, val);
				Packet packetB;
				Int8 action = MOVE;
				Int8 valF = val;
				packetB << action << iF << jF << kF << valF;
				broadcast(packetB);
			}
		}
	}
	
	void broadcast(Packet packet) {
		for (n=0; n<2; n++) {
			if (isOnlineClient[n]) clientSocket[n].send(packet);
			else clients[n]->receiveOffline(packet);
		}
	}
	
	int getPlayerTurn() {
		return playerTurn;
	}
	
	void nextPlayerTurn() {
		if (playerTurn == 0) playerTurn = 1;
		else playerTurn = 0;
	}
	
	Board* getBoard() { return &board; }
	
};