#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "AllResManager.h"
#include "Game.h"
#include "GameEntity.h"
#include "ReadFile.h"
#include "WorldContactListener.h"
#include "MyTimer.h"


/* We need this to easily convert between pixel and real-world coordinates*/
static const float SCALE = 30.f;

static bool levelOne = true;
static bool levelTwo = false;
static bool levelThree = false;

//TO CHANGE LEVELS ENTER 1, 2, 3 TO level VARIABLE
static int level = 3;

WorldContactListener wCLI;

void charMovement(sf::RenderWindow* w, Game* g){
	GameEntity* temp = new GameEntity();
	for (int i = 0; i < g->all_entities.size(); i++){
		if (g->all_entities[i]->getType() == CHARACTER){
			temp = g->all_entities[i];
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		temp->getPXObject()->getPXBody()->SetLinearVelocity(b2Vec2(-8.0f, temp->getPXObject()->getPXBody()->GetLinearVelocity().y + 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		temp->getPXObject()->getPXBody()->SetLinearVelocity(b2Vec2(8.0f, temp->getPXObject()->getPXBody()->GetLinearVelocity().y + 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		temp->getPXObject()->getPXBody()->SetLinearVelocity(b2Vec2(temp->getPXObject()->getPXBody()->GetLinearVelocity().x, -8.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		temp->getPXObject()->getPXBody()->SetLinearVelocity(b2Vec2(temp->getPXObject()->getPXBody()->GetLinearVelocity().x, 8.0f));
	}

	sf::Event event;
	while (w->pollEvent(event)){
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
			w->close();
			break;
		}
	}
}

int main()
{
	/* PREPARE THE WINDOW */
	sf::RenderWindow Window(sf::VideoMode(1000, 600, 32), "NomNomSweets");
	Window.setFramerateLimit(60);
	float temp = 6.0f;
	/* CREATE THE 2D WORLD READ FROM FILE */
	ReadFile rf;
	rf.GetWorld("Resources/Settings/box2d_world.txt");
	b2World* World2D = rf.createWorldtxt();
	World2D->SetContactListener(&wCLI);

	sf::Texture Background;
	Background.loadFromFile("Resources/Textures/backgroundcandy.png");
	sf::Sprite bg;
	bg.setTexture(Background);

	Game game(10, 2, World2D, &Window);
	game.loadMusicTex();

	if (level == 1){
		game.LevelOne(World2D, &Window);
		game.addObjectsToWorld();
	}
	if (level == 2){
		game.LevelTwo(World2D, &Window);
		game.addObjectsToWorld();
	}
	if (level == 3){
		game.LevelThree(World2D, &Window);
		game.addObjectsToWorld();
	}
	/* MAIN LOOP */
	while (Window.isOpen()){
		Window.clear();
		//Set the time step of the world
		World2D->Step(1 / 60.0f, 8, 3);
		//draw the background in the window
		Window.draw(bg);

		if (level == 1){
			//update all of the sprites of all objects
			game.update();
			if (game.updateCollisions() == true){
				break;
			}
			if (game.updateCollisions() == false){
				break;
			}
			//deals with the movement of the character
			charMovement(&Window, &game);
			for (int i = 0; i < game.all_entities.size(); i++){
				if (game.all_entities[i]->getType() == VEGGIE){
					if (game.all_entities[i]->getPXObject()->getPXBody()->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)){
						temp = -temp;
					}
					game.all_entities[i]->getPXObject()->getPXBody()->SetLinearVelocity(b2Vec2(0.0f, temp));
				}
			}
		}
		if (level == 2){
			//update all of the sprites of all objects
			game.update();
			if (game.updateCollisions() == true){
				break;
			}
			if (game.updateCollisions() == false){
				break;
			}
			//deals with the movement of the character
			charMovement(&Window, &game);
			for (int i = 0; i < game.all_entities.size(); i++){
				if (game.all_entities[i]->getType() == VEGGIE){
					if (game.all_entities[i]->getPXObject()->getPXBody()->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)){
						temp = -temp;
					}
					game.all_entities[i]->getPXObject()->getPXBody()->SetLinearVelocity(b2Vec2(0.0f, temp));
				}
			}
		}
		if (level == 3){
			//update all of the sprites of all objects
			game.update();
			if (game.updateCollisions() == true){
				break;
			}
			if (game.updateCollisions() == false){
				break;
			}
			//deals with the movement of the character
			charMovement(&Window, &game);
			for (int i = 0; i < game.all_entities.size(); i++){
				if (game.all_entities[i]->getType() == VEGGIE){
					if (game.all_entities[i]->getPXObject()->getPXBody()->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)){
						temp = -temp;
					}
					game.all_entities[i]->getPXObject()->getPXBody()->SetLinearVelocity(b2Vec2(0.0f, temp));
				}
			}
		}


		Window.display();
	}
	return 0;
}
