#pragma once
#include <regex>
#include <string>
#include <fstream>
#include "GameEntity.h"

/*This class is responsible for File I/O management.
It is capable of determining if the specified
settings file exists, what information is enclosed,
and what should be done with the enclosed information.*/

//using regular expressions
using std::regex;
using std::regex_match;
using std::smatch;
using std::ifstream;
using std::string;
using std::stoi;

//Struct for sweets/veggie objects falling from the sky
struct drop{
	int lifetime;
	int score;
	char type;
};

//Struct for character objects moving around the environment
struct character{
	float width;
	float height;
	float density;
	std::string tex_name;
};

struct world{
	float gravx;
	float gravy;
	float step;
	int vi;
	int pi;
};

struct platform{
	float width;
	float height;
	float posx;
	float posy;
	float density;
	std::string tex_name;
};

struct LevelOne{
	GameEntity* charA;
	GameEntity* platform1;
	GameEntity* platform2;
	GameEntity* sweet1;
	GameEntity* sweet2;
	GameEntity* sweet3;
};
class ReadFile{
public:
	ReadFile(){} //Default constructor
	~ReadFile(){} //Default destructor

	void readLevelOne(char* lvlonetext, b2World* w, sf::RenderWindow* r){
		regex lvl1("Resources/Settings/levelone.txt");

		if (regex_match(lvlonetext, lvl1)){
			regex charac("character-");
			regex pt1("platform1-");
			regex pt2("platform2-");
			regex sw1("sweet1-");
			regex sw2("sweet2-");
			regex sw3("sweet3-");

			string fromtxt;

			ifstream file(lvlonetext);

			if (file.is_open()){
				int flag = 0;

				while (getline(file, fromtxt)){
					switch (flag){
					case 1:
						lvlone.charA = GetCharacterA("Resources/Settings/character.txt", w, CHARACTER, r, 170.0f, 300.0f);
						level_one_entities.push_back(lvlone.charA);
						flag = 0;
						break;

					case 2:
						lvlone.platform1 = GetPlatformA("Resources/Settings/platform1.txt", w, r, 900.0f, 300.0f);
						level_one_entities.push_back(lvlone.platform1);
						flag = 0;
						break;
					case 3:
						lvlone.platform2 = GetPlatformA("Resources/Settings/platform2.txt", w, r, 900.0f, 500.0f);
						level_one_entities.push_back(lvlone.platform2);
						flag = 0;
						break;
						
					}
					if (regex_match(fromtxt, charac)){
						flag = 1;
						continue;
					}
					if (regex_match(fromtxt, pt1)){
						flag = 2;
						continue;
					}

					if (regex_match(fromtxt, pt2)){ 
						flag = 3;
						continue;
					}
				}
			}
		}
	}

	//Reads in the specified settings text file associated with the dropped objects
	void GetDrop(char* droptxt){
		//We know exactly where the file is located and what it is called
		regex drop("Resources/Settings/drop.txt");

		//Check that the provided filename matches the regular expression
		if (regex_match(droptxt, drop)){ //IF yes then proceed  

			//regular expression identifying different parts of the document
			regex lifetime(">lifetime_");
			regex score(">score_");
			regex type(">type_");

			//line of text from the file
			string linefromtxt;

			//incoming stream of information from the specified file
			ifstream file(droptxt);

			if (file.is_open()){ //open the file, checking it doesn't fail


				int flag = 0; //1 = lifetime, 2 = score, 3 = type

				while (getline(file, linefromtxt)){ //get line from .txt

					switch (flag){

					case 1:
						d.lifetime = stoi(linefromtxt);
						flag = 0;
						break;

					case 2:
						d.score = stoi(linefromtxt);
						flag = 0;
						break;

					case 3:
						d.type = *(const_cast<char*>(linefromtxt.c_str()));
						flag = 0;
						break;
					}


					if (regex_match(linefromtxt, lifetime)){ //If flag != 0  then Next line is what we want
						flag = 1;
						continue;
					}
					if (regex_match(linefromtxt, score)){
						flag = 2;
						continue;
					}
					if (regex_match(linefromtxt, type)){
						flag = 3;
						continue;
					}

				}
			}
		}
	}


