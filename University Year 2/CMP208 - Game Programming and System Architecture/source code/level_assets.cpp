#include "level_assets.h"
#include <system/platform.h>
#include <graphics/renderer_3d.h>
#include "input/sony_controller_input_manager.h"
#include "input/input_manager.h"
#include <maths/math_utils.h>
#include <system/debug_log.h>
#include <cstdlib>
level_assets::level_assets(gef::Platform& platform, gef::Renderer3D& renderer, gef::InputManager& input, b2World& world, audio_setup& audio_, Ball& ball):
	primitive_builder_(NULL),
	platform_(platform),
	renderer_(renderer),
	input_(input),
	world_(world),
	asset_audio_(audio_),
	ball_(ball),
	scene_asset_(NULL),
	scene_asset_2(NULL)
{
}

void level_assets::init_()
{
	primitive_builder_ = new PrimitiveBuilder(platform_);
}

void level_assets::load_model()//init
{
	//sets game object types
	player_lvl_.set_type(PLAYER);//sets player gameobject to type PLAYER
	

	//loads models
	const char* scene_asset_file = "player-level.scn";//loads in player model
	scene_asset_ = LoadSceneAssets(platform_, scene_asset_file);
	if (scene_asset_)
	{
		player_lvl_.set_mesh(GetMeshFromSceneAssets(scene_asset_));//sets gaemobject to scene asset

	}


	//player physics
	b2BodyDef bodydef;
	bodydef.type = b2_dynamicBody;
	bodydef.position = b2Vec2(0.0f, -0.75f);
	bodydef.userData.pointer = reinterpret_cast<uintptr_t>(&player_lvl_);

	player_body_ = world_.CreateBody(&bodydef);//sets player body to body def
	

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.01f);//set players box

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;//sets players density
	fixtureDef.friction = 6.0f;//sets players friction higher so player doesnt "slide" along terrain

	b2Fixture* fixture = player_body_->CreateFixture(&fixtureDef);//creates pointer to fixture which equals player bodys fixture def

	
	player_lvl_.UpdateFromSimulation(player_body_);//updates player
	/////////


}

void level_assets::load_balls()
{
	//sets gameobject to type ball
	ball_.set_type(BALL);

	const char* scene_asset_file2 = "tennis-ball.scn"; //loads in ball file
	scene_asset_2 = LoadSceneAssets(platform_, scene_asset_file2);  
	if (scene_asset_2)
	{
		ball_.set_mesh(GetMeshFromSceneAssets(scene_asset_2));//sets gameobject to model 
	}


	//ball physics
	b2BodyDef bodydef2;
	bodydef2.type = b2_dynamicBody;//set bodies type
	bodydef2.position = b2Vec2(-1.0, 3.0);//set bodies position
	bodydef2.userData.pointer = reinterpret_cast<uintptr_t>(&ball_);

	tball_body_ = world_.CreateBody(&bodydef2);//create ball body

	b2PolygonShape dynamicBox2;
	dynamicBox2.SetAsBox(0.5, 0.03);//set bodies box

	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &dynamicBox2;//set bodies shape
	fixtureDef2.density = 1.0f;//sets bodies density
	fixtureDef2.friction = 0.5f;//set bodies friction

	//create fixture for body
	b2Fixture* fixture2 = tball_body_->CreateFixture(&fixtureDef2);

	
	ball_.UpdateFromSimulation(tball_body_); //updates ball phyiscs body

	////////////
}

void level_assets::create_walls()
{
	//wall dimensions
	gef::Vector4 wall_dimensions(0.1f, 0.5f, 0.5f);//sets up walls dimensions

	for (int i = 0; i < 2; i++)
	{
		walls_[i].set_type(TERRAIN);//sets both walls to type terrain
		wall_mesh[i] = primitive_builder_->CreateBoxMesh(wall_dimensions);
		walls_[i].set_mesh(wall_mesh[i]);//creates both walls and sets their meshes

	}


	//physics bodies
	b2BodyDef body_def;
	body_def.type = b2_staticBody;//wall is static wont be moving
	body_def.position = b2Vec2(3.7, -0.70);//first walls position 
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(&walls_[0]);

	//1st wall
	wall_body_[0] = world_.CreateBody(&body_def);//creates wall body 


	//create shape
	b2PolygonShape wall_shape_;
	wall_shape_.SetAsBox(wall_dimensions.x(), wall_dimensions.y());//sets box to walls dimension

	//wall fixtures
	//create fixture
	b2FixtureDef fixture_def;
	fixture_def.shape = &wall_shape_;

	//create fixture on rigid body
	wall_body_[0]->CreateFixture(&fixture_def);


	//2nd wall
	//physics bodies
	b2BodyDef body_def2;
	body_def2.type = b2_staticBody;
	body_def2.position = b2Vec2(-3.7, -0.70);
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(&walls_[1]);

	wall_body_[1] = world_.CreateBody(&body_def2);

	//create shape
	b2PolygonShape wall_shape_2;
	wall_shape_2.SetAsBox(wall_dimensions.x(), wall_dimensions.y());

	b2FixtureDef fixture_def2;
	fixture_def2.shape = &wall_shape_2;

	//create fixture on rigid body
	wall_body_[1]->CreateFixture(&fixture_def2);

	//update visuals
	for (int i = 0; i <= 1; i++)
	{
		walls_[i].UpdateFromSimulation(wall_body_[i]);//updates both walls
	}

}

void level_assets::create_ground_()
{
	//ground dimensions
	gef::Vector4 ground_dimensions(4.5f, 0.25f, 0.5f);//sets up grounds dimensions
	//set up mesh
	ground_mesh = primitive_builder_->CreateBoxMesh(ground_dimensions);
	ground_.set_mesh(ground_mesh);
	ground_.set_type(TERRAIN);//set type to terrain 

	//create a physics body
	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position = b2Vec2(0.0f, -1.0f);
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(&ground_);

	ground_body_ = world_.CreateBody(&body_def);//creates boyd

	//create the shape
	b2PolygonShape shape_;
	shape_.SetAsBox(ground_dimensions.x(), ground_dimensions.y());//set collision box


	//create fixture
	b2FixtureDef fixture_def;
	fixture_def.shape = &shape_;
	fixture_def.friction = 2.5f;//set friction to 2.5f

	b2Fixture* static_fixture = ground_body_->CreateFixture(&fixture_def);//creates pointer to fixture to equal physics body

	//create fixture on rigid body
	ground_body_->CreateFixture(&fixture_def);

	//update visuals
	ground_.UpdateFromSimulation(ground_body_);
}

void level_assets::move_balls()
{
	//give balls random x starting position
	float randX = (rand() % 5) - 1 ;//create a random position variable
	b2Vec2 changeX = b2Vec2(randX, 3.0); //implement into a b2vec2
	tball_body_->SetTransform(changeX, tball_body_->GetAngle());//set transform to random X position
	tball_body_->SetLinearVelocity(b2Vec2(0,0));//linerar velocity is set to 0,0 after transform so physics body doesnt speed up
	tball_body_->SetAwake(true);//after transform set body to awake
}

void level_assets::change_ball_gravity(float scale_)
{
	tball_body_->SetGravityScale(scale_);//will change balls gravity depending on difficulty of the level
}


void level_assets::clean_models()
{
	if (scene_asset_)
	{
		delete scene_asset_;//delete scene assets once done
		scene_asset_ = NULL;
	}
}

void level_assets::cleanup_ground()
{
	if (ground_mesh)
	{
		delete ground_mesh;
		ground_mesh = NULL;
	}

	if (primitive_builder_)
	{
		delete primitive_builder_;
		primitive_builder_ = NULL;							//will checks these individually whether to delete or not. If its not null then delete...
	}

	if (wall_mesh[0])
	{
		delete wall_mesh[0];
		wall_mesh[0] = NULL;
	}

	if (wall_mesh[1])
	{
	
	delete wall_mesh[1];
	wall_mesh[1] = NULL;
	}
}

void level_assets::Update()
{
	input_.Update();
	
	gef::SonyControllerInputManager* controllerManager = input_.controller_input();//sets up input for player
	if (controllerManager)
	{

		const gef::SonyController* controller = controllerManager->GetController(0);

		
		if (controller->buttons_down() & gef_SONY_CTRL_RIGHT)
		{
	
			//moves player left by applying force to center
			player_body_->ApplyForceToCenter(b2Vec2(1.25, 0), true);
			asset_audio_.play_sound_(1);//plays movement sound
			
			
		}
		else if(controller->buttons_down() & gef_SONY_CTRL_LEFT)
		{
			//moves player to right by applying force to center
			player_body_->ApplyForceToCenter(b2Vec2(-1.25, 0), true);
			asset_audio_.play_sound_(1); //plays movement sound
			
		}
		

	}

	gef::Matrix44 player_transform, ball_transform, scale;//creates transform matrix for player, ball and the balls scale


	player_transform.SetIdentity(); //sets player identity
	player_transform.RotationZ(player_body_->GetAngle()); //sets rotation of player
	player_transform.SetTranslation(gef::Vector4(player_body_->GetPosition().x, player_body_->GetPosition().y, 0.0f));//sets up translation to players body



	scale.Scale(gef::Vector4(7, 7, 0));//scales ball first 
	ball_transform.SetIdentity();//set up matrices for ball
	ball_transform.RotationZ(tball_body_->GetAngle());
	ball_transform.SetTranslation(gef::Vector4(tball_body_->GetPosition().x, tball_body_->GetPosition().y, 0.0f));
	
	player_lvl_.set_transform(player_transform);//set player transform
	ball_.set_transform(scale * ball_transform);//set ball transform

	collisions_();//calls collision function ,checks every frame
}

