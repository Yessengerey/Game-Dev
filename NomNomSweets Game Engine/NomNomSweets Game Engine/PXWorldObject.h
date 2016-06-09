#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>


enum PX_TYPE{
	PX_QUAD,
	PX_TRIANGLE
};


/*This class acts as a representation of the Box2D world in
which various physical objects exist. All objects will need
to be created through this physics world.*/
class PXWorldObject{
public:
	//Default constructor
	PXWorldObject();
	
	//
	PXWorldObject(b2Vec2 world_gravity, PX_TYPE px_type);
	
	//Physics constructor for square objects
	PXWorldObject(b2World* world, PX_TYPE px_type, const float& width, const float& height, const float& X, const float& Y, const float& density, bool isDynamic = false);

	//Physics constructor for triangle objects (polygon shapes)
	PXWorldObject(b2World* world, PX_TYPE px_type, const b2Vec2 indeces[3], const float& X, const float& Y, bool isDynamic = false);

	//Destructor
	~PXWorldObject();

	//Return the created Box2D world
	inline b2World* getWorld(){ return world; };
	//Set the box2d world
	void setWorld(b2World* new_2d_world);
	
	//Return the gravity of the world
	b2Vec2 getWorldGravity();
	//Set the gravity of the world
	void setWorldGravity(b2Vec2 mew_world_gravity);
	
	//Return the Box2D body of an object
	inline b2Body* getPXBody(){ return px_body; };
	//Set the box2d body
	void setPXBody(b2Body* new_body);

	//Return the body of an object
	b2Vec2 getBodyPosition();

	//Returns the physical type of an object
	PX_TYPE getPXType();

	//Sets the physical type of an object
	void setPXType(PX_TYPE new_px_type);

	//Adds a physical body to the Box2D world
	void add2Screen();
	
	//Scaling of 30.0f, since by standard, 1 unit in Box2D is equivalent to 30 pixels on screen
	const float SCALE = 30.f;

	//Density
	float dens = 0.0f;
private:
	//Gravitational force
	b2Vec2 world_gravity = b2Vec2(0.0f, 9.8f);

	//Box2D world
	b2World* world;

	//Physical body
	b2Body* px_body;
	
	//Definition of the physical body
	b2BodyDef body_def;

	//Definition of the fixture of the occupying space in the world by this object
	b2FixtureDef fixture_def;

	//Shape of an object
	b2PolygonShape shape;

	//Physical type
	PX_TYPE pxt;


	std::vector<PXWorldObject> px_objects;
/*
	std::vector<PXSquare> px_square;
	std::vector<PXTriangle> px_triangles;*/

};