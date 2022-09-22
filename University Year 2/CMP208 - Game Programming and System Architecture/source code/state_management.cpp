#include "state_management.h"
#include "load_texture.h"
#include <input/sony_controller_input_manager.h>
#include <graphics/sprite_renderer.h>
#include <graphics/sprite.h>
#include <graphics/font.h>
#include <system/platform.h>
#include <graphics/renderer_3d.h>
state_management::state_management(gef::Platform& platform) :

	state_font(NULL),
	state_input_(NULL),
	renderer_3d_(NULL),
	sprite_renderer_(NULL),
	menu_screen_(NULL),
	active_states(ActiveStates::None),
	state_timer(0.0f),
	platform_(platform)
{
}

state_management::~state_management()
{
	if (ball_)//makes deleting ball_ conditional to not cause any null pointers
	{
		delete ball_;
		ball_ = NULL;
	}
}

void state_management::GameStateInit()
{
	//creates 3d renderer
	renderer_3d_ = gef::Renderer3D::Create(platform_);
	
	//creates sprite renderer
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	StateFont();

	// initialise input manager
	state_input_ = gef::InputManager::Create(platform_);

	//create ball
	ball_ = new Ball();

	//create physics world
	b2Vec2 gravity(0.0, -9.8);
	world_  = new b2World(gravity);

	//initialise buttons here (they may be used in other gamestates)
	splash_screen = CreateTextureFromPNG("splash-screen.png", platform_);      //makes textures equal appropritate pngs for background
	splash_icon = CreateTextureFromPNG("splash-icon.png", platform_);
	cross_button = CreateTextureFromPNG("playstation-cross-dark-icon.png", platform_);
	circle_button = CreateTextureFromPNG("playstation-circle-dark-icon.png", platform_);
	triangle_button = CreateTextureFromPNG("playstation-triangle-dark-icon.png", platform_);

	ChangeGameState(ActiveStates::Init);//sets gamestate to initialise

	game_audio_ = new audio_setup(platform_);
	//initialise audio
	game_audio_->audio_init_();

	//level models
	lvl_assets_ = new level_assets(platform_, *renderer_3d_, *state_input_, *world_, *game_audio_, *ball_);
	lvl_assets_->init_();

	
}

