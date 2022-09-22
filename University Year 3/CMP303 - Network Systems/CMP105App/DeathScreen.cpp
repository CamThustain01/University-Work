#include "DeathScreen.h"

DeathScreen::DeathScreen()
{

	//loads in texture from file 
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font \n";
	}


	
	death.setFont(font); //sets the font for the text to arial
	death.setString("YOU DIED"); //sets the string fot thex text to YOU DIED
	death.setFillColor(sf::Color::Red); //sets the text colour to red
	death.setCharacterSize(40); //sets the size to 40
	death.setPosition(550, 300); //sets the texts position

	respawn.setFont(font); //sets the font
	respawn.setString("Back To Menu (Press Backspace)"); //sets string
	respawn.setFillColor(sf::Color::Red); //sets the texts colour to red
	respawn.setCharacterSize(20); //sets its size
	respawn.setPosition(10, 550); //sets the texts position
}

DeathScreen::~DeathScreen()
{
}

void DeathScreen::update(float dt)
{
}

void DeathScreen::handleInput(float dt)
{
}

void DeathScreen::render(sf::RenderWindow* hwnd)
{
	//draws the text
	window = hwnd;
	window->draw(death);
	window->draw(respawn);

}
