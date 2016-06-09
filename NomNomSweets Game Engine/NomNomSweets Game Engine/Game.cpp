#include "Game.h"
#include "MyTimer.h"

Game::Game(int max_score, int max_hp, b2World* World, sf::RenderWindow* rw){
	this->max_score = max_score;
	this->max_hp = max_hp;
	this->World = World;
	this->wind = rw;
}

Game::~Game(){
	for (int i = 0; i < all_entities.size(); i++){
		delete all_entities[i];
	}
}

void Game::loadMusicTex(){
	//Pre-load all textures and audio files
	AllResManager::Instance().loadTexture("backgroundcandy.png");
	AllResManager::Instance().loadTexture("pinkground.png");
	AllResManager::Instance().loadTexture("new_ground.png");
	AllResManager::Instance().loadTexture("cotton_heart.png");
	AllResManager::Instance().loadTexture("heart.png");
	AllResManager::Instance().loadTexture("pinkplat.png");
	AllResManager::Instance().loadTexture("pinkthin.png");
	AllResManager::Instance().loadTexture("candy monster.png");
	AllResManager::Instance().loadTexture("red_monster.png");
	AllResManager::Instance().loadTexture("sweet1.png");
	AllResManager::Instance().loadTexture("sweet2.png");
	AllResManager::Instance().loadTexture("sweet3.png");
	AllResManager::Instance().loadTexture("veggie1.png");
	AllResManager::Instance().loadTexture("veggie2.png");
	AllResManager::Instance().loadTexture("veggie3.png");

	AllResManager::Instance().loadMusic("Spy_Hunter.wav");
	AllResManager::Instance().loadSFX("mario_jump.wav");
	AllResManager::Instance().loadSFX("death.wav");

	AllResManager::Instance().playMusic("Spy_Hunter.wav");
	AllResManager::Instance().loopMusic("Spy_Hunter.wav");
}

void Game::loadBounds(sf::RenderWindow* rw){
	//Pre-load necessary and constant objects 

	all_entities.push_back(new GameEntity(this->World, GROUND, 1000.0f, 16.f, 500.0f, 500.0f, 0.0f, *(AllResManager::Instance().retrieveTexture("pinkground.png")), wind));
	all_entities.push_back(new GameEntity(this->World, CEILING, 1000.0f, 5.0f, 500.0f, -10.0f, 1.0f, wind));
	all_entities.push_back(new GameEntity(this->World, R_WALL, 16.0f, 600.0f, 1030.0f, 300.0f, 1.0f, wind));
	all_entities.push_back(new GameEntity(this->World, L_WALL, 16.0f, 600.0f, -30.0f, 300.0f, 1.0f, wind));

	all_entities[0]->add2World();
	all_entities[1]->add2World();
	all_entities[2]->add2World();
	all_entities[3]->add2World();
}

void Game::createElement(E_TYPE t, b2World* w, sf::RenderWindow* d, float x, float y){
	if (t == CHARACTER){
		readF.GetCharacter("Resources/Settings/character.txt");
		GameEntity* new_Char = readF.createCharacter(CHARACTER, w, d, x, y);
		all_entities.push_back(new_Char);
	}
	if (t == PLATFORM){
		readF.GetPlatform("Resources/Settings/platform.txt");
		GameEntity* new_plat = readF.createPlatform(PLATFORM, w, d);
		all_entities.push_back(new_plat);
	}
}

void Game::loadObjResources(sf::RenderWindow* rw){
	//game_on = true;

	b2Vec2 inds[3];
	inds[0] = b2Vec2(-3.0f, 3.0f);
	inds[1] = b2Vec2(0.0f, -3.0f);
	inds[2] = b2Vec2(3.0f, 3.0f);
	
	//all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 900.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));
	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 800.0f, 200.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet1.png")), wind));
	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 300.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet2.png")), wind));
	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 100.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet3.png")), wind));
	all_entities.push_back(new GameEntity(World, VEGGIE, drop_size, drop_size, 400.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("veggie1.png")), wind));
	all_entities.push_back(new GameEntity(World, VEGGIE, drop_size, drop_size, 500.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("veggie2.png")), wind));
	all_entities.push_back(new GameEntity(World, VEGGIE, drop_size, drop_size, 600.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("veggie3.png")), wind));

}

void Game::update(){
	for (int i = 0; i < all_entities.size(); i++){
		all_entities[i]->updateSprites();
	}
	sf::Font font;
	font.loadFromFile("Aller_Bd.ttf");

	sf::Text text;

	text.setFont(font);
	text.setString("SCORE:" + std::to_string(n_collisions*10));

	text.setPosition(sf::Vector2f(30.0f, 550.0f));

	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	wind->draw(text);

}

void Game::addObjectsToWorld(){
	for (int i = 0; i < all_entities.size(); i++){
		all_entities[i]->add2World();
	}
}

bool Game::updateCollisions(){
	for (int i = 0; i < this->all_entities.size(); i++){
		if (this->all_entities[i]->getType() == SWEET && this->all_entities[i]->m_contacting == true){
			delete this->all_entities[i];
			all_entities.erase(std::find(this->all_entities.begin(), this->all_entities.end(), this->all_entities[i]));
			n_collisions++;
		}
		if (this->all_entities[i]->getType() == VEGGIE && this->all_entities[i]->m_contacting == true){
			delete this->all_entities[i];
			all_entities.erase(std::find(this->all_entities.begin(), this->all_entities.end(), this->all_entities[i]));
			this->max_hp--;
		}
	}
	if (n_collisions == 3){
		return true;
	}
	if (this->max_hp == 0){
		return false;
	}
}

