#include "Level.h"

//Networking 
//creates pointers to networking classes and asigns them to NULL
Server* server_ = NULL;
Client* client_ = NULL;

extern Player* player_; //creates external pointers which are linked with the global pointers within network utils
extern Enemy* enemy_;
extern Enemy2* enemy2_;
extern CollectableBullets* bulletMan_;

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	
	//creates managers for each class
	game_Background = new Background;
	player_Obj = new Player(&windX);
	enemyObject = new Enemy(&windowSize, player_Obj);
	enemyObject2 = new Enemy2(&windowSize, player_Obj);
	gameState = new GameState();
	menu = new MainMenu();
	options = new OptionsScreen();
	paused = new PauseScreen();
	credits = new CreditsScreen();
	dead = new DeathScreen();
	audio = new AudioManager();
	bulletMan = new CollectableBullets(player_Obj);
	// initialise game objects

	//assigns network pointers to game pointers
	player_ = player_Obj;
	bulletMan_ = bulletMan;
	enemy_ = enemyObject;
	enemy2_ = enemyObject2;

	//initialise client and server
	client_ = new Client();
	server_ = new Server();

	

	srand(time(NULL));

	//creates a variable called scale as type integer and equal to three this is used to declare the player, enemy and bullet size 
	int scale = 3;

	//sets the current game state to menu 
	gameState->setCurrentState(State::MENU);

	//declares player object
	player_Text.loadFromFile("gfx/Player-Sheet.png"); //loads the texture from the file
	player_Obj->setInput(input); //sets the input for the player
	player_Obj->setTexture(&player_Text); //sets the texture for the player 
	player_Obj->setSize(sf::Vector2f(19 * scale, 24 * scale)); //sets the size of the player by their height and width multiplied by the scale.
	player_Obj->setCollisionBox(sf::FloatRect(0,0, player_Obj->getSize().x, player_Obj->getSize().y)); //sets the collision to the players size
	player_Obj->setPosition(550, 300); //sets the players position 
	player_Obj->setVelocity(10, 10); //sets the players velocity
	

	windX = window->getSize(); //makes windX to the size of the window


	background.loadFromFile("gfx/bigBackground.png");  //loads in image for the background
	game_Background->setTexture(&background); //sets the background texture
	game_Background->setSize(sf::Vector2f(11038, 675)); //sets the size of the background 

	//creates variables to set the enemies positions
	int randomX1;
	int randomY1;
	int randomX2;
	
	
	//for loops to create 4 random numbers which are used to set the enemies position so its different each time
	for (int x = 0; x < 2; x++)
	{
		int rX = rand() % 425 + 1;
		randomX1 = rX;
	}

	for (int y = 0; y < 2; y++)
	{
		int rY = rand() % 550 + 1;
		randomY1 = rY;
	}

	for (int x = 0; x < 2; x++)
	{
		int rX = rand() % 625 + 1000;
		randomX2 = rX;
	}


	enemy1.loadFromFile("gfx/RED CHASER-Sheet.png");//loads enenmy image from file
	enemyObject->setTexture(&enemy1); //sets the texture for the enemy
	enemyObject->setInput(input); 
	enemyObject->setSize(sf::Vector2f(38 * scale, 45* scale)); //sets the enemies size the height and width by the scale
	enemyObject->setCollisionBox(sf::FloatRect(0, 0, enemyObject->getSize().x,enemyObject->getSize().y)); //sets the collision box to the size of the enemy
	enemyObject->setPosition(randomX1, randomY1); //sets the position of enemy
	enemyObject->setVelocity(5, 5); //sets velocity of enemy

	//this code is the same but for the second enemy just different size, position etc.
	enemy2.loadFromFile("gfx/BLUE SPITTER-Sheet.png");
	enemyObject2->setTexture(&enemy2);
	enemyObject2->setInput(input);
	enemyObject2->setSize(sf::Vector2f(38 * scale, 44 * scale));
	enemyObject2->setCollisionBox(sf::FloatRect(0, 0, enemyObject2->getSize().x,enemyObject2->getSize().y));
	enemyObject2->setPosition(randomX2,randomY1);
	enemyObject2->setVelocity(5, 5);




	//loads in font arial
	if (!pauseFont.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font \n";
	}


	//creates the text on the level to pause the game
	pauseGame.setFont(pauseFont);
	pauseGame.setString("Press P To Pause");
	pauseGame.setFillColor(sf::Color::Black);
	pauseGame.setCharacterSize(18);
	pauseGame.setPosition(10, 610);


	//creates text to displayer lives on screen
	lives.setFont(pauseFont);
	lives.setFillColor(sf::Color::Black);
	lives.setCharacterSize(20);
	lives.setPosition(10, 5);


	//displays the bullets collected 
	bullets_collected.setFont(pauseFont);
	bullets_collected.setFillColor(sf::Color::Black);
	bullets_collected.setCharacterSize(20);
	bullets_collected.setPosition(200, 5);

	//adding music and sounds
	audio->addMusic("sfx/hyrulefield.ogg", "hyrule");
	audio->addMusic("sfx/Cantina.ogg", "Cantina");
	audio->addMusic("sfx/win music 1.ogg", "victory");
	audio->addSound("sfx/smb_1-up.ogg", "collect");
	audio->addSound("sfx/PowerDown10.ogg", "dead");
	

		
	audio->playMusicbyName("hyrule");
	audio->getMusic()->setVolume(100);


}


Level::~Level()
{
	//deletes the pointers 
	delete game_Background;
	delete player_Obj;
	delete enemyObject;
	delete enemyObject2;
	delete gameState;
	delete menu;
	delete options;
	delete paused;
	delete credits;
	delete dead;
	delete audio;
	delete bulletMan;
}

// handle user input
void Level::handleInput(float dt)
{
	if (!isServer)
	{
		player_Obj->handleInput(dt); //handles player object input
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();//close window is player presses esc key
	}



	if (input->isKeyDown(sf::Keyboard::C) && gameState->getCurrentState() == State::MENU)
	{
		input->setKeyUp(sf::Keyboard::C);
		client_->run_client(); //runs the client 
		gameState->setCurrentState(State::LEVEL); //if the player presses p and the game state is set to menu it changes the gamestate level
		audio->stopAllMusic();

	}
	else if (input->isKeyDown(sf::Keyboard::S) && gameState->getCurrentState() == State::MENU)
	{
		input->setKeyUp(sf::Keyboard::S);
		
		server_->run_server();
		isServer = true;  //sets is server variable to true if the user presses S
		player_->predict_server = true; //sets predict server variable to true if the user presses S
		gameState->setCurrentState(State::LEVEL); //if the player presses p and the game state is set to menu it changes the gamestate level
		audio->stopAllMusic();
	}

	if (input->isKeyDown(sf::Keyboard::O) && gameState->getCurrentState() == State::MENU)
	{
		input->setKeyUp(sf::Keyboard::O);
		gameState->setCurrentState(State::OPTIONS);//if the player presse o on the menu it changes to the options gamestate 
	}

	if (input->isKeyDown(sf::Keyboard::BackSpace) && gameState->getCurrentState() == State::OPTIONS)
	{
		input->setKeyUp(sf::Keyboard::BackSpace);
		gameState->setCurrentState(State::MENU); //if player presses backspace it leaves the options gamestate and returns to the menu
	}

	if (input->isKeyDown(sf::Keyboard::P) && gameState->getCurrentState() == State::LEVEL)
	{
		input->setKeyUp(sf::Keyboard::P);
		gameState->setCurrentState(State::PAUSE);//if the player presses p and its on the level gamestate the pause game state is set
	}

	if (input->isKeyDown(sf::Keyboard::P) && gameState->getCurrentState() == State::PAUSE)
	{
		input->setKeyUp(sf::Keyboard::P);
		gameState->setCurrentState(State::LEVEL); // if the player presses p on the pause gamestate it returns back to the level gamestate
	}

	if (input->isKeyDown(sf::Keyboard::BackSpace) && gameState->getCurrentState() == State::PAUSE)
	{
		input->setKeyUp(sf::Keyboard::BackSpace);
		gameState->setCurrentState(State::MENU); //if the player presses backspace on the pause screen it returns to the menu and resets the level
		audio->stopAllMusic();
		audio->playMusicbyName("hyrule");
		shouldReset = true;
	}

	if (input->isKeyDown(sf::Keyboard::M) && gameState->getCurrentState() == State::PAUSE) //if player presses M in pause screen music is stopped
	{
		input->setKeyUp(sf::Keyboard::M);

		if (audio->getMusic()->getVolume() == 100)
		{
			audio->getMusic()->setVolume(0);
		}
		else
		{
			audio->getMusic()->setVolume(100);
		}
	}


	if (input->isKeyDown(sf::Keyboard::P) && gameState->getCurrentState() == State::CREDITS)
	{
		input->setKeyUp(sf::Keyboard::P);
		gameState->setCurrentState(State::MENU); //if the player presses p on the credits to play again it takes them back to menu and resets level
		audio->playMusicbyName("hyrule");
		shouldReset = true;
	}

	if (input->isKeyDown(sf::Keyboard::Escape) && gameState->getCurrentState() == State::CREDITS)
	{
		input->setKeyUp(sf::Keyboard::Escape); //if the player presses escape on credits it closes window
		window->close();
	}

	if (input->isKeyDown(sf::Keyboard::BackSpace) && gameState->getCurrentState() == State::DEAD)
	{
		input->setKeyUp(sf::Keyboard::BackSpace);
		gameState->setCurrentState(State::MENU);//if the player presses backspace on the dead gamestate it takes the player back to the menu and the level is reset
		audio->stopAllMusic();
		audio->playMusicbyName("hyrule");
		shouldReset = true;
	}

	
	

	switch (gameState->getCurrentState()) //switch statement for each gamestates handle input
	{
	case(State::MENU):
		menu->handleInput(dt); //handles input for menu 
		break;
	case(State::LEVEL):
		break;
	case(State::OPTIONS):
		options->handleInput(dt); //handles input for the options
		break;
	case(State::PAUSE):
		paused->handleInput(dt); //handles input for pause screen
		break;
	case(State::CREDITS):
		credits->handleInput(dt); //handles input for credits
		break;
	case(State::DEAD):
		dead->handleInput(dt); //handles input for the dead screen
		break;
	}

}