	//Read in the text file associated with the character
	void GetCharacter(char* chartxt){

		regex drop("Resources/Settings/character.txt");

		if (regex_match(chartxt, drop)){ //IF the specified file matches the regular expression then proceed 

			regex width("width-");
			regex height("height-");
			regex dens("density-");
			regex tex("tex-");


			string linefromtxt;

			ifstream file(chartxt);

			if (file.is_open()){ //open the file, checking it doesn't fail


				int flag = 0; //1 = posx, 2 = posy

				while (getline(file, linefromtxt)){ //get line from .txt

					switch (flag){
					case 1:
						c.width = stof(linefromtxt);
						flag = 0;
						break;

					case 2:
						c.height = stof(linefromtxt);
						flag = 0;
						break;
					case 3:
						c.density = stof(linefromtxt);
						flag = 0;
						break;

					case 4:
						c.tex_name = linefromtxt;
						flag = 0;
						break;

					}


					if (regex_match(linefromtxt, width)){ //If flag != 0  then Next line is what we want
						flag = 1;
						continue;
					}
					if (regex_match(linefromtxt, height)){
						flag = 2;
						continue;
					}
					if (regex_match(linefromtxt, dens)){ //If flag != 0  then Next line is what we want
						flag = 3;
						continue;
					}
					if (regex_match(linefromtxt, tex)){
						flag = 4;
						continue;
					}
				}
			}
		}
	}

	GameEntity* GetCharacterA(char* chartxt, b2World* w, E_TYPE e, sf::RenderWindow* r, float posx, float posy){

		regex drop("Resources/Settings/character.txt");

		if (regex_match(chartxt, drop)){ //IF the specified file matches the regular expression then proceed 

			regex width("width-");
			regex height("height-");
			regex dens("density-");
			regex tex("tex-");


			string linefromtxt;

			ifstream file(chartxt);

			if (file.is_open()){ //open the file, checking it doesn't fail


				int flag = 0; //1 = posx, 2 = posy

				while (getline(file, linefromtxt)){ //get line from .txt

					switch (flag){
					case 1:
						c.width = stof(linefromtxt);
						flag = 0;
						break;

					case 2:
						c.height = stof(linefromtxt);
						flag = 0;
						break;
					case 3:
						c.density = stof(linefromtxt);
						flag = 0;
						break;

					case 4:
						c.tex_name = linefromtxt;
						flag = 0;
						break;

					}


					if (regex_match(linefromtxt, width)){ //If flag != 0  then Next line is what we want
						flag = 1;
						continue;
					}
					if (regex_match(linefromtxt, height)){
						flag = 2;
						continue;
					}
					if (regex_match(linefromtxt, dens)){ //If flag != 0  then Next line is what we want
						flag = 3;
						continue;
					}
					if (regex_match(linefromtxt, tex)){
						flag = 4;
						continue;
					}
				}
			}
		}
		this->character = new GameEntity(world, e, c.width, c.height, posx, posy, c.density, *(AllResManager::Instance().retrieveTexture(c.tex_name)), r);
		return this->character;
	}

	void GetWorld(char* worldtxt){

		regex world("Resources/Settings/box2d_world.txt");

		if (regex_match(worldtxt, world)){ //IF the specified file matches the regular expression then proceed 

			regex gravx(">gravityX_");
			regex gravy(">gravityY_");
			regex step(">time_step_");
			regex vi(">velocity_iterations_");
			regex pi(">position_iterations_");


			string linefromtxt;

			ifstream file(worldtxt);

			if (file.is_open()){ //open the file, checking it doesn't fail


				int flag = 0;

				while (getline(file, linefromtxt)){ //get line from .txt

					switch (flag){

					case 1:
						w.gravx = stof(linefromtxt);
						flag = 0;
						break;

					case 2:
						w.gravy = stof(linefromtxt);
						flag = 0;
						break;

					case 3:
						w.step = stof(linefromtxt);
						flag = 0;
						break;

					case 4:
						w.vi = stoi(linefromtxt);
						flag = 0;
						break;

					case 5:
						w.pi = stoi(linefromtxt);
						flag = 0;
						break;
					}


					if (regex_match(linefromtxt, gravx)){ //If flag != 0  then Next line is what we want
						flag = 1;
						continue;
					}
					if (regex_match(linefromtxt, gravy)){
						flag = 2;
						continue;
					}
					if (regex_match(linefromtxt, step)){
						flag = 3;
						continue;
					}
					if (regex_match(linefromtxt, vi)){
						flag = 4;
						continue;
					}
					if (regex_match(linefromtxt, pi)){
						flag = 5;
						continue;
					}
				}
			}
		}
	}

