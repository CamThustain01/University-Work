#pragma once
#include <system/application.h>
#include <input/input_manager.h>
#include "primitive_builder.h"
#include<box2d/Box2D.h>
#include <maths/math_utils.h>
#include "audio_setup.h"
#include "level_assets.h"
#include "game_object.h"


enum ActiveStates {
	None,
	Init,
	Menu,      //enum holding all possible gamestates within game
	Options,
	HowTo,
	Level,
	Win,
	Lose
};


namespace gef {

	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Texture;
	class Renderer3D;
}


class state_management
{
public:

	//instance of states enum
	ActiveStates active_states;

	//acess to audio class
	audio_setup* game_audio_;

	//instance of gameobject ball
	Ball* ball_;

	//pointer access to level assets: ground, player, ball etc.
	level_assets* lvl_assets_;

	//pointers to gef classes
	gef::Font* state_font;
	gef::SpriteRenderer* sprite_renderer_;
	gef::InputManager* state_input_;
	gef::Renderer3D* renderer_3d_;


	//b2 world poimter
	b2World* world_;

	//platform reference 
	gef::Platform& platform_;

	//textures pointers for state backgrounds
	gef::Texture* splash_screen;
	gef::Texture* splash_icon;
	gef::Texture* menu_screen_;
	gef::Texture* options_screen_;
	gef::Texture* htp_screen_;
	gef::Texture* level_screen_;
	gef::Texture* win_screen_;
	gef::Texture* lose_screen_;

	//tecture pointers for buttons
	gef::Texture* circle_button;
	gef::Texture* cross_button;
	gef::Texture* triangle_button;


	
	state_management(gef::Platform& platform); //constructor
	~state_management(); //destructor

	//functions
	void StateHUD(); //state hud
	void StateFont(); //sets up state font

	void StateUpdate(float frame_time); //state update, updates our world, frame time, timer and each individual states update using switch statement
	void StateRender(); //call each states render using a switch statement

	void GameStateInit(); //initilaises world 
	void ChangeGameState(ActiveStates new_state);


	
	void NormalDifficultySetup();
	void HardDifficultySetup();
	void ChangeGravScale();

	void CleanStates();

	//game state functions 
	//init state functions
	void InitStateUpdate();
	void InitStateRender();

	//menu functions
	void MenuStateInit();
	void MenuStateUpdate();
	void MenuStateRender();
	void MenuStateRelease();

	void OptionsInit();
	void OptionsUpdate();
	void OptionsRender();
	void OptionsRelease();

	void HTPinit();
	void HTPupdate();
	void HTPrender();
	void HTPrelease();

	//level functions
	void LevelStateInit();
	void LevelStateUpdate();
	void LevelStateRender();
	void LevelStateRelease();

	//win functions 
	void WinInit();
	void WinUpdate();
	void WinRender();
	void WinRelease();

	//lose function
	void LoseInit();
	void LoseUpdate();
	void LoseRender();
	void LoseRelease();

	//text render functions
	void RenderBack();//renders back text for returning to menu
	void RenderButton(gef::Texture* tex, float x, float y, float z, float w, float h);//renders button icons
	void RenderBackground(gef::Texture* tex);//render gamestate backgrounds
	void RenderGameInfo(char* text, float x, float y, float z, int info);//renders lives and score in level
	void RenderSplashIcon();//renders rotating splash screen icon

	void state_lights();//function setting up lights
	void state_camera();//function setting up camera

private:

	//variables
	float fps_; //fps
	float rotation_;//rotation variable for splash screen icon
	float speed_ = 50;//speed variable for splash screen icon
	float state_timer;//state timer
	bool level_hard_ = false;//boolean variable for deciding if level is hard mode or not


};