// Update game objects
void Level::update(float dt)
{


	switch (gameState->getCurrentState())//switch statement for updating gamestates
	{
	case(State::MENU):
		menu->update(dt);//handles update in the menu
		break;
	case(State::LEVEL):
		windowSize = window->getSize(); //sets windowSize to the size of the window
		lives.setString("Players Lives: " + std::to_string(player_Obj->playerLives)); //sets the player lives to a string so they can be displayed on screen and constantly update		
		player_Obj->update(dt); // updates player object
	

		bulletMan->update(dt); //updates the bullets
		// updates the enemies
		enemyObject->update(dt); 

		enemyObject2->update(dt);


		/// NETWORKING CODE
		if (isServer == true) //if boolean variable is true send and receive data from server
		{
			server_->receive_client_data(); //receives client data
			server_->update_client_data(player_, enemy_, enemy2_, bulletMan_, dt);//update game objects based on recieved data
		}
		else { // else send and receive data from client instead
			client_->AddTick(dt); //adds a tick to the client before sending data 
			if (client_->GetTick() >= 0.02)//this value was used as it was the lowest possible value without breaking during brute force testing.
			{								//it has been added so the server can handle all the messages with more objects added value may need to be higher. 
			client_->send_data(); //sends data to server
			client_->ResetTick(); //resets tick to zero once done with
			}
			
		}
		//////////////////////////////////////

		
		
		


		//X axis collision for player
		if (player_Obj->getPosition().x < 0)
		{
			player_Obj->setPosition(0, player_Obj->getPosition().y); //if the players x position is less than 0 they cant move any further
		}

		else if (player_Obj->getPosition().x + 100 > windowSize.x)
		{
			player_Obj->setPosition(windowSize.x - 100, player_Obj->getPosition().y ); // else if the players  x position + 100 is greater than the x size of the window they cant move any further 
		}

		//Y axis collision for player
		if (player_Obj->getPosition().y < 0)
		{
			player_Obj->setPosition(player_Obj->getPosition().x, 0); //if the players y position is less than 0 they cant move anyfurther 
		}

		else if (player_Obj->getPosition().y + 100 > windowSize.y)
		{
			player_Obj->setPosition(player_Obj->getPosition().x, windowSize.y - 100); //else if the  players y position + 100 is greather than the y size of the window they cant move any further
		}

		//Player -> enemy collision
		if (Collision::checkBoundingBox(player_Obj,enemyObject))
		{
			player_Obj->collisionResponse(NULL); //checks collisiton between the player and first enemy
		}

		if (Collision::checkBoundingBox(player_Obj,enemyObject2))
		{
			player_Obj->collisionResponse(NULL); //checks collision between the player and the second enemy
		}
	

		//Enemy -> enemy collision
		if (Collision::checkBoundingBox(enemyObject, enemyObject2))
		{
			enemyObject->collisionResponse(NULL); //checks collision between the two enemies
			
		}

		
		//COMMNET OUT FOR NOW!
		/*if (player_Obj->playerLives < 1 && gameState->getCurrentState() == State::LEVEL)
		{
			audio->playSoundbyName("dead");
			gameState->setCurrentState(State::DEAD); //if the players lives becomes 0 and the gamestate is = level dead sound is played and the gamestate is changed to the dead state
			server_->disconnect_all();
		}*/

		if (bulletMan->score >= 7 && gameState->getCurrentState() == State::LEVEL)
		{
			gameState->setCurrentState(State::CREDITS); //if the score is >= 7 the gamestate is changed to the credits
			audio->stopAllMusic();
			audio->playMusicbyName("victory");
			server_->disconnect_all();
		}


		break;
	case(State::OPTIONS):
		options->update(dt); //manages the options update
		break;
	case(State::PAUSE):
		paused->update(dt); //manages the paused update function
		break;
	case(State::CREDITS):
		credits->update(dt); //manages the credits update function
		break;
	case(State::DEAD):
		dead->update(dt); // manages the dead update function
		break;
	}







}

// Render level
void Level::render()
{
	beginDraw();

	switch (gameState->getCurrentState()) 
	{
	case(State::MENU):
		menu->render(window); //renders the menu
		break;
	case(State::LEVEL):
		window->draw(*game_Background); //renders the level and all the objects within the level
		bulletMan->render(window);
		window->draw(*player_Obj);
		window->draw(*enemyObject);
		window->draw(*enemyObject2);
		window->draw(pauseGame);
		window->draw(lives);
		window->draw(bullets_collected);
		break;
	case(State::OPTIONS):
		options->render(window); //renders the options
		break;
	case(State::PAUSE):
		paused->render(window); //renders the pause screen
		break;
	case(State::CREDITS):
		credits->render(window); //renders the credits screen
		break;
	case(State::DEAD):
		dead->render(window); //renders the dead screen
	}




	endDraw();
}

bool Level::resetLevel()
{
	return shouldReset; //returns should reset 
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color::Black); //window colour black
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}