void state_management::StateHUD()
{
	if (state_font)
	{
		// display frame rate
		state_font->RenderText(sprite_renderer_, gef::Vector4(850.0f, 0.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
	}
}

void state_management::StateFont()
{

	//load in font
	state_font = new gef::Font(platform_);
	state_font->Load("comic_sans");
}



void state_management::StateUpdate(float frame_time)
{

	//update frames per second
	fps_ = 1.0f / frame_time;

	//setup rotation for splash screen icon
	rotation_ += speed_ * frame_time;

	//updates physics world
	int velocityIterations = 6;
	int positionIterations = 2;
	world_->Step(frame_time, velocityIterations, positionIterations);//updates b2workds


	//update gamestate input
	state_input_->Update();

	state_timer += frame_time;//makes state timer equal to frame time
	


	switch (active_states)//switch statement for calling each states update function
	{
	case ActiveStates::Init:
		InitStateUpdate();
		break;
	case ActiveStates::Menu:
		MenuStateUpdate();
		break;
	case ActiveStates::Level:
		LevelStateUpdate();
		break;
	case ActiveStates::Options:
		OptionsUpdate();
		break;
	case ActiveStates::HowTo:
		HTPupdate();
		break;
	case ActiveStates::Win:
		WinUpdate();
		break;
	case ActiveStates::Lose:
		LoseUpdate();
		break;
	default:
		break;

	}
}

void state_management::StateRender()//switch statement which will call appropriate render function when state is changed
{
	switch (active_states)
	{
	case ActiveStates::Init:
		InitStateRender();
		break;
	case ActiveStates::Menu:
		MenuStateRender();
		break;
	case ActiveStates::Level:
		LevelStateRender();
		break;
	case ActiveStates::Options:
		OptionsRender();
		break;
	case ActiveStates::HowTo:
		HTPrender();
		break;
	case ActiveStates::Win:
		WinRender();
		break;
	case ActiveStates::Lose:
		LoseRender();
		break;
	default:
	break;

	}
}



void state_management::ChangeGameState(ActiveStates new_state)
{
	//clean up old state
	switch (active_states) 
	{
	case ActiveStates::Init:
		break;
	case ActiveStates::Menu:
		MenuStateRelease();
		break;
	case ActiveStates::Options:
		OptionsRelease();
		break;
	case ActiveStates::HowTo:
		HTPrelease();
		break;
	case ActiveStates::Level:                      //switch statemnent which calls appropriate relase when state is changed 
		LevelStateRelease();
		break;
	case ActiveStates::Win:
		WinRelease();
		break;
	case ActiveStates::Lose:
		LoseRelease();
		break;
	case ActiveStates::None:
	default:
		break;
	}

	//set active_states to reference
	active_states = new_state;
	//set timer back to 0.0f
	state_timer = 0.0f;

	//init new state
	switch (active_states)
	{
	case ActiveStates::Init:
		break;
	case ActiveStates::Menu:
		MenuStateInit();
		break;
	case ActiveStates::Options:
		OptionsInit();
		break;
	case ActiveStates::HowTo:            //switch statement calls appropriate state inits when the state changes
		HTPinit();
		break;
	case ActiveStates::Level:
		LevelStateInit();
		break;
	case ActiveStates::Win:
		WinInit();
		break;
	case ActiveStates::Lose:
		LoseInit();
		break;
	case ActiveStates::None:
	default:
		break;
	}
}



void state_management::NormalDifficultySetup()
{
	ball_->SetLives(6);//sets lives to 6 if level is normal
	game_audio_->play_sound_(0);//plays button clicked sound
	ChangeGameState(ActiveStates::Level);//changes gamestate to the level
}

void state_management::HardDifficultySetup()
{	
	ball_->SetLives(3);//sets lives to 3 if level is hardmode

	game_audio_->play_sound_(0);//plays button clicked sound
	level_hard_ = true; //sets boolean level hard to tue 
	ChangeGameState(ActiveStates::Level);//changes gamestate to the level
	
}

void state_management::ChangeGravScale()
{
	if (level_hard_ == true)//checks if boolean is true
	{
		lvl_assets_->change_ball_gravity(0.04);// if level is hard ball grav scale is 0.04 falls slighlty quicker
	}
	else
	{
		lvl_assets_->change_ball_gravity(0.01);//if not hard ball grav scale is 0.01 slower 
	}
}



void state_management::CleanStates()
{

	//all conditional to not cause any nullptrs
	if (splash_screen)
	{
		delete splash_screen;
		splash_screen = NULL;
	}

	if (splash_icon)
	{
		delete splash_icon;
		splash_icon = NULL;
	}

	if (game_audio_)
	{
		delete game_audio_;
		game_audio_ = NULL;

	}

	if (world_)
	{
		delete world_;
		world_ = NULL;
	}

	if (renderer_3d_)
	{
		delete renderer_3d_;
		renderer_3d_ = NULL;
	}

	if (sprite_renderer_)
	{
		delete sprite_renderer_;
		sprite_renderer_ = NULL;
	}

	if (state_input_)
	{
		delete state_input_;
		state_input_ = NULL;
	}
}

void state_management::InitStateUpdate()
{
	

	if (state_timer > 6.0f)
	{
		ChangeGameState(ActiveStates::Menu); //after state timer reaches 6 seconds state changes to menu
	}

	game_audio_->play_sound_(2);//plays splash screen sound
}

void state_management::InitStateRender()//init state 
{

	sprite_renderer_->Begin();
	RenderBackground(splash_screen); //renders splash screen background
	RenderSplashIcon(); //renders rotating splash screen icon

	StateHUD(); 
	sprite_renderer_->End();

	
}

void state_management::MenuStateInit()
{
	menu_screen_ = CreateTextureFromPNG("Menu-Screen-Filled.png", platform_); //initialises menu screen background

}

void state_management::MenuStateUpdate()
{

	

	const gef::SonyController* controller = state_input_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_CROSS)//if cross pressed
	{
		game_audio_->play_sound_(0);
		ChangeGameState(ActiveStates::Options);//press cross to play, takes us to options first so set music, difficulty etc.
		//plays main music
		game_audio_->play_music_();
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_TRIANGLE) //if triangle pressed
	{
		game_audio_->play_sound_(0);
		ChangeGameState(ActiveStates::HowTo);//press triangle goes to how to play screen the user learns how to play 
	}
	if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE) //if circle is pressed
	{
		game_audio_->play_sound_(0); //plays button click sound
		//exit program 
		exit(0);
	}

}

void state_management::MenuStateRender()
{

	sprite_renderer_->Begin();

	RenderBackground(menu_screen_);//renders menu bg
	RenderButton(circle_button, 72.0f, 24.0f, -2.0f, 20.0f, 20.0f);//renders a button sprite, can change the buttons texture, position and size with this function.
	RenderButton(cross_button, 780.0f, 329.0f, -2.0f, 25.0f, 25.0f);//renders cross button near play text
	RenderButton(triangle_button, 845.0f, 468.0f, -2.0f, 20.0f, 20.0f);//renders triangle button near how to play text

	StateHUD();
	sprite_renderer_->End();
}

void state_management::MenuStateRelease()
{


	delete menu_screen_;
	menu_screen_ = NULL;

}

void state_management::OptionsInit()
{
	options_screen_ = CreateTextureFromPNG("Options-Screen.png", platform_);//loads in texture for options screen
}

