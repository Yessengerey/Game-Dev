#pragma once
#include "AllResManager.h"
#include "GameEntity.h"
#include "ReadFile.h"

/*This class plays a role of a container of all necessary 
resources such as textures, sprites and some entities. The
resources are preloaded and then retrieved when needed.
This class also provides game logic and states.*/
class Game{
public:

	//Game constructor
	Game(int max_score, int max_hp, b2World* World, sf::RenderWindow* rw);

	//Game destructor
	~Game();

	//Loads game objects onto the vector (veggies and sweets)
	void loadObjResources(sf::RenderWindow* rw);

	//Loads the boundaries of the world into the game
	void loadBounds(sf::RenderWindow* rw);

	//Loads preloads all necessary texture files and music files and plays the main
	//theme music in a loop
	void loadMusicTex();

	//Updates all of the sprites of all objects
	void update();

	//Destroys all objects
	void destroyAllResources();

	//Adds all objects to the Box2d world
	void addObjectsToWorld();

	//Can be called from main file to create an object.
	//this function uses text file settings depending on what sort of object
	//is to be created
	void createElement(E_TYPE t, b2World* w, sf::RenderWindow* d, float posx, float posy);

	//Creates the world set up for level One
	//void createLevelOne(b2World* w, sf::RenderWindow* d);

	void GamePlay();
	void EndGame();

	std::vector<GameEntity*> all_entities;

	float drop_size = 32.0f;

	//Updates collisions of all objects
	bool updateCollisions();

	void createLevelOne(b2World* w, sf::RenderWindow* d);

	void LevelOne(b2World* w, sf::RenderWindow* d);
	void LevelTwo(b2World* w, sf::RenderWindow* d);
	void LevelThree(b2World* w, sf::RenderWindow* d);
	ReadFile readF;

	std::vector<GameEntity*> forRemoval;

	int n_collisions = 0;
	int hp = 0;
private:

	PXWorldObject* pxw;
	b2World* World = new b2World(b2Vec2(0.0f, 9.8f));
	sf::RenderWindow* wind;

	int max_score = 99;
	int max_hp = 5;
	int number_of_elements;


	bool game_on;
	bool victory;

};