	void GetPlatform(char* chartxt){

		regex drop("Resources/Settings/platform.txt");

		if (regex_match(chartxt, drop)){ //IF the specified file matches the regular expression then proceed 

			regex width("width-");
			regex height("height-");
			regex posx("posx-");
			regex posy("posy-");
			regex dens("density-");
			regex tex("tex-");


			string linefromtxt;

			ifstream file(chartxt);

			if (file.is_open()){ //open the file, checking it doesn't fail


				int flag = 0; //1 = posx, 2 = posy

				while (getline(file, linefromtxt)){ //get line from .txt

					switch (flag){
					case 1:
						p.width = stof(linefromtxt);
						flag = 0;
						break;

					case 2:
						p.height = stof(linefromtxt);
						flag = 0;
						break;
					case 3:
						p.posx = stof(linefromtxt);
						flag = 0;
						break;

					case 4:
						p.posy = stof(linefromtxt);
						flag = 0;
						break;

					case 5:
						p.density = stof(linefromtxt);
						flag = 0;
						break;

					case 6:
						p.tex_name = linefromtxt;
						flag = 0;
						break;

					}


					if (regex_match(linefromtxt, width)){ //If flag != 0  then Next line is what we want
						flag = 1;
						continue;
					}
					if (regex_match(linefromtxt, height)){
						flag = 2;
						continue;
					}
					if (regex_match(linefromtxt, posx)){ //If flag != 0  then Next line is what we want
						flag = 3;
						continue;
					}
					if (regex_match(linefromtxt, posy)){
						flag = 4;
						continue;
					}

					if (regex_match(linefromtxt, dens)){ //If flag != 0  then Next line is what we want
						flag = 5;
						continue;
					}
					if (regex_match(linefromtxt, tex)){
						flag = 6;
						continue;
					}
				}
			}
		}
	}

	GameEntity* GetPlatformA(char* chartxt, b2World* w, sf::RenderWindow* r, float posx, float posy){

		regex drop(chartxt);

		if (regex_match(chartxt, drop)){ //IF the specified file matches the regular expression then proceed 

			regex width("width-");
			regex height("height-");
			regex dens("density-");
			regex tex("tex-");


			string linefromtxt;

			ifstream file(chartxt);

			if (file.is_open()){ //open the file, checking it doesn't fail


				int flag = 0; //1 = posx, 2 = posy

				while (getline(file, linefromtxt)){ //get line from .txt

					switch (flag){
					case 1:
						p.width = stof(linefromtxt);
						flag = 0;
						break;

					case 2:
						p.height = stof(linefromtxt);
						flag = 0;
						break;

					case 5:
						p.density = stof(linefromtxt);
						flag = 0;
						break;

					case 6:
						p.tex_name = linefromtxt;
						flag = 0;
						break;

					}


					if (regex_match(linefromtxt, width)){ //If flag != 0  then Next line is what we want
						flag = 1;
						continue;
					}
					if (regex_match(linefromtxt, height)){
						flag = 2;
						continue;
					}

					if (regex_match(linefromtxt, dens)){ //If flag != 0  then Next line is what we want
						flag = 5;
						continue;
					}
					if (regex_match(linefromtxt, tex)){
						flag = 6;
						continue;
					}
				}
			}
		}
		this->platform = new GameEntity(world, PLATFORM, p.width, p.height, posx, posy, c.density, *(AllResManager::Instance().retrieveTexture(p.tex_name)), r);
		return this->platform;
	}

	//Print the found values from the text files
	void PrintDrop(){
		cout << d.lifetime << "\t>lifetime_" << endl;
		cout << d.score << "\t>score_" << endl;
		cout << d.type << "\t>type_" << endl;
	}

	void PrintCharacter(){
		cout << "width: " << c.width << endl;
		cout << "height: " << c.height << endl;
		cout << "Density: " << c.density << endl;
	}

	b2World* createWorldtxt(){
		this->world = new b2World(b2Vec2(w.gravx, w.gravy));
		return this->world;
	}

	GameEntity* createCharacter(E_TYPE e_type, b2World* world, sf::RenderWindow* window, float posx, float posy){
		this->character = new GameEntity(world, e_type, c.width, c.height, posx, posy, c.density, *(AllResManager::Instance().retrieveTexture(c.tex_name)), window);
		return this->character;
	}

	/*GameEntity* createChar(){
		this->character = new GameEntity(world, CHARACTER, c.width, c.height, posx, posy, c.density, *(AllResManager::Instance().retrieveTexture(c.tex_name)), window);
		return this->character;
		}*/

	GameEntity* createPlatform(E_TYPE e_type, b2World* world, sf::RenderWindow* window){
		this->platform = new GameEntity(world, e_type, p.width, p.height, p.posx, p.posy, c.density, *(AllResManager::Instance().retrieveTexture(p.tex_name)), window);
		return this->platform;
	}

	std::vector<GameEntity*> *makeLevelOne(b2World* world, sf::RenderWindow* window){
		readLevelOne("levelonn.txt", world, window);

		return &level_one_entities;
	}

private:

	//Access the drop object variables
	drop d;

	//Access the character object variables
	character c;
	platform p;

	world w;
	LevelOne lvlone;

	b2World* world;
	GameEntity* character;
	GameEntity* platform;
	std::vector<GameEntity*> level_one_entities;

};