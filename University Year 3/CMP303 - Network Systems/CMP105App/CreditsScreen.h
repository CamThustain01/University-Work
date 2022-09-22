#pragma once
#include "Framework/GameObject.h"
#include"Framework/AudioManager.h"
#include<iostream>
class CreditsScreen: public GameObject
{
public:
	CreditsScreen();
	~CreditsScreen();
	void update(float dt)override;
	void handleInput(float dt)override;
	void render(sf::RenderWindow* hwnd);
	sf::RenderWindow* window;
	sf::Font font; //creates font object
	sf::Text credits[4]; //cretas array of objects called credits from the sf text class

	

};

