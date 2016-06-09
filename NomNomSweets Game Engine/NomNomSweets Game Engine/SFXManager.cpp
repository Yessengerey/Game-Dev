#include "SFXManager.h"

SFXManager::SFXManager(){

}

/*
Audio Manager destructor
*/
SFXManager::~SFXManager(){
	for (map<string, Music*>::iterator it = all_music.begin(); it != all_music.end(); it++){
		it->second->stop();
		delete it->second;
		//all_music.erase(it);
	}
	for (map<string, Sound*>::iterator it = all_sfx.begin(); it != all_sfx.end(); it++){
		it->second->stop();
		delete it->second;
		//all_sfx.erase(it);
	}
	for (deque<SoundBuffer*>::iterator it = buff.begin(); it != buff.end(); it++){
		delete *it;
	}
}

/*Function to retrieve the music file from the map
@param file_name : name of the file including the format (.png)*/
Music* SFXManager::retrieveMusic(const string& file_name){
	map<string, Music*>::iterator it = all_music.find(file_name);

	//if the specified audio file exists, then return it
	if (it != all_music.end()){
		return it->second;
	}

	return NULL;
}

/*Function that accesses an audio file via the provided name and loads it into the map*/
Music* SFXManager::loadMusic(const string& file_name){
	Music* m = SFXManager::retrieveMusic(file_name);

	if (m != NULL){
		return m;
	}

	m = new Music();
	m->openFromFile(SFX_PATH + file_name);
	all_music.insert(pair<string, Music*>(file_name, m));

	return m;
}

/*Function to play the music file*/
void SFXManager::playMusic(const string& file_name){
	Music* music = retrieveMusic(file_name);

	if (music != NULL){
		music->play();
	}
}

/*Function to stop the specified music file*/
void SFXManager::stopMusic(const string& file_name){
	Music* music = retrieveMusic(file_name);

	if (music != NULL){
		if (music->getStatus() != Music::Stopped){
			music->stop();
		}
	}
}

/*Function that sets a music file on a loop so it keeps on playing after it finishes*/
void SFXManager::loopMusic(const string& file_name){
	Music* music = retrieveMusic(file_name);

	if (music != NULL){
		music->setLoop(true);
	}
}

/*Function that retrieves the speicifed sound effect from the map*/
Sound* SFXManager::retrieveSFX(const string& file_name){
	map<string, Sound*>::iterator it = all_sfx.find(file_name);

	//if the specified audio file exists, then return it
	if (it != all_sfx.end()){
		return it->second;
	}

	return NULL;
}

/*Function to load the sound effect file into the map*/
Sound* SFXManager::loadSFX(const string& file_name){
	Sound* s = SFXManager::retrieveSFX(file_name);

	if (s != NULL){
		return s;
	}
	
	s = new Sound();
	SoundBuffer* buffer = new SoundBuffer();

	if (!buffer->loadFromFile((SFX_PATH + file_name).c_str())){
		delete s;
		delete buffer;
		return NULL;
	}

	buff.push_back(buffer);
	s->setBuffer(*buffer);

	all_sfx.insert(pair<string, Sound*>(file_name, s));

	return s;
}

/*Function to play the sound effect*/
void SFXManager::playSFX(const string& file_name){
	Sound* sfx = retrieveSFX(file_name);

	if (sfx != NULL){
		sfx->play();
	}
}



