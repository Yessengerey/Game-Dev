#pragma once
#include "Singleton.h"
#include "TextureManager.h"
#include "SFXManager.h"

/*This class is responsible to provide means for an easy access
to all other resource managers. This class acts as a global access
point to all managers.*/
class AllResManager : public Singleton<AllResManager>{
public:
	friend class Singleton<AllResManager>;

	//Textures Functions
	inline bool existTexture(const string &file_name){
		return TextureManager::Instance().existTexture(file_name);
	};

	inline sf::Texture* retrieveTexture(const string &file_name){
		return TextureManager::Instance().retrieveTexture(file_name);
	};

	inline bool loadTexture(const string &file_name){
		return TextureManager::Instance().loadTexture(file_name);
	};

	//Sound effects functions
	inline Music* loadMusic(const string& file_name){
		return SFXManager::Instance().loadMusic(file_name);
	};

	inline Music* retrieveMusic(const string& file_name){
		return SFXManager::Instance().retrieveMusic(file_name);
	};

	inline Sound* loadSFX(const string& file_name){
		return SFXManager::Instance().loadSFX(file_name);
	};

	inline Sound* retrieveSFX(const string& file_name){
		return SFXManager::Instance().retrieveSFX(file_name);
	};

	void playMusic(const string& file_name){
		return SFXManager::Instance().playMusic(file_name);
	};

	void stopMusic(const string& file_name){
		return SFXManager::Instance().stopMusic(file_name);
	};

	void loopMusic(const string& file_name){
		return SFXManager::Instance().loopMusic(file_name);
	};

	void playSFX(const string& file_name){
		return SFXManager::Instance().playSFX(file_name);
	};

	//Other managers 
	AllResManager(){
		TextureManager::Create();
		SFXManager::Create();
	};

	~AllResManager(){
		TextureManager::Delete();
		SFXManager::Delete();
	};
};
