#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <graphics/mesh.h>
#include <maths/math_utils.h>
#include <input/sony_controller_input_manager.h>
#include <graphics/sprite.h>
#include "load_texture.h"

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	input_manager_(NULL),
	font_(NULL),
	world_(NULL),
	player_body_(NULL),
	state_timer(0.0f)
{
}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	InitFont();

	input_manager_ = gef::InputManager::Create(platform_);

	//creates new state_management
	states_ = new state_management(platform_);
	states_->GameStateInit();

}

void SceneApp::CleanUp()
{
	delete input_manager_;
	input_manager_ = NULL;

	CleanUpFont();

	//cleans states when appropriate
	states_->CleanStates();
	

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete states_;
	states_ = NULL;    //deletes states pointer when appropriate 

}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	input_manager_->Update();

	//updates states
	states_->StateUpdate(frame_time);
	
	return true;
}

void SceneApp::Render()
{

	//renders states
	states_->StateRender();

}

void SceneApp::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void SceneApp::DrawHUD()
{
	if (font_)
	{
		//display frame rate
		//font_->RenderText(sprite_renderer_, gef::Vector4(850.f, 510.f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
	}
}

void SceneApp::UpdateSimulation(float frame_time)
{
	float timestep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world_->Step(timestep, velocityIterations, positionIterations);
}





