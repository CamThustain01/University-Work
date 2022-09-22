#pragma once
#include "Framework/GameObject.h"
#include "Framework/Input.h"
#include"Framework/Collision.h"
#include "Framework/Animation.h"
#include"Framework/Vector.h"
#include "Framework/Animation.h"
#include "Player.h"
#include <iostream>
class Enemy2: public GameObject, public Collision, public Input, public Vector
{
public:
	Enemy2(sf::Vector2u* x, Player* player);
	~Enemy2();
	void update(float dt) override;
	sf::Vector2u* windowSize; //creates a vector pointing to window size
	GameObject* player_obj; //creates an a pointer from gameobject called player_obj
	void collisionResponse(GameObject* collider)override;

	const int e2_id = 3;
	time_t e2_latest_time = std::time(0);

protected:
	Animation move; //creates object of called move from the Animation class
	//Animation* current = &animation; //creates an object called current from a pointer of Animation and makes it equal to reference of animation

private:
	//creates private variables and vectors
	float speed; //creates variable called speed as type float
	float acceleration; // creates variable acceleration as type float
	sf::Vector2f target; //creates new vector called target
	sf::Vector2f direction; //creates new vector called direction
};

