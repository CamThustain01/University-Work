#pragma once
#include <audio/audio_manager.h>
#include <system/application.h>
namespace gef
{
	class Platform;
	class AudioManager;
}

class audio_setup
{
public:

	//audio functions
	audio_setup(gef::Platform& platform); //constructor takes reference of platform
	void audio_cleanup(); //cleans up audio 
	void audio_init_(); //initialise audio, sets up samples etc
	void play_sound_(Int32 sample_); //play sound takes an int32 called sample which will play the specific sample i.e play_sound_(0) plays sound sample 0 
	void play_music_(); //plays music
	void end_music_(); //ends music

	//platform
	gef::Platform& platform_;

	//instance of audio manager
	gef::AudioManager* audio_manager_;
};

