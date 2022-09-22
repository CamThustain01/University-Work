#pragma once
#include "Framework/GameObject.h"
#include <iostream>
class DeathScreen: public GameObject
{
public:

	DeathScreen();
	~DeathScreen();
	void update(float dt)override;
	void handleInput(float dt)override;
	void render(sf::RenderWindow* hwnd);
	sf::RenderWindow* window;
	sf::Font font; //creates font object from font class
	sf::Text death; //creates a text object named death
	sf::Text respawn; //creates a text object named respawn
};

