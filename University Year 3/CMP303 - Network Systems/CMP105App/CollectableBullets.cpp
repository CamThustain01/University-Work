#include "CollectableBullets.h"

CollectableBullets::CollectableBullets(Player* player)
{

	

	player_Obj = player; //creates a local variable of the player class 
	
	srand(time(NULL)); //creates the seed for the random function as NULL


	//creates two new variables randomX & randomY as type integers and both equal to zero 
	int randomX = 0;
	int randomY = 0;


	//adds new sound for when the player collides with a bullet
	audio.addSound("sfx/TP_Secret.ogg", "collected");


	//loads a texture for the bullet called bullet
	bullet_texture.loadFromFile("gfx/bullet.png");


	//creates a for loop with the variable i runs the loop until its less than 7
	for (int i = 0; i < 7; i++)
	{
		//sets the texture, size and collision for each bullet in the array
		bullets[i].setTexture(&bullet_texture);
		bullets[i].setSize(sf::Vector2f(25, 23));
		bullets[i].setCollisionBox(sf::FloatRect(0, 0, bullets[i].getSize().x,bullets[i].getSize().y)); //sets the collision boxes to the size of the bullets size

		

		//creates to for loops which will get random numbers for the x and y coordinates
		for (int x = 0; x < 7; x++) 
		{
			int rX = rand() % 1000;
			 randomX = rX;
		}

		for (int y = 0; y < 7; y++)
		{
			int rY = rand() % 550;
			randomY = rY;
		}

		float bulletPostions[2][7] = { { 200.0, 650.0, 321.0, 590.0, 148.0, 702.0, 444.0 }, {314.0, 500.0, 120.0, 630.0, 363.0, 222.0, 487.0} };
	

		//sets the bullets positions to the random numbers and then sets each bullets alive status to true
		bullets[i].setPosition(bulletPostions[0][i], bulletPostions[1][i]);
		bullets[i].setAlive(true);

		
	}
}

CollectableBullets::~CollectableBullets()
{
}

void CollectableBullets::update(float dt)
{
	//calls the collision function
	collision();



	
}



void CollectableBullets::render(sf::RenderWindow* hwnd)
{
	window = hwnd;

	//creates a for loop display the bullets if they are alive
	for (int i = 0; i < 7; i++)

	{
		if(bullets[i].isAlive())
		{
			window->draw(bullets[i]);
			
		}
		
	}
	
	

}

void CollectableBullets::collision()
{

	//creates a for loop so each bullet can be checked for collision
	for (int i = 0; i < 7; i++)
	{
		//checks bounding box between the player and the bullets
		if (Collision::checkBoundingBox(player_Obj, &bullets[i]))
		{

			if (bullets[i].isAlive() == true) //if the bullets are alive 
			{
				score = score + 1; //1 is added to the score variable 
				audio.getSound("collected")->setVolume(50);
				audio.playSoundbyName("collected"); //the collected sound is player
			}

			bullets[i].collisionResponse(NULL); //collision response is set
			bullets[i].setAlive(false); //the bullets alive status is now set to false so its no longer on the screen

		}
		


	}
}

