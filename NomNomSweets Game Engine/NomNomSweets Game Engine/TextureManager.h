#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include "Singleton.h"

//Pre define the texture path to all texture files
#define TEX_PATH "Resources\\Textures\\" 

using std::map;
using std::string; 
using std::cout;

/*
A class that is responsible for managing the texture resources for the game
*/
class TextureManager : public Singleton<TextureManager>{
public:
	friend class Singleton<TextureManager>;

	//Checks if the given texture already exists or not
	bool existTexture(const string &file_name);

	//Retrieves a texture from the map based on the provided file name as the key
	sf::Texture* retrieveTexture(const string &file_name);

	//Loads the texture into the map
	bool loadTexture(const string &file_name);


protected:
	//Constructor
	TextureManager();

	//Destructor
	~TextureManager();

	//Map of file name as string keys and textures as the mapped values
	map<string, sf::Texture*> all_textures;

};