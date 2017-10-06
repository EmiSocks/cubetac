#include <iostream>
#include <string>
#include "SFML/Network.hpp"
using namespace sf;
using namespace std;

class Client {
private:
	TcpSocket socket;
	string ipAddress;
	int port = 53000;

public:
	Client(bool online) {
		if (online) {
			cout << "Enter IP address to connect to server: " << endl;
			cin >> ipAddress;
			socket.connect(ipAddress, port);
			cout << "Connection established." << endl;
		}
	}
	
};