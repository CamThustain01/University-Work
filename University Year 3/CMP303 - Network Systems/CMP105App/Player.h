#pragma once
#include "Framework/GameObject.h"
#include "Framework/Input.h"
#include"Framework/Collision.h"
#include "Framework/AudioManager.h"
#include "Framework/Animation.h"
#include <algorithm> 




class Player: public GameObject, public Input, public Collision, public AudioManager
{
public:
	Player(sf::Vector2u* x);
	~Player();
	int playerLives = 4; //creates new variable called playerLives as type integer and eqaul to 4
	sf::Vector2u* WindX; //creates new vector called windX


	//creates texture objects for the different directions the player will be facing up,down,left & right 
	sf::Texture facingRight; 
	sf::Texture facingLeft;
	sf::Texture facingBack;
	sf::Texture facingFront;

	//creates an object of a pointer of the audio manager called audio 
	AudioManager audio;

	void update(float dt)override;
	void handleInput(float dt)override;
	void collisionResponse(GameObject* collider)override;
	
	// player network variables
	const int p_id = 1; //objects id
	time_t latest_time = std::time(0); //creates time t variable for players latest time

	float t_since_event = 0.0; //creates a float for time since event, initially 0.0
	bool predict_server = false; //variable for predicting server initially set to false

	//player prediction vectors
	sf::Vector2f acceleration_; //acceleration 
	sf::Vector2f previous_velocity; //previous velocity
	sf::Vector2f last_current_velocity; //last current velocity
	sf::Vector2f displacement_; //displacment 
	sf::Vector2f previous_position; //previous position 
	sf::Vector2f last_current_position; //players last current position
	sf::Vector2f predicted_pos; //predicted position 

	 float move_offsetX = 0.0f; //"Velocity" values
	 float move_offsetY = 0.0f; 

protected:

	//creating objects of the animation class sp we can add the frames for each direction of movement
	Animation MoveUP;
	Animation MoveDOWN;
	Animation MoveLR;
	//creates a pointer to animation called current and makes it equal to a reference of MoveUP
	Animation* current = &MoveDOWN;
	
	
	
};