void state_management::OptionsUpdate()
{
	const gef::SonyController* controller = state_input_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE)//pressing circle goes back to menu
	{
		game_audio_->play_sound_(0);//plays button clicked sound
		ChangeGameState(ActiveStates::Menu);//chagnes gamestate to menu
	}
	if (controller && controller->buttons_released() & gef_SONY_CTRL_DOWN) //if dpad down is pressed
	{
		//stops music
		game_audio_->play_sound_(0);//plays button clicked sound
		game_audio_->end_music_();


	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_CROSS)
	{
		NormalDifficultySetup();//sets up lives for normal mode and gravity scale
		
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_TRIANGLE)
	{
		HardDifficultySetup();//sets up lives for hard mode and gravity scale
		
	}



}

void state_management::OptionsRender()
{
	sprite_renderer_->Begin();

	RenderBackground(options_screen_);//renders options bg

	RenderButton(circle_button, 90.0f, 522.0f, -2.0f, 20.0f, 20.0f);//renders a button sprite, can change the buttons texture, position and size with this function.
	RenderButton(triangle_button, 600.0f, 330.0f, -2.0f, 30.0f, 30.0f);//renders triangle button underneath hard difficulty
	RenderButton(cross_button, 480.0f, 330.0f, -2.0f, 30.0f, 30.0f);//renders a cross button underneath normal difficulty;
	RenderBack(); 

	StateHUD();
	sprite_renderer_->End();
}

void state_management::OptionsRelease()
{
	delete options_screen_;//deletes options screen sprite
	options_screen_ = NULL;
}

void state_management::HTPinit()
{

	htp_screen_ = CreateTextureFromPNG("How-To-Screen.png", platform_);//create texture for how to play screen
}

void state_management::HTPupdate()
{
	const gef::SonyController* controller = state_input_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE)//pressing circle goes back to menu
	{
		game_audio_->play_sound_(0);//plays button clicked soubds
		ChangeGameState(ActiveStates::Menu);//changes state to menu
	}
}

void state_management::HTPrender()
{
	sprite_renderer_->Begin();

	RenderBackground(htp_screen_);//renders how to play bg

	RenderButton(circle_button, 90.0f, 522.0f, -2.0f, 20.0f, 20.0f);//renders a button sprite, can change the buttons texture, position and size with this function.
	RenderBack(); //renders text to return to menu

	StateHUD();
	sprite_renderer_->End();
}

void state_management::HTPrelease()
{
	delete htp_screen_;
	htp_screen_ = NULL;
}

void state_management::LevelStateInit()
{
	//loads texture for level background
	level_screen_ = CreateTextureFromPNG("Level-Background.png", platform_);

	//makes terrain
	lvl_assets_->create_ground_();//creates ground 
	lvl_assets_->create_walls(); //creates walls

	lvl_assets_->load_model();//loads player model
	lvl_assets_->load_balls();//loads ball model


}

void state_management::LevelStateUpdate()
{

	lvl_assets_->Update();//update level models
	lvl_assets_->update_ground();//updates ground
		
	ChangeGravScale();//changes grav scale of the ball

	if (ball_->GetScore() >= 20)//if score is greater than or equal to 20 do the following :
	{
		game_audio_->play_sound_(6); //plays win sound
		ChangeGameState(ActiveStates::Win);//change state to win gamestate
	}

	if (ball_->GetLives() <= 0) //if lives is less than or equal to 0 do the following:
	{
		game_audio_->play_sound_(5);//plays lose sound
		ChangeGameState(ActiveStates::Lose);//if player has 0 lives change gamestate to lose

	}

}

void state_management::LevelStateRender()
{



	state_lights();//sets up lights in level
	state_camera();//sets up camera in level

	sprite_renderer_->Begin();//begin sprite render

	RenderBackground(level_screen_);//renders level bg sprite

	RenderGameInfo("Confidence: %i", 10.0f, 5.0f, -6.0f, ball_->GetLives());
	RenderGameInfo("Balls Caught: %i", 180.f, 5.0f, -6.0f, ball_->GetScore());

	StateHUD();
	sprite_renderer_->End();//end sprite render

	renderer_3d_->Begin(false); //begin 3d renderer

	lvl_assets_->render_ground_(); //renders green platform and walls 
	lvl_assets_->render_model();//renders player
	
	
	lvl_assets_->render_balls();//render ball

	renderer_3d_->End();//end 3d renderer

	

}

void state_management::LevelStateRelease()
{
	//cleans level state
	if (level_screen_)
	{
		delete level_screen_;
		level_screen_ = NULL;
	}

	game_audio_->audio_cleanup(); //cleans audio

	lvl_assets_->clean_models(); //checks if scene assets needs to be deleted
	lvl_assets_->cleanup_ground(); //checks if terrain needs to be deleted

	if (lvl_assets_)//delete lvl assets if nessecary 
	{
		delete lvl_assets_;
		lvl_assets_ = NULL;
	}

}

