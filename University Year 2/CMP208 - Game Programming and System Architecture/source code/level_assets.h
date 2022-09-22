#pragma once
#include <system/application.h>
#include<box2d/Box2D.h>
#include"graphics/scene.h"
#include "game_object.h"
#include "audio_setup.h"
#include <graphics/mesh_instance.h>
#include <maths/vector4.h>
#include "primitive_builder.h"

using gef::Vector4;

namespace gef
{
	class Platform;
	class Renderer3D;
	class InputManager;
	class PrimitiveBuilder;
	class SpriteRenderer;
}

class level_assets
{
public:

	//platform reference
	gef::Platform& platform_;

	//renderer reference
	gef::Renderer3D& renderer_;

	//input reference
	gef::InputManager& input_;

	//audio reference
	audio_setup& asset_audio_;

	//create a reference of physics world
	b2World& world_;


	Ball& ball_;//reference to ball 

	//instance of primitive builder
	PrimitiveBuilder* primitive_builder_;


	//constructor
	level_assets(gef::Platform& platform, gef::Renderer3D& renderer, gef::InputManager& input, b2World& world, audio_setup& audio_, Ball& ball); //takes these parameters which are referenced in state management

	//functions
	void init_();


	//functions for loading in player model, ball model and creating terrain meshes
	void load_model();
	void load_balls();
	void create_walls();
	void create_ground_();

	void move_balls(); //func for move the ball to a random x position off screen
	void change_ball_gravity(float scale_); //chages the balls gravity scale depending on players difficulty choice

	void clean_models(); //cleans models when appropriate
	void cleanup_ground(); //cleans terrain when appropriate
	void Update(); //assets update function for setting up transform , input etc.
	void update_ground(); //updates the terrain.

	void render_model(); //renders player model
	void render_balls(); //renders ball
	void render_ground_(); //renders terrain 

	void collisions_(); //collision checks

	//instances of gef
	gef::Scene* scene_asset_; //two scene assets since we have two models. stops a memory leak if we were to use only 1
	gef::Scene* scene_asset_2;
	gef::MeshInstance mesh_instance_; //pointer to mesh instance
	gef::Renderer3D* renderer_3d_; //pointer to renderer 3d

	

private:

	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);//function for loading models
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene); //getting mesh from scene

	//player
	GameObject player_lvl_;
	b2Body* player_body_;

	//ball body
	b2Body* tball_body_;

	//ground variables
	gef::Mesh* ground_mesh; //creates pointer to mesh for ground
	GameObject ground_; //creates static gameobject called ground_
	b2Body* ground_body_; //creates pointer to b2body for ground

	//wall variables
	gef::Mesh* wall_mesh[2]; //crates array of meshes since level has two walls. saves memory
	GameObject walls_[2]; //same for gameobject
	b2Body* wall_body_[2]; //and walls bodies


	
	

	
};

