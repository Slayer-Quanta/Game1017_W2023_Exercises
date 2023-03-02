#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__
#include <iostream>
#include <string>
#include <map> 
#include <SDL_mixer.h>

enum SoundType
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public: // Public methods.
	static void Init();
	static void AllocateChannels(const int);
	static bool Load(const std::string&, const std::string&, SoundType);
	static void Unload(const std::string&, SoundType);
	static void PlayMusic(const std::string&, int = -1, int = 0);
	static void StopMusic(int = 0);
	static void PauseMusic();
	static void ResumeMusic();
	static void PlaySound(const std::string&, int = 0, int = -1);
	static void StopSound(int = -1);
	static void SetMusicVolume(const int);
	static void SetSoundVolume(const int, int = -1);
	static void SetAllVolume(const int);
	
	// Panning converts a single slider value from 0 to 100 to the stereo speaker volumes.
	static void PanLeft(const unsigned = 5U, const int = MIX_CHANNEL_POST);
	static void PanRight(const unsigned = 5U, const int = MIX_CHANNEL_POST);
	static void PanReset(const int = MIX_CHANNEL_POST);
	static void PanSet(const int, const int = MIX_CHANNEL_POST);
	static void Quit();
	
private: // Private members.
	static std::map<std::string, Mix_Chunk*> s_sfxs;
	static std::map<std::string, Mix_Music*> s_music;
	static int s_pan; // A slider value from 0 to 100. 0 = full left, 100 = full right.
	SoundManager() = default;
};

typedef SoundManager SOMA;

#endif 