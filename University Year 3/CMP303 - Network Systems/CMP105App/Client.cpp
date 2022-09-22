#include "Client.h"
#include <cstring>
#include <string>
#include <sstream>

Client::Client()
{

	client_socket.setBlocking(false); //sockets blocking is set to non blocking

}

Client::~Client()
{
}

void Client::run_client()
{

	serverPort = UDPPORT; //server port is set to the port 4321 from network utils

	std::cout << "Connecting to server using local address" << std::endl;

	serverIP = IPADDRESS; //Client automatically connects to server using local address 

	// Send a message to the server
	const char out[] = "Hi, I'm a client";
	if (client_socket.send(out, sizeof(out), serverIP, serverPort) == sf::Socket::Done)//simple message sent to server
	std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;
	else
		return;

	// Receive an answer from anyone (but most likely from the server)
	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	if (client_socket.receive(in, sizeof(in), received, sender, senderPort) == sf::Socket::Done) //simple messages received from the server
	std::cout << "Message received from " << sender << ": \"" << in << "\"" << std::endl;
	else
		return;

}

void Client::send_data()
{
	
		std::vector<char> toSend; //creates a vector of characters called toSend
		std::vector<std::vector<char>>btoSend; //creates a vector vector of characters called btoSend for bullets since theres more than one and are held within an array

		p_message(toSend); //calls p_message function and uses toSend vector

		///check whether message was sent
		if (client_socket.send(toSend.data(), toSend.size(), serverIP, serverPort) == sf::Socket::Done) //sends vector which currently contains the message for player data
			std::cout << "Player data was sent to server! " << std::endl; //lets us know if it was sent
		else 
			return;																						//the following do very similar but for different game objects
		
		e1_message(toSend); //calls first enemy message function
		if (client_socket.send(toSend.data(), toSend.size(), serverIP, serverPort) == sf::Socket::Done)//sends enemy data
			std::cout << "First enemy data was sent to server! " << std::endl;
		else
			return;

		e2_message(toSend); //calls second enemy message function 
		if (client_socket.send(toSend.data(), toSend.size(), serverIP, serverPort) == sf::Socket::Done)//second enemy send 
			std::cout << "Second enemy data was sent to server! " << std::endl;
		else
			return;

		b_message(btoSend); //bullet message uses vector vector of characters since there is multiple 
		for (auto it : btoSend) //iterates through each one and sends 
		{
			if (client_socket.send(it.data(), it.size(), serverIP, serverPort) == sf::Socket::Done)
				std::cout << "Bullet data was sent to server! " << std::endl;
			else
				return;

		}
}




