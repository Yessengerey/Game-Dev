#include "TextureManager.h"

TextureManager::TextureManager(){

}

//Texture manager destructors that erases all textures
TextureManager::~TextureManager(){
	for (map<string, sf::Texture*>::iterator it = all_textures.begin(); it != all_textures.end(); it++){
		//all_textures.erase(it);
		delete it->second;
	}
}

/*
Retrieve the texture of a given file name
*/
sf::Texture* TextureManager::retrieveTexture(const string &file_name){
	sf::Texture* empty_texture = new sf::Texture;

	if (existTexture(file_name) == false){
		cout << "THE FILE DOESN'T EXIST!" << std::endl;
		return empty_texture;
	}

	map<string, sf::Texture*>::iterator it = all_textures.find(file_name);

	if (it != all_textures.end()){
		return it->second;
	}
}

/*
Checks if the given texture file exists
@param file_name : name of the file, type string
*/
bool TextureManager::existTexture(const string &file_name){

	map<string, sf::Texture*>::iterator it = all_textures.find(file_name);

	if (it != all_textures.end()){
		return true;
	}

	return false;
}

bool TextureManager::loadTexture(const string &file_name){
	if (existTexture(file_name) == true){
		return false;
	}

	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile(TEX_PATH + file_name);

	all_textures.insert(std::pair<string, sf::Texture*>(file_name, tex));

	return true;
}