#include "Enemy2.h"
Enemy2::Enemy2(sf::Vector2u* x, Player* player)
{
	this->windowSize = x;
	player_obj = player;
	speed = 1.f; //sets to the speed to 1
	acceleration = 40.f; //sets the acceleration to 50
	target = sf::Vector2f(100, 100); //sets the target to vector 100,100


	//sets up enemy moving animation
	move.addFrame(sf::IntRect(0, 0, 38, 44));
	move.addFrame(sf::IntRect(38, 0, 38, 44));
	move.addFrame(sf::IntRect(76, 0, 38, 44));
	move.addFrame(sf::IntRect(114, 0, 38, 44));
	move.addFrame(sf::IntRect(152, 0, 38, 44));
	move.setFrameSpeed(1.f / 8.f);

}
Enemy2::~Enemy2()
{

}

void Enemy2::update(float dt)
{
	move.animate(dt);
	setTextureRect(move.getCurrentFrame());

	//Flips enemies depending on players position
	if (player_obj->getPosition().x > getPosition().x)
	{
		move.setFlipped(false);
	}
	else if (player_obj->getPosition().x < getPosition().x)
	{

		move.setFlipped(true);
	}



	//calculate direction and move
	target = sf::Vector2f(player_obj->getPosition().x, player_obj->getPosition().y); //sets the target to the players position
	direction = target - getPosition(); //sets the direction to the player minus the enemies position
	direction = Vector::normalise(direction); //returns normalised vector direction 
	velocity = ((direction * speed * acceleration) * dt); //sets the velocity equal to direction * speed * acceleration and * by delta time



	if (Vector::magnitude(target - getPosition()) < 10.f) //if the magnitude is less than 10 the position is set to the target
	{
		setPosition(target);
	}

	//X axis //if the enemy tries to go over or below the size of the window along the x axis it stops the enemy in its path
	if (getPosition().x < 0)
	{
		setPosition(0, getPosition().y);
	}

	else if (getPosition().x + getSize().x > windowSize->x)
	{
		setPosition(windowSize->x - getSize().x, getPosition().y);
	}

	//Y axis //if the enemy tries to go over or below the size of the window along the y axis it stops the enemy in its path
	if (getPosition().y < 0)
	{
		setPosition(getPosition().x, 0);
	}

	else if (getPosition().y + getSize().y > windowSize->y)
	{
		setPosition(getPosition().x, windowSize->y - getSize().y);
	}



	//sets the enemies position to its current position + its velocity
	setPosition(getPosition() + velocity);
}

void Enemy2::collisionResponse(GameObject* collider)
{

	

}