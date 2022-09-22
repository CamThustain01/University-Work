#pragma once
#include "SFML/Network.hpp"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "CollectableBullets.h"


#define UDPPORT 4321  //defined port
#define IPADDRESS sf::IpAddress::getLocalAddress() //ip address is set to local address  of the computer

struct Message { //struct called message which will contain data required to send to server and client

	int m_Id = -1; //current id 
	int m_object; //id of object: player, enemy, enemy2, collectable bullets
	float m_position_x; //x position of object 
	float m_position_y; //y poisition of object 
	float m_velocity_x; //velocity of object
	float m_velocity_y; //velocity of object
	int m_lives; // current lives
	int m_score; //current score
	time_t m_time; //timestamp since udp can send out of order
};

std::vector<char> data_to_string(Message* msg); //serialisation ~ converts data we are sending into a vector of characters
Message string_to_data(std::vector<char> data); // ~ converts that vector of characters back to data i.e Message

void p_message(std::vector<char>& p_data); //message functions for player, enemies and bullets
void e1_message(std::vector<char>& e1_data);
void e2_message(std::vector<char>& e2_data);
void b_message(std::vector<std::vector<char>>& b_data);

time_t t_stamp(time_t timeStamp); //time stamp function for getting it



