#pragma once
#include "SFML//Network.hpp"
#include "Network_utils.h"
#include <iostream>
#include <string>
#include <ctime>

class Client
{
public:

	Client();
	~Client();


	//functions for client
	void run_client();	
	void send_data();
	void update_server_data(Enemy *enemy, Enemy2* enemy2, CollectableBullets* bullets);
	float GetTick() { return client_tick; } ;
	void AddTick(float add) { client_tick += add; };
	void ResetTick() { client_tick = 0.0f; };

private:

	sf::UdpSocket client_socket; //private client variables
	sf::SocketSelector selector;
	sf::IpAddress serverIP;
	unsigned short serverPort;
	
	std::vector<Message>r_msg; //vector of messages for received messages

	float client_tick = 0.0; //client tick variable



};

