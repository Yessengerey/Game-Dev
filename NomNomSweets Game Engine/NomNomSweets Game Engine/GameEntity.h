#pragma once
#include "PXWorldObject.h"

//Enum types for each object
enum E_TYPE{
	GROUND,
	CEILING,
	R_WALL,
	L_WALL,
	PLATFORM,
	CHARACTER,
	T_OBSTACLE,
	S_OBSTACLE,
	SWEET,
	VEGGIE,
	LIFE1,
	LIFE2
};


/*This class is responsible for storing all necessary information
about all possible game entities. All entities, that are needed to
be, are connected to their respective physical representation.*/
class GameEntity{
public:
	//Default constructor
	GameEntity();

	GameEntity(sf::RenderWindow* rw);

	//GameEntity constructor for square entities
	GameEntity(b2World* world, E_TYPE pe_type, const float& width, const float& height, const float& X, const float& Y, const float& density, sf::Texture& entity_texture, sf::RenderWindow* rw);

	//GameEntity constructor for square entities
	GameEntity(b2World* world, E_TYPE pe_type, const float& width, const float& height, const float& X, const float& Y, const float& density, sf::RenderWindow* rw);

	//GameEntity constructor for tirangular entities
	GameEntity(b2World* world, E_TYPE px_type, const b2Vec2 indeces[3], const float& X, const float& Y, sf::Texture& entity_texture, sf::RenderWindow* rw);

	~GameEntity();
	//Returns the physical object of an entity
	PXWorldObject* getPXObject();

	//Sets the physical object of an entity
	void setPXObject(PXWorldObject* new_px_obj);

	//Get the texture of the object
	sf::Texture* getEntityTexture();
	//Sets the texture of an entity
	void setEntityTexture(sf::Texture& new_texture);
	
	void setType(E_TYPE et){
		this->px_type = et;
	};
	E_TYPE getType(){
		return this->px_type;
	};


	float getWidth();
	void setWidth(float new_width);

	float getHeight();
	void setHeight(float new_height);

	void updateSprites();
	

	//Returns 1 if physical body of this entity is NULL
	//Else draws the physical body in the box2d world and return 0
	int add2World();

	void startContact() { m_contacting = true; };
	void endContact() { m_contacting = false; };

	bool m_contacting;

	float tempmove;
private:

	//entity type
	E_TYPE px_type;

	b2World* my_world;
	//Physical object of an entity
	PXWorldObject* pxworld_object;
	sf::RenderWindow* rend;
	//Texture of an entity object
	sf::Texture* entity_texture;

	//Sprite of the entity is stored within the object,
	//however will be defined where needed/appropriate
	//since some sprites of objects will have to be 
	//updated every frame.
	sf::Sprite entity_sprite;

	//Render Window object accessor
	//sf::RenderWindow* rend;

	float width;
	float height;
	float position_x;
	float position_y;
	float density;
};