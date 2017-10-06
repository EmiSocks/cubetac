#include <iostream>
#include "SFML/Network.hpp"
using namespace sf;
using namespace std;

class Server {
private:
	bool onlineMode;
	TcpListener listener;
	TcpSocket clientSocket;
	Client* offlineClient;
	int port = 53000;

public:
	Server(bool online) {
		this->onlineMode = online;
		if (onlineMode) {
			listener.listen(port);
			cout << "Awaiting connection on port " << port << "..." << endl;
			listener.accept(clientSocket);
			cout << "Connection established." << endl;
		}
		else {
			cout << "Running server in offline mode." << endl;
			offlineClient = new Client(false);
		}
	}
	
	void deleteClient() {
		delete offlineClient;
	}
	
};