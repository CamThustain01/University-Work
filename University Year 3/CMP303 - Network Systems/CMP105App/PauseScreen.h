#pragma once
#include "Framework/GameObject.h"
#include<iostream>
class PauseScreen :public GameObject
{
public:


	//creates constructor and deconstructor and declares the functions used in the pause screen class
	PauseScreen();
	~PauseScreen();
	void update(float dt)override;
	void handleInput(float dt)override;
	void render(sf::RenderWindow* hwnd);
	sf::RenderWindow* window;



	//creates a font object and text objects for the text that will be displayed on the pause screen
	sf::Font texture;
	sf::Text paused;
	sf::Text play;
	sf::Text exit;

};