void level_assets::update_ground()
{
	//update physics world
	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world_.Step(timeStep, velocityIterations, positionIterations);//updates world for ground
}

void level_assets::render_model()
{
	//renders player model
	renderer_.DrawMesh(player_lvl_);
}

void level_assets::render_balls()
{
	//renders balls
	renderer_.DrawMesh(ball_);
}

void level_assets::render_ground_()
{
	//render ground
	renderer_.set_override_material(&primitive_builder_->green_material());//sets material to green
	renderer_.DrawMesh(ground_); //draws mesh
	renderer_.set_override_material(NULL);

	//render walls
	renderer_.set_override_material(&primitive_builder_->green_material());//sets material to green
	renderer_.DrawMesh(walls_[0]);//draws walls 
	renderer_.DrawMesh(walls_[1]);
	renderer_.set_override_material(NULL);

}



void level_assets::collisions_()
{

	// collision detection
	// get the head of the contact list
	b2Contact* contact = world_.GetContactList();
	// get contact count
	int contact_count = world_.GetContactCount();

	bool collision_check_ = true;

	for (int contact_num = 0; contact_num < contact_count && collision_check_; ++contact_num)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies player and ball
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();


			// DO COLLISION RESPONSE HERE
			Player* player = NULL;
			Ball* ball = NULL; //creates pointer of gameobject subclasses makes them null
			Terrain* terrain = NULL;

			GameObject* gameObjectA = NULL; //makes pointers of gameobject equal to null
			GameObject* gameObjectB = NULL;

			gameObjectA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer); 
			gameObjectB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);
			

			if (gameObjectA)
			{
				if (gameObjectA->type() == PLAYER)//checks if object a is player type 
				{
					player = reinterpret_cast<Player*>(bodyA->GetUserData().pointer);
				}
				else if (gameObjectA->type() == BALL)// checks if object a is ball type
				{
					ball = reinterpret_cast<Ball*>(bodyA->GetUserData().pointer);           //if anything of these convert pointer of another pointer
				}

				else if (gameObjectA->type() == TERRAIN) //checks if object a is terrain type 
				{
					terrain = reinterpret_cast<Terrain*>(bodyA->GetUserData().pointer);
				}
			}

			if (gameObjectB)
			{
				if (gameObjectB->type() == PLAYER)
				{
					
					player = reinterpret_cast<Player*>(bodyB->GetUserData().pointer);
				}
				else if (gameObjectB->type() == BALL)
				{
					ball = reinterpret_cast<Ball*>(bodyB->GetUserData().pointer);				//same checks but for object b this time....
				}
				else if (gameObjectB->type() == TERRAIN)
				{
					terrain = reinterpret_cast<Terrain*>(bodyB->GetUserData().pointer);
				}
			}

			if (ball && player)   //if a ball and player collide do the following:
			{
				ball->IncreaseScore(1);//increase the score if collision is made with player
				asset_audio_.play_sound_(4);//if player and ball collider play collision sound
				move_balls();//randomly transform balls
				collision_check_ = false;
				
			}

			if (ball && terrain) //if ball or any form of terrain collide do the following:
			{
				ball->DecreaseLives(1);//if wall and ball collide decrement health
				asset_audio_.play_sound_(3);//if wall and ball collide play collision sound
				move_balls();//randomly transform balls
				collision_check_ = false;
			}
		}

		// Get next contact point
		contact = contact->GetNext();
	}

}


gef::Scene* level_assets::LoadSceneAssets(gef::Platform& platform, const char* filename)
{
	gef::Scene* scene = new gef::Scene();

	if (scene->ReadSceneFromFile(platform, filename))
	{
		// if scene file loads successful
		// create material and mesh resources from the scene data
		scene->CreateMaterials(platform);
		scene->CreateMeshes(platform);
	}
	else
	{
		delete scene;
		scene = NULL;
	}

	return scene;
}

gef::Mesh* level_assets::GetMeshFromSceneAssets(gef::Scene* scene)
{
	gef::Mesh* mesh = NULL;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
		mesh = scene->meshes.front();

	return mesh;
}