void Game::createLevelOne(b2World* w, sf::RenderWindow* d){
	std::vector<GameEntity*> level_one_ent = *(readF.makeLevelOne(w, d));

	for (int i = 0; i < level_one_ent.size(); i++){
		all_entities.push_back(level_one_ent[i]);
	}
}

void Game::LevelOne(b2World* w, sf::RenderWindow* d){
	all_entities.push_back(new GameEntity(this->World, GROUND, 1000.0f, 16.f, 500.0f, 500.0f, 0.0f, *(AllResManager::Instance().retrieveTexture("pinkground.png")), wind));
	all_entities.push_back(new GameEntity(this->World, CEILING, 1000.0f, 5.0f, 500.0f, -10.0f, 1.0f, wind));
	all_entities.push_back(new GameEntity(this->World, R_WALL, 16.0f, 600.0f, 1030.0f, 300.0f, 1.0f, wind));
	all_entities.push_back(new GameEntity(this->World, L_WALL, 16.0f, 600.0f, -30.0f, 300.0f, 1.0f, wind));

	

	all_entities.push_back(new GameEntity(this->World, CHARACTER, 100.0f, 100.0f, 170.0f, 400.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("candy monster.png")), wind));

	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 900.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));
	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 100.0f, 150.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));
	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 100.0f, 350.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));

	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 100.0f, 100.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet1.png")), wind));
	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 900.0f, 250.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet2.png")), wind));
	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 100.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet3.png")), wind));
	all_entities.push_back(new GameEntity(World, VEGGIE, drop_size, drop_size, 600.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("veggie3.png")), wind));
	all_entities.push_back(new GameEntity(World, VEGGIE, drop_size, drop_size, 500.0f, 100.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("veggie1.png")), wind));

	all_entities.push_back(new GameEntity(World, LIFE1, drop_size, drop_size, 30.0f, 20.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("heart.png")), wind));
	all_entities.push_back(new GameEntity(World, LIFE2, drop_size, drop_size, 70.0f, 20.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("heart.png")), wind));
}

void Game::LevelTwo(b2World* w, sf::RenderWindow* d){
	all_entities.push_back(new GameEntity(this->World, GROUND, 1000.0f, 16.f, 500.0f, 500.0f, 0.0f, *(AllResManager::Instance().retrieveTexture("pinkground.png")), wind));
	all_entities.push_back(new GameEntity(this->World, CEILING, 1000.0f, 5.0f, 500.0f, -10.0f, 1.0f, wind));
	all_entities.push_back(new GameEntity(this->World, R_WALL, 16.0f, 600.0f, 1030.0f, 300.0f, 1.0f, wind));
	all_entities.push_back(new GameEntity(this->World, L_WALL, 16.0f, 600.0f, -30.0f, 300.0f, 1.0f, wind));

	all_entities.push_back(new GameEntity(World, LIFE1, drop_size, drop_size, 840.0f, 550.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("heart.png")), wind));
	all_entities.push_back(new GameEntity(World, LIFE2, drop_size, drop_size, 900.0f, 550.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("heart.png")), wind));

	all_entities.push_back(new GameEntity(this->World, CHARACTER, 100.0f, 100.0f, 170.0f, 400.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("candy monster.png")), wind));

	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 500.0f, 400.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));
	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 100.0f, 150.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));
	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 900.0f, 150.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));
	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 500.0f, 250.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));

	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 500.0f, 350.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet1.png")), wind));
	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 100.0f, 100.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet2.png")), wind));
	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 900.0f, 100.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet3.png")), wind));
	all_entities.push_back(new GameEntity(World, VEGGIE, drop_size, drop_size, 300.0f, 450.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("veggie3.png")), wind));
	all_entities.push_back(new GameEntity(World, VEGGIE, drop_size, drop_size, 700.0f, 350.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("veggie1.png")), wind));

}

void Game::LevelThree(b2World* w, sf::RenderWindow* d){
	all_entities.push_back(new GameEntity(this->World, GROUND, 1000.0f, 16.f, 500.0f, 500.0f, 0.0f, *(AllResManager::Instance().retrieveTexture("pinkground.png")), wind));
	all_entities.push_back(new GameEntity(this->World, CEILING, 1000.0f, 5.0f, 500.0f, -10.0f, 1.0f, wind));
	all_entities.push_back(new GameEntity(this->World, R_WALL, 16.0f, 600.0f, 1030.0f, 300.0f, 1.0f, wind));
	all_entities.push_back(new GameEntity(this->World, L_WALL, 16.0f, 600.0f, -30.0f, 300.0f, 1.0f, wind));

	all_entities.push_back(new GameEntity(World, LIFE1, drop_size, drop_size, 840.0f, 550.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("heart.png")), wind));
	all_entities.push_back(new GameEntity(World, LIFE2, drop_size, drop_size, 900.0f, 550.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("heart.png")), wind));

	all_entities.push_back(new GameEntity(this->World, CHARACTER, 100.0f, 100.0f, 170.0f, 400.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("candy monster.png")), wind));

	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 100.0f, 300.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));
	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 100.0f, 150.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));
	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 500.0f, 350.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));
	all_entities.push_back(new GameEntity(World, PLATFORM, 300.0f, 20.0f, 500.0f, 200.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("pinkthin.png")), wind));

	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 500.0f, 350.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet1.png")), wind));
	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 100.0f, 100.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet2.png")), wind));
	all_entities.push_back(new GameEntity(World, SWEET, drop_size, drop_size, 900.0f, 100.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("sweet3.png")), wind));
	all_entities.push_back(new GameEntity(World, VEGGIE, drop_size, drop_size, 300.0f, 450.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("veggie3.png")), wind));
	all_entities.push_back(new GameEntity(World, VEGGIE, drop_size, drop_size, 700.0f, 350.0f, 1.0f, *(AllResManager::Instance().retrieveTexture("veggie1.png")), wind));

}