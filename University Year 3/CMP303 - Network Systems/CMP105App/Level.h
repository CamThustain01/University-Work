#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "CollectableBullets.h"
#include "MainMenu.h"
#include "OptionsScreen.h"
#include "PauseScreen.h"
#include "CreditsScreen.h"
#include "DeathScreen.h"
#include <string>
#include <iostream>

#include "Server.h"
#include "Client.h"



class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	sf::Vector2u windowSize;

	void handleInput(float dt);
	void update(float dt);
	void render();
	bool resetLevel();


private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;
	Player* player_Obj;
	MainMenu* menu;
	OptionsScreen* options;
	CreditsScreen* credits;
	PauseScreen* paused;
	DeathScreen* dead;
	CollectableBullets* bulletMan;
	GameObject* game_Background;
	//GameObject* enemyObject;
	//GameObject* enemyObject2;

	Enemy* enemyObject;
	Enemy2* enemyObject2;

	//creates texture objects for the player, enemies and background
	sf::Texture player_Text; 
	sf::Texture background;
	sf::Texture enemy1;
	sf::Texture enemy2;
	
	sf::Vector2u windX; //creates a new vector called windX
	sf::Text pauseGame; //creates a new text object called pauseGame
	sf::Font pauseFont; //creates new font object called pauseFont
	sf::Text lives; //creates a  new text object called lives
	sf::Text bullets_collected; //creates a new text object called bullets_collected

	bool shouldReset = false; //creates a new variable could shouldReset as type boolean and equal to false

	bool isServer = false;
	


};