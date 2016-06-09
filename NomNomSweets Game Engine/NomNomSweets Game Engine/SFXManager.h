#pragma once
#include <SFML\Audio.hpp>
#include <map>
#include <string>
#include <deque>
#include <iostream>
#include "Singleton.h"

//Pre-define the path way for the sound effects 
#define SFX_PATH "Resources\\SFX\\"
using std::map;
using std::string; 
using std::cout;
using std::endl;
using std::pair;
using std::deque;
using sf::Music;
using sf::Sound;
using sf::SoundBuffer;

//Class is responsible for managing the audio files for the game
class SFXManager : public Singleton <SFXManager>{
public:

	friend class Singleton<SFXManager>;

	//Loads music into the map
	Music* loadMusic(const string& file_name);

	//Retrieves the specified music file from the map
	Music* retrieveMusic(const string& file_name);

	//Plays the specified music file
	void playMusic(const string& file_name);

	//Stops the specified music file
	void stopMusic(const string& file_name);

	//Puts the music file on the loop for it to repeat 
	void loopMusic(const string& file_name);

	//Loads the sound effects file into the map
	Sound* loadSFX(const string& file_name);

	//Retrieves the specified sound effect from the map
	Sound* retrieveSFX(const string& file_name);

	//Plays the specified sound effect
	void playSFX(const string& file_name);


protected:

	SFXManager();
	~SFXManager();
	map<string, Music*> all_music;
	map<string, Sound*> all_sfx;
	deque<SoundBuffer*> buff;
};
