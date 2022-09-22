#pragma once
#include "Framework/GameObject.h"
#include <iostream>
class MainMenu : public GameObject
{
public:

	//creates constructor and deconstructor
	MainMenu();
	~MainMenu();

	//declares functions for the main menu
	void update(float dt)override;
	void handleInput(float dt)override;
	void render(sf::RenderWindow* hwnd);
	sf::RenderWindow* window;
	
	//creates text objects and a font object for the text displaying on the main menu
	sf::Text menu;
	sf::Text menu2;
	sf::Text title;
	sf::Text options;
	sf::Text exit;
	sf::Font texture;
};

