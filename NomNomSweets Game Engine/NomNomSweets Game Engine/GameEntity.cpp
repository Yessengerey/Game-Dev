#include "GameEntity.h"
#include "AllResManager.h"

GameEntity::GameEntity(){

}

//Default constructor for GameEntity class
GameEntity::GameEntity(sf::RenderWindow* rw){
	//this->rend = rw;
}

/*GameEntity constructor to create SQUARE dynamic and non-dynamic entities of the game
@param: world - Box2D world into which the physical body will eventually be placed
@param: pe_type - game entity type of the object
@param: width - width of the rectangular object in pixels
@param: height - height of the rectangular object in pixels
@param: density - density of the physical object
@param: X - x position of the entity on the screen
@param: Y - y position of the entity on the screen
@param: rw - RenderWindow object passed down to allow acces to draw function*/

GameEntity::GameEntity(b2World* world, E_TYPE pe_type, const float& width, const float& height, const float& X, const float& Y, const float& density, sf::Texture& tex, sf::RenderWindow* rw){
	PX_TYPE pxt = PX_QUAD; //Physics type of all these objects is quad, since all of these shapes resemble a quad
	bool dynamic = false;
	rend = rw;
	px_type = pe_type;
	my_world = world;
	this->width = width;
	this->height = height;
	this->position_x = X;
	this->position_y = Y;
	this->density = density;
	this->tempmove = 6.0f;
	//If the entity is of type ground or platform they are defined as static objects since they are not supposed to move
	if (pe_type == GROUND || pe_type == PLATFORM || pe_type == LIFE1 || pe_type == LIFE2){
		dynamic = false;
	}
	//If the entity is of type character, obstacle, sweet or veggie, they are defined as dynamic objects
	if (pe_type == CHARACTER || pe_type == S_OBSTACLE || pe_type == SWEET || pe_type == VEGGIE){
		dynamic = true;
	}

	//Create the physics representation of this entity
	this->pxworld_object = new PXWorldObject(world, pxt, width, height, X, Y, density, dynamic);

	this->m_contacting = false;

	this->entity_texture = &tex;

	this->pxworld_object->getPXBody()->SetUserData(this);
	

}

/*GameEntity constructor to create dynamic and non-dynamic square objects
THAT HAVE NO TEXTURE or sprite associated with them (not needed; ceiling,
walls)*/
GameEntity::GameEntity(b2World* world, E_TYPE pe_type, const float& width, const float& height, const float& X, const float& Y, const float& density, sf::RenderWindow* rw){
	PX_TYPE pxt = PX_QUAD;
	bool dynamic = false;
	rend = rw;
	px_type = pe_type;
	my_world = world;
	//If the entity is of type ground or platform they are defined as static objects since they are not supposed to move
	if (pe_type == GROUND || pe_type == PLATFORM || pe_type == LIFE1 || pe_type == LIFE2){
		dynamic = false;
	}
	//If the entity is of type character, obstacle, sweet or veggie, they are defined as dynamic objects
	if (pe_type == CHARACTER || pe_type == S_OBSTACLE || pe_type == SWEET || pe_type == VEGGIE){
		dynamic = true;
	}
	this->m_contacting = false;
	//Create the physics representation of this entity
	this->pxworld_object = new PXWorldObject(world, pxt, width, height, X, Y, density, dynamic);
	this->pxworld_object->getPXBody()->SetUserData(this);
}

/*
GameEntity constructor for TRIANGLE entities
@param: world - the Box2D world
@param: pe_type - the entity type of the object
@param: ind[] - indeces of the triangle
@param: X - position X of the entity on the screen
@param: Y - position Y of the entity on the screen
*/
GameEntity::GameEntity(b2World* world, E_TYPE pe_type, const b2Vec2 ind[3], const float& X, const float& Y, sf::Texture& tex, sf::RenderWindow* rw){
	PX_TYPE pxt = PX_TRIANGLE;
	//Any triangle objects are defined as static
	bool dynamic = false;
	rend = rw;
	my_world = world;

	this->pxworld_object = new PXWorldObject(world, pxt, ind, X, Y, dynamic);

	this->entity_texture = &tex;
	this->m_contacting = false;
}

