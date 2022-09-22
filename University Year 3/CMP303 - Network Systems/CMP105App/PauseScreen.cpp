#include "PauseScreen.h"

PauseScreen::PauseScreen()
{

	//gets arial font from file
	if (!texture.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font \n";
	}
	//creates text for the text objects, declares the string, the colour, the size and position of each
	paused.setFont(texture);
	paused.setString("PAUSED");
	paused.setFillColor(sf::Color::Magenta);
	paused.setCharacterSize(100);
	paused.setPosition(430, 100);

	play.setFont(texture);
	play.setString("Press P To Play");
	play.setFillColor(sf::Color::Magenta);
	play.setCharacterSize(20);
	play.setPosition(525, 300);

	exit.setFont(texture);
	exit.setString("Press M To Mute Music\n\nExit To Menu (Press BackSpace)");
	exit.setFillColor(sf::Color::Magenta);
	exit.setCharacterSize(20);
	exit.setPosition(525, 350);

}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::update(float dt)
{
}

void PauseScreen::handleInput(float dt)
{
}

void PauseScreen::render(sf::RenderWindow* hwnd)
{

	//draws the text to the window.
	window = hwnd;
	window->draw(paused);
	window->draw(play);
	window->draw(exit);
}
