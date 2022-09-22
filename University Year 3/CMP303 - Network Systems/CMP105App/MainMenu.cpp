#include "MainMenu.h"
MainMenu::MainMenu()
{

	//loads arial texture for file
	if (!texture.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font \n";
	}


	//creates text for the title 
	title.setFont(texture); //sets the font to arial
	title.setString("Pink Herman & The Slugs From Geetar"); //sets the string
	title.setFillColor(sf::Color::Magenta); //sets colour to magenta
	title.setCharacterSize(38); //sets the texts size
	title.setPosition(340, 100); //sets the texts position

	//creates text for the play button
	menu.setFont(texture);
	menu.setString("Client (Press C)");
	menu.setFillColor(sf::Color::Magenta);
	menu.setCharacterSize(24);
	menu.setPosition(400, 200);

	//creates text for the play button
	menu2.setFont(texture);
	menu2.setString("Server (Press S)");
	menu2.setFillColor(sf::Color::Magenta);
	menu2.setCharacterSize(24);
	menu2.setPosition(750, 200);

	//creates the options text setting its size,colour,position
	options.setFont(texture);
	options.setString("How To Play (Press O)");
	options.setFillColor(sf::Color::Magenta);
	options.setCharacterSize(24);
	options.setPosition(490, 300);


	//creates text for the exit option
	exit.setFont(texture);
	exit.setString("Exit (Press Esc)");
	exit.setFillColor(sf::Color::Magenta);
	exit.setCharacterSize(24);
	exit.setPosition(510, 400);



}

MainMenu::~MainMenu()
{
}

void MainMenu::update(float dt)
{
}

void MainMenu::handleInput(float dt)
{
}

void MainMenu::render(sf::RenderWindow* hwnd)
{
	//draws the text
	window = hwnd;
	window->draw(title);
	window->draw(menu);
	window->draw(menu2);
	window->draw(options);
	window->draw(exit);
}
