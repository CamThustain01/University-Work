#include "Server.h"
#include <cstring>
#include <string>
#include <sstream>

Server::Server()
{
	server_socket.setBlocking(false);
}

Server::~Server()
{
}

void Server::run_server()
{

	mainPort = UDPPORT; //main port is set to 4321

	// Listen to messages on the specified port
	if (server_socket.bind(mainPort) == sf::Socket::Done)
	std::cout << "Server is listening to port " << mainPort << ", waiting for a message... " << std::endl;
	else
		return;

	// Wait for a message
	char in[128];
	std::size_t received;

	if(server_socket.receive(in, sizeof(in), received, senderIP, senderPort) == sf::Socket::Done) //receives simple message from client
		std::cout << "Message received from client " << senderIP << ": \"" << in << "\"" << std::endl;
	else
		return;

	// Send an answer to the client
	const char out[] = "Hi, I'm the server";
	if (server_socket.send(out, sizeof(out), senderIP, senderPort) == sf::Socket::Done)
	std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;
	else
		return;

}

void Server::disconnect_all()
{
	const char disc[] = "The Sever has disconnected";
	if(server_socket.send(disc, sizeof(disc), senderIP, senderPort) == sf::Socket::Done)
	std::cout << "Message was sent to client!" << std::endl;
	else
		return;

}

void Server::receive_client_data()
{
	std::size_t tempReceived; //creates temporary ip and ports for recieved data and the address which is receiving from
	sf::IpAddress tempSender;
	unsigned short tempPort;

	std::vector<char> toReceive;//vector of characters for receiving 
	toReceive.resize(sizeof(Message)); //resizes vector to the size of the Message

	while(server_socket.receive(toReceive.data(), sizeof(Message), tempReceived, tempSender, tempPort) == sf::Socket::Done) //received null as number of bytes received is constant, server sends them so ip and port is null already know from server
	{
		sr_msg.push_back(string_to_data(toReceive)); //uses vector of messages to contain the data which has be deserialised string -> data
		std::cout << "Some data was received from client with ID: "<< sr_msg.back().m_Id << " at time: "<< sr_msg.back().m_time<< std::endl;

	}
		return;

}

void Server::update_client_data(Player* player, Enemy* enemy, Enemy2* enemy2, CollectableBullets* bullets,float dt)
{
	
	while (!sr_msg.empty()) //which there is messages being received
	{
		auto current = sr_msg.back(); //create a variable called current of type Message 
		sr_msg.pop_back(); //removes last element in vector, removes from queue
		
		if (current.m_Id == 1 ) //if the current message that has been iterated throughs id is 1 (player)
		{										// and current time is the latest timestamp 

			//quadratic prediction 		
			double seconds = abs(difftime(player->latest_time,current.m_time)); //finds the difference in time between the players latest time and the current time of the message
			player->t_since_event = 0.0f; //set time since event to zero after each receive

			player->previous_velocity = (player->last_current_position - player->previous_position); //players prev velocity is last current position minus previous pos
			player->previous_velocity.x /= seconds; //divides velocity by time in seconds to get distance
			player->previous_velocity.y /= seconds;
			
			player->last_current_velocity = (sf::Vector2f(current.m_position_x, current.m_position_y) - player->last_current_position); //last current velocity is the current positiion - last current postion
			player->last_current_velocity.x /= seconds;  //divides velocity by time for distances
			player->last_current_velocity.y /= seconds;

			player->acceleration_ = player->previous_velocity - player->last_current_velocity; //calculates acceleration using the players prev velocity and last current velocity 
			player->acceleration_.x /= (2 * seconds); //divides acceleration by 2 by seconds
			player->acceleration_.y /= (2 * seconds);

			player->previous_position = player->last_current_position; //make players previous position the last current position
			player->last_current_position = { current.m_position_x, current.m_position_y }; //sets the players last current position to the messages received position
			
			player->setPosition(current.m_position_x, current.m_position_y); //update players position 
			bullets->score = current.m_score;
			player->playerLives = current.m_lives;

			continue;
		}


		if (current.m_Id == 2 && current.m_time > enemy->e_latest_time) //if id is 2 and the current time is > latest time updates enemy1 position and velocity 
		{
			enemy->setPosition(current.m_position_x, current.m_position_y);
			enemy->setVelocity(current.m_velocity_x, current.m_velocity_y);

			enemy->e_latest_time = current.m_time;
			continue;
		}


		if (current.m_Id == 3 && current.m_time > enemy2->e2_latest_time) //if id is 3 and the current time is > latest time updates enemy2 position and velocity
		{
			enemy2->setPosition(current.m_position_x, current.m_position_y);
			enemy2->setVelocity(current.m_velocity_x, current.m_velocity_y);
			enemy2->e2_latest_time = current.m_time;

			continue;
		}


	}

}



