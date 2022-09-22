#include "CreditsScreen.h"

CreditsScreen::CreditsScreen()
{

	

	//loads font from file displays the cout if it fails
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font \n";
	}


	//creates each line of text on the credit screen setting their colour, size, position and the string
	credits[0].setFont(font);
	credits[0].setString("You Win!");
	credits[0].setFillColor(sf::Color::Green);
	credits[0].setCharacterSize(38);
	credits[0].setPosition(530, 50);

	credits[1].setFont(font);
	credits[1].setString("A Game Created By:");
	credits[1].setFillColor(sf::Color::Magenta);
	credits[1].setCharacterSize(30);
	credits[1].setPosition(510, 200);

	credits[2].setFont(font);
	credits[2].setString("Cameron Thustain\n\nThanks For Playing!");
	credits[2].setFillColor(sf::Color::Magenta);
	credits[2].setCharacterSize(30);
	credits[2].setPosition(510, 345);

	credits[3].setFont(font);
	credits[3].setString("Play Again (Press P)         Exit (Esc)");
	credits[3].setFillColor(sf::Color::Magenta);
	credits[3].setCharacterSize(20);
	credits[3].setPosition(510, 455);
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::update(float dt)
{
	
	
}

void CreditsScreen::handleInput(float dt)
{
}

void CreditsScreen::render(sf::RenderWindow* hwnd)
{
	//draws each line of text on the screen
	window = hwnd;

	for (int i = 0; i < 4; i++)
	{
		window->draw(credits[i]);
	}

	/*window->draw(credits[0]);
	window->draw(credits[1]);
	window->draw(credits[2]);
	window->draw(credits[3]);*/
}
