#include "Player.h" 



Player::Player(sf::Vector2u* x)
{
	WindX = x;
	//adds sound for when player is hit
	audio.addSound("sfx/hit35.mp3.ogg", "hit");

	//adds frames for animation moving up 
	MoveDOWN.addFrame(sf::IntRect(0, 0, 19, 24));
	MoveDOWN.addFrame(sf::IntRect(38, 0, 19, 24));
	MoveDOWN.addFrame(sf::IntRect(57, 0, 19, 24));
	MoveDOWN.setFrameSpeed(1.f / 4.f);

	//adds frame for animation moving down
	MoveUP.addFrame(sf::IntRect(95, 0, 19, 24));
	MoveUP.addFrame(sf::IntRect(114, 0, 19, 24));
	MoveUP.addFrame(sf::IntRect(133, 0, 19, 24));
	MoveUP.setFrameSpeed(1.f / 4.f);

	//adds frames for animation moving left
	MoveLR.addFrame(sf::IntRect(165, 0, 13, 24));
	MoveLR.addFrame(sf::IntRect(178, 0, 13, 24));
	MoveLR.addFrame(sf::IntRect(191, 0, 13, 24));
	MoveLR.addFrame(sf::IntRect(204, 0, 13, 24));
	MoveLR.setFrameSpeed(1.f / 4.f);

	
	

}

Player::~Player()
{
}

void Player::update(float dt)
{

	current->animate(dt);
	setTextureRect(current->getCurrentFrame());


	if (predict_server == true) //if the variable is true i.e the the appliction is server then fulfil prediction calculations
	{
		//prediction eqaution  which is used
		//s = prev speed * time + (((prev speed - prev prev speed)* time) / 2)

		t_since_event += dt; //adds delta time to time since last event variable 
		displacement_ = previous_velocity * t_since_event + (((previous_velocity - last_current_velocity) * t_since_event) / 2.0f); //calculates displacment using the players velocity and the time since last event
	
		predicted_pos = last_current_position + displacement_; //new predicted position is the sum of last current position + displacement 
		setPosition(predicted_pos); //update players position 
		
	}

}

void Player::handleInput(float dt)
{
	
	if (input->isKeyDown(sf::Keyboard::Right)) //if the key pressed is the right arrow the player moves right and sets the correct texture
	{
		current = &MoveLR;
		MoveLR.setFlipped(false);
		move_offsetX += 200 * dt;
		move_offsetX = std::min(move_offsetX, 150.0f);
		move_offsetX = std::max(move_offsetX - 150 * dt, 0.0f); //adds drag to movement , slows player down in a direction

	
	}
	else if (input->isKeyDown(sf::Keyboard::Left))//if the key pressed is the left arrow the player moves left and sets the correct texture
	{	
		current = &MoveLR;
		MoveLR.setFlipped(true);
		move_offsetX -= 200 * dt;
		move_offsetX = std::max(move_offsetX, -150.0f);
		move_offsetX = std::min(move_offsetX + 150 * dt, 0.0f); //adds drag to movement , slows player down in a direction
	}

	else if (input->isKeyDown(sf::Keyboard::Up))//if the key pressed is the up arrow the player moves up and sets the correct texture
	{	
		current = &MoveUP;
		move_offsetY -= 200 * dt;
		move_offsetY = std::max(move_offsetY, -150.0f);
		move_offsetY = std::min(move_offsetY + 150 * dt, 0.0f);
	}

	else if (input->isKeyDown(sf::Keyboard::Down))//if the key pressed is the down arrow the player moves down and the correct texture is set
	{
		current = &MoveDOWN;
		move_offsetY += 200 * dt;
		move_offsetY = std::min(move_offsetY, 150.0f);
		move_offsetY = std::max(move_offsetY - 150 * dt, 0.0f);
	}

	move(move_offsetX * dt, move_offsetY * dt);
	
	
}

void Player::collisionResponse(GameObject* collider)
{

	
	//when player is touched by enemy the lose a life and are set back to spawn point
	audio.playSoundbyName("hit");
	//setPosition(550, 300);//when the player collides with the enemy the player respawns to its original position however the player loses one life
	//playerLives = playerLives - 1; 


}



