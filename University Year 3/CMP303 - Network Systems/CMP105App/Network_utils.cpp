#include "Network_utils.h"
#pragma warning(disable: 4996)

Player* player_; //creates global pointers
Enemy* enemy_;
Enemy2* enemy2_;
CollectableBullets* bulletMan_;


time_t t_stamp_var; //creates time t variabl for timestamp

std::vector<char> data_to_string(Message* msg)
{
	int offset = 0;

	std::vector<char> output;
	output.resize(sizeof(Message));
	memcpy(output.data(), &msg->m_Id, sizeof(int));
	offset += sizeof(int);
	memcpy(output.data() + offset, &msg->m_object, sizeof(int));
	offset += sizeof(int);
	memcpy(output.data() + offset, &msg->m_position_x, sizeof(float));
	offset += sizeof(float);
	memcpy(output.data() + offset, &msg->m_position_y, sizeof(float)); //converts data to string
	offset += sizeof(float);											//using memory to memory copy, copies bytes from message to the object vector of characters
	memcpy(output.data() + offset, &msg->m_velocity_x, sizeof(float));  //offset is used so the object doesnt become overlapped, uses size of float, int etc as that is the num of bytes to copy
	offset += sizeof(float);
	memcpy(output.data() + offset, &msg->m_velocity_y, sizeof(float));
	offset += sizeof(float);
	memcpy(output.data() + offset, &msg->m_lives, sizeof(int));
	offset += sizeof(int);
	memcpy(output.data() + offset, &msg->m_score, sizeof(int));
	offset += sizeof(int);
	memcpy(output.data() + offset, &msg->m_time, sizeof(time_t));
	
	return output;
}

Message string_to_data(std::vector<char> data)
{
	int offset = 0;

	Message output;
	memcpy(&output.m_Id, data.data() + offset, sizeof(int));
	offset += sizeof(int);
	memcpy(&output.m_object, data.data() + offset, sizeof(int));
	offset += sizeof(int);
	memcpy(&output.m_position_x, data.data() + offset, sizeof(float)); //converts string back to data
	offset += sizeof(float);											//using memory to memory copy, copies bytes from the vector to the object Message
	memcpy(&output.m_position_y, data.data() + offset, sizeof(float)); //again amd offset is used so there is no overlap and adds the number of bytes of the variable type of each piece of data
	offset += sizeof(float);
	memcpy(&output.m_velocity_x, data.data() + offset, sizeof(float));
	offset += sizeof(float);
	memcpy(&output.m_velocity_y, data.data() + offset, sizeof(float));
	offset += sizeof(float);
	memcpy(&output.m_lives, data.data() + offset, sizeof(int));
	offset += sizeof(int);
	memcpy(&output.m_score, data.data() + offset, sizeof(int));
	offset += sizeof(int);
	memcpy(&output.m_time, data.data() + offset, sizeof(time_t));

	return output;
}

void p_message(std::vector<char> &p_data)
{

	Message p_msg;

	p_msg.m_Id = player_->p_id; //player has id 1
	p_msg.m_object = 1;
	p_msg.m_position_x = player_->getPosition().x; //gets position and velocity of player
	p_msg.m_position_y = player_->getPosition().y;
	p_msg.m_velocity_x = player_->getVelocity().x;
	p_msg.m_velocity_y = player_->getVelocity().y;
	p_msg.m_lives = player_->playerLives; //player has 4 lives
	p_msg.m_score = bulletMan_->score; //player will have a score
	p_msg.m_time = t_stamp(t_stamp_var);
	


	p_data.resize(sizeof(p_msg)); //resizes so data is not overwritten 
	 
	p_data = data_to_string(&p_msg); //vector of characters p_data now equals the data of p_msg

}

void e1_message(std::vector<char>& e1_data)
{

	Message e1_msg;

	e1_msg.m_Id = enemy_->e1_id; //enemy 1 has id 2
	e1_msg.m_object = 2;
	e1_msg.m_position_x = enemy_->getPosition().x;
	e1_msg.m_position_y = enemy_->getPosition().y;
	e1_msg.m_velocity_x = enemy_->getVelocity().x;
	e1_msg.m_velocity_y = enemy_->getVelocity().y;
	e1_msg.m_lives = 0; //enemy doesnt have health...
	e1_msg.m_score = 0; //enemy has no score
	e1_msg.m_time = t_stamp(t_stamp_var);
	
	


	e1_data.resize(sizeof(e1_msg));

	e1_data = data_to_string(&e1_msg);
}

void e2_message(std::vector<char>& e2_data)
{
	Message e2_msg;

	e2_msg.m_Id = enemy2_->e2_id; //enemy 2 has id 3
	e2_msg.m_object = 3;
	e2_msg.m_position_x = enemy2_->getPosition().x;
	e2_msg.m_position_y = enemy2_->getPosition().y;
	e2_msg.m_velocity_x = enemy2_->getVelocity().x;
	e2_msg.m_velocity_y = enemy2_->getVelocity().y;
	e2_msg.m_lives = 0; //enemy doesnt have health...
	e2_msg.m_score = 0; //enemy has no score
	e2_msg.m_time = t_stamp(t_stamp_var);
	

	e2_data.resize(sizeof(e2_msg));

	e2_data = data_to_string(&e2_msg);
}

void b_message(std::vector<std::vector<char>>& b_data)
{
	Message b_msg[7]; //creates array of messages for each collectable 
	 
	for (int i = 0; i < 7; i++) //for loop as there is multiple bullets
	{
		
		b_msg[i].m_Id = bulletMan_->b_id + i; //bullet has id 4
		b_msg[i].m_object = 4;
		b_msg[i].m_position_x = bulletMan_->bullets[i].getPosition().x;
		b_msg[i].m_position_y = bulletMan_->bullets[i].getPosition().y;
		b_msg[i].m_velocity_x = 0; //bullets are static dont have a velocity
		b_msg[i].m_velocity_y = 0;
		b_msg[i].m_lives = 0; //bullets dont have lives 
		b_msg[i].m_score = 0; //bullets dont have score
		b_msg[i].m_time = t_stamp(t_stamp_var);


	}


	b_data.resize(0); //resize data to 0
	
	for (int j = 0; j < 7; j++)
	b_data.push_back(data_to_string(&b_msg[j]));
		
	
}

time_t t_stamp(time_t timeStamp)
{ 
	timeStamp = time(nullptr); //sets time t variables time to null
	if (timeStamp != (time_t)(-1)); 
	asctime(gmtime(&timeStamp)), (intmax_t)timeStamp; //sets timestamp to local time

	return timeStamp;
}



