#pragma once
#include "Framework/GameObject.h"
#include<iostream>

class OptionsScreen:public GameObject
{
public: 

	//declares functions for options screen class
	OptionsScreen();
	~OptionsScreen();
	void update(float dt)override;
	void handleInput(float dt)override;
	void render(sf::RenderWindow* hwnd);
	sf::RenderWindow* window;


	//creates objects for font class and an array of text objects called options
	sf::Font texture;
	sf::Text options[5];


};

