#pragma once
#include"Framework/GameObject.h"
#include"Framework/Collision.h"
#include "Framework/AudioManager.h"
#include "Player.h"
#include<iostream>
class CollectableBullets
{
public:
	CollectableBullets(Player* player);
	~CollectableBullets();
	GameObject* player_Obj; //creates a playerObject in the bullet class
	int score = 0; //creates new variable score to 0
	void update(float dt); 
	void render(sf::RenderWindow* hwnd);
	void collision();
	sf::RenderWindow* window;
	sf::Texture bullet_texture; //new texture for the bullets
	AudioManager audio; //creates new audio object from AudioManager Class
	GameObject bullets[7]; //creates an array of bullets as an instance of GameObject

	const int b_id = 4;
	time_t b_latest_time = std::time(0);

};