GameEntity::~GameEntity(){
	
	this->my_world->DestroyBody(this->pxworld_object->getPXBody());
}

//Returns the physical representation for an entity
PXWorldObject* GameEntity::getPXObject(){
	return this->pxworld_object;
}

//Sets the physical representation of this object to a given physical representation
//@param: px - PXWorldObject 
void GameEntity::setPXObject(PXWorldObject* px){
	this->pxworld_object = px;
}

sf::Texture* GameEntity::getEntityTexture(){
	return this->entity_texture;
}

void GameEntity::setEntityTexture(sf::Texture& new_tex){
	this->entity_texture = &new_tex;
}

int GameEntity::add2World(){
	if (this->getPXObject()->getPXBody() == NULL){
		return 1;
	}

	this->getPXObject()->add2Screen();

	return 0;
}

float GameEntity::getWidth(){
	return this->width;
}

void GameEntity::setWidth(float new_width){
	this->width = new_width;
}

float GameEntity::getHeight(){
	return this->width;
}

void GameEntity::setHeight(float new_height){
	this->height = new_height;
}

void GameEntity::updateSprites(){
	sf::Sprite spr;
	if (this->getType() == GROUND){
		spr.setTexture(*this->getEntityTexture());
		spr.setOrigin(this->width / 2, this->height / 2);
		spr.setPosition(this->getPXObject()->getPXBody()->GetPosition().x * 30.0f, this->getPXObject()->getPXBody()->GetPosition().y * 30.0f);

	}
	if (this->getType() == PLATFORM){
		spr.setTexture(*this->getEntityTexture());
		spr.setOrigin(this->width / 2, this->height / 2);
		spr.setPosition(this->getPXObject()->getPXBody()->GetPosition().x * 30.0f, this->getPXObject()->getPXBody()->GetPosition().y * 30.0f);
	}
	if (this->getType() == CHARACTER){
		spr.setTexture(*this->getEntityTexture());
		spr.setOrigin(this->width / 2, this->height / 2);
		spr.setPosition(this->getPXObject()->getPXBody()->GetPosition().x * 30.0f, this->getPXObject()->getPXBody()->GetPosition().y * 30.0f);
	}
	if (this->getType() == SWEET){
		spr.setTexture(*this->getEntityTexture());
		spr.setOrigin(this->width / 2, this->height / 2);
		spr.setPosition(this->getPXObject()->getPXBody()->GetPosition().x * 30.0f, this->getPXObject()->getPXBody()->GetPosition().y * 30.0f);
		spr.setRotation(180 / b2_pi * this->getPXObject()->getPXBody()->GetAngle());
	}
	if (this->getType() == VEGGIE){
		spr.setTexture(*this->getEntityTexture());
		spr.setOrigin(this->width / 2, this->height / 2);
		spr.setPosition(this->getPXObject()->getPXBody()->GetPosition().x * 30.0f, this->getPXObject()->getPXBody()->GetPosition().y * 30.0f);
		spr.setRotation(180 / b2_pi * this->getPXObject()->getPXBody()->GetAngle());
	}
	if (this->getType() == LIFE1){
		spr.setTexture(*this->getEntityTexture());
		spr.setOrigin(this->width / 2, this->height / 2);
		spr.setPosition(this->getPXObject()->getPXBody()->GetPosition().x * 30.0f, this->getPXObject()->getPXBody()->GetPosition().y * 30.0f);
		spr.setRotation(180 / b2_pi * this->getPXObject()->getPXBody()->GetAngle());
	}
	if (this->getType() == LIFE2){
		spr.setTexture(*this->getEntityTexture());
		spr.setOrigin(this->width / 2, this->height / 2);
		spr.setPosition(this->getPXObject()->getPXBody()->GetPosition().x * 30.0f, this->getPXObject()->getPXBody()->GetPosition().y * 30.0f);
		spr.setRotation(180 / b2_pi * this->getPXObject()->getPXBody()->GetAngle());
	}
	this->rend->draw(spr);
}
