#include "game_object.h"
#include <system/debug_log.h>

//
// UpdateFromSimulation
// 
// Update the transform of this object from a physics rigid body
//
void GameObject::UpdateFromSimulation(const b2Body* body)
{
	if (body)
	{
		// setup object rotation
		gef::Matrix44 object_rotation;
		object_rotation.RotationZ(body->GetAngle());

		// setup the object translation
		gef::Vector4 object_translation(body->GetPosition().x, body->GetPosition().y, 0.0f);

		// build object transformation matrix
		gef::Matrix44 object_transform = object_rotation;
		object_transform.SetTranslation(object_translation);
		set_transform(object_transform);
	}
}

void GameObject::MyCollisionResponse()
{
	gef::DebugOut("A collision has happened.\n"); //collision response message
}



Player::Player()
{
	set_type(PLAYER); //set type player

}


Ball::Ball()
{
	set_type(BALL); //set type ball
}


Terrain::Terrain()
{
	set_type(TERRAIN); //set type terrain 
}
