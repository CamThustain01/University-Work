#pragma once
#include "SFML//Network.hpp"
#include "SFML/Network//Socket.hpp"
#include "Network_utils.h"
#include <iostream>
#include <string>
class Server
{
public:

	Server();
	~Server();

	void run_server(); //functions for server
	void disconnect_all();
	void receive_client_data();
	void update_client_data(Player* player, Enemy* enemy, Enemy2* enemy2, CollectableBullets* bullets, float dt);
	
	// Create a socket to receive a message from anyone
	sf::UdpSocket server_socket;
	unsigned short mainPort; //create port for server

	sf::IpAddress senderIP; //ip address and port for sending and receiving data
	unsigned short senderPort;


private:

	std::vector<Message> sr_msg; //vector of messages for received data

	
};