void state_management::WinInit()
{
	win_screen_ = CreateTextureFromPNG("win-screen.png", platform_);//creates win screen texture
}

void state_management::WinUpdate()
{
	const gef::SonyController* controller = state_input_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE)//pressing circle goes back to menu
	{
		game_audio_->play_sound_(0);//plays button clicked sound
		ChangeGameState(ActiveStates::Menu);//chagnes gamestate to menu
	}
}

void state_management::WinRender()
{
	sprite_renderer_->Begin();

	RenderBackground(win_screen_);//render win bg sprite
	RenderButton(circle_button, 90.0f, 522.0f, -2.0f, 20.0f, 20.0f);//renders a button sprite, can change the buttons texture, position and size with this function.
	RenderBack(); //renders text to return to menu

	StateHUD();
	sprite_renderer_->End();//end sprite render
}

void state_management::WinRelease()
{
	if (win_screen_)
	{
		delete win_screen_;  //only deletes if win_Screen isnt null ptr
		win_screen_ = NULL;
	}
}

void state_management::LoseInit()
{

	lose_screen_ = CreateTextureFromPNG("lose-screen.png", platform_);//creates win screen texture
}

void state_management::LoseUpdate()
{
	const gef::SonyController* controller = state_input_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE)//pressing circle goes back to menu
	{
		game_audio_->play_sound_(0);//plays button clicked sound
		ChangeGameState(ActiveStates::Menu);//chagnes gamestate to menu
	}
}

void state_management::LoseRender()
{
	sprite_renderer_->Begin();//begins sprite renderer

	RenderBackground(lose_screen_);//render win bg sprite
	RenderButton(circle_button, 90.0f, 522.0f, -2.0f, 20.0f, 20.0f);//renders a button sprite, can change the buttons texture, position and size with this function.
	RenderBack(); //renders text to return to menu


	StateHUD();
	sprite_renderer_->End();
}

void state_management::LoseRelease()
{
	if (lose_screen_)
	{
		delete lose_screen_;
		lose_screen_ = NULL;
	}
}


void state_management::RenderBack()
{
	//renders text for going back to menu
	state_font->RenderText(sprite_renderer_, gef::Vector4(75.0f, 510.0f, -2.0f), 0.70f, 0xffffffff, gef::TJ_RIGHT, "Menu");
}

void state_management::RenderButton(gef::Texture* tex, float x, float y, float z, float w, float h)//button function takes a texture as well as 5 floats for size and position 
{
	//Render button icon
	gef::Sprite button; //creates sprite called button
	button.set_texture(tex); //sets texture to tex parameter
	button.set_position(gef::Vector4(x,y,z)); //sets position to x,y,z parameters
	button.set_height(h);//sets hegiht to h parameter 
	button.set_width(w);//sets width to w parameter
	sprite_renderer_->DrawSprite(button);//draws sprite
}

void state_management::RenderBackground(gef::Texture* tex) //render background takes just a texture as every background will have the same size and position. 
{
	//renders background which is size of window 
	gef::Sprite state_bg_;//creates sprite 
	state_bg_.set_texture(tex);//takes in a texture parameter...
	state_bg_.set_position(gef::Vector4(platform_.width() * 0.5f, platform_.height() * 0.5f, 10.0));//sets position of sprite
	state_bg_.set_height(platform_.height());//sprites height and width equal the platforms width and height
	state_bg_.set_width(platform_.width());
	sprite_renderer_->DrawSprite(state_bg_);//renders sprite
}

void state_management::RenderGameInfo(char* text, float x, float y, float z, int info)//game info takes text, 3 floats and an integer so the position and the information being displayed can be decided 
{
	// render game information text e.g lives, scores etc
	state_font->RenderText(sprite_renderer_, gef::Vector4(x, y, z), 1.0f, 0xffffffff, gef::TJ_LEFT, text, info);
}

void state_management::RenderSplashIcon()
{
	gef::Sprite icon_;//creates sprite called icon
	icon_.set_texture(splash_icon);//takes in a texture parameter...
	icon_.set_position(480.0f,270.0f,10.0f);//sets position of sprite
	icon_.set_height(72.0f);//sets height 
	icon_.set_width(72.0f);//sets width
	icon_.set_rotation(rotation_);//sets rotatiom of sprite
	sprite_renderer_->DrawSprite(icon_);//draws sprite
}

void state_management::state_lights()
{

	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.6f, 0.6f, 0.6f, 1.0f));

	
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.9f, 0.9f, 0.0f, 1.0f));//sets the light to a yellow-ish colour
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void state_management::state_camera()
{

	// setup camera

	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(0.0f, 0.0f, 5.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);

}
