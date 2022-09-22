#include "audio_setup.h"
#include <system/platform.h>
audio_setup::audio_setup(gef::Platform& platform) :
	audio_manager_(NULL),
	platform_(platform)
{	
}

void audio_setup::audio_cleanup()
{

	audio_manager_->UnloadMusic(); //unloads music...
}

void audio_setup::audio_init_()
{
	audio_manager_ = gef::AudioManager::Create();

	//music
	audio_manager_->LoadMusic("main-music.wav", platform_);//music sample 0

	//sounds
	audio_manager_->LoadSample("button-click.wav", platform_);//sound sample 0
	audio_manager_->LoadSample("player-steps.wav", platform_);//sound sample 1
	audio_manager_->LoadSample("intro-sound.wav", platform_);//sound sample 2
	audio_manager_->LoadSample("ground-collision.wav", platform_);//sound sample 3
	audio_manager_->LoadSample("player-collision.wav", platform_);//sound sample 4
	audio_manager_->LoadSample("lose-sound.wav", platform_);//sound sample 5
	audio_manager_->LoadSample("win-sound.wav", platform_);//sound sample 6

}


void audio_setup::play_sound_(Int32 sample_)
{
	audio_manager_->PlaySample(sample_, false); //plays sample not looping as sound will play after a button click or collision it doesnt need looped
}

void audio_setup::play_music_()
{
	audio_manager_->SetMasterVolume(75.0f);//sets volume
	audio_manager_->PlayMusic();//plays music

}

void audio_setup::end_music_()
{
	audio_manager_->StopMusic();//stops music
}
