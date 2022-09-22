#include "OptionsScreen.h"

OptionsScreen::OptionsScreen()
{

	

	//loads in font arial from file
	if (!texture.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font \n";
	}



	//creates each line of text in the options, declaring their size, colour, position and string
	options[0].setFont(texture);
	options[0].setString("HOW TO PLAY");
	options[0].setFillColor(sf::Color::Magenta);
	options[0].setCharacterSize(38);
	options[0].setPosition(340, 100);

	options[1].setFont(texture);
	options[1].setString("Game Controls:");
	options[1].setFillColor(sf::Color::Magenta);
	options[1].setCharacterSize(24);
	options[1].setPosition(340, 180);

	options[2].setFont(texture);
	options[2].setString("MOVE UP - Up Arrow\nMOVE DOWN - Down Arrow\nMOVE LEFT - Left Arrow\nMOVE RIGHT - Right Arrow\n");
	options[2].setFillColor(sf::Color::Magenta);
	options[2].setCharacterSize(18);
	options[2].setPosition(340, 250);

	options[3].setFont(texture);
	options[3].setString("You must collect the bullets to win! Then you can destroy the pesky slugs!\nYou have 4 lives goodluck!\n");
	options[3].setFillColor(sf::Color::Magenta);
	options[3].setCharacterSize(18);
	options[3].setPosition(340, 350);

	options[4].setFont(texture);
	options[4].setString("Back To Home Screen (Press Backspace)");
	options[4].setFillColor(sf::Color::Magenta);
	options[4].setCharacterSize(18);
	options[4].setPosition(10, 550);



	


}

OptionsScreen::~OptionsScreen()
{
}

void OptionsScreen::update(float dt)
{

}

void OptionsScreen::handleInput(float dt)
{

}

void OptionsScreen::render(sf::RenderWindow* hwnd)
{
	//draws each line of text to the window
	window = hwnd;

	window->draw(options[0]);
	window->draw(options[1]);
	window->draw(options[2]);
	window->draw(options[3]);
	window->draw(options[4]);
}
