#include "PXWorldObject.h"

//Default constructor
PXWorldObject::PXWorldObject(){

}

//Destructor: deletes physical bodies from the world
PXWorldObject::~PXWorldObject(){
	this->px_body->GetWorld()->DestroyBody(this->px_body);
}

/*Constructor for square objects in the physical world
@param: world - Box2D world
@param: t - type of the physical object in the world
@param: w - width of the rectangular physical object
@param: h - height of the rectangular physical object
@param: X - x position of the physical object in space
@param: Y - y position of the physical object in space
@param: den - density of the object
@param: d - is object dynamic?
*/
PXWorldObject::PXWorldObject(b2World* world, PX_TYPE t, const float& w, const float& h, const float& X, const float& Y, const float& den, bool d){
	//setWorld(world);
	
	this->pxt = t;

	this->body_def.position = b2Vec2(X / SCALE, Y / SCALE);
	if (d == true){
		this->body_def.type = b2_dynamicBody;
	}
	else if (d == false){
		this->body_def.type = b2_staticBody;
	}
	this->px_body = world->CreateBody(&this->body_def);

	shape.SetAsBox((w / 2) / SCALE, (h / 2) / SCALE);

	this->fixture_def.density = den;
	this->fixture_def.shape = &shape;

}
/*
Physical constructor for triangular objects
@param ind[] - indeces of the triangle in space
*/
PXWorldObject::PXWorldObject(b2World* world, PX_TYPE t, const b2Vec2 ind[3], const float& X, const float& Y, bool d){
	//setWorld(world);

	this->pxt = t;

	this->body_def.position = b2Vec2(X / SCALE, Y / SCALE);
	if (d == true){
		this->body_def.type = b2_dynamicBody;
	}
	else if (d == false){
		this->body_def.type = b2_staticBody;
	}
	this->px_body = world->CreateBody(&this->body_def);


	shape.Set(ind, 3);

	this->fixture_def.density = 0.0f;
	this->fixture_def.shape = &shape;

}

//Sets the Box2D world for objects
void PXWorldObject::setWorld(b2World* w){
	this->world = w;
}

//Sets the world's gravity
void PXWorldObject::setWorldGravity(b2Vec2 g){
	this->world_gravity = g;
}

//Returns the world's gravity
b2Vec2 PXWorldObject::getWorldGravity(){
	return this->world_gravity;
}

//Sets the physical body (b2Body)
void PXWorldObject::setPXBody(b2Body* b){
	this->px_body = b;
}

//Returns the type of the phyiscal object
PX_TYPE PXWorldObject::getPXType(){
	return this->pxt;
}

//Sets the type of the physical object
void PXWorldObject::setPXType(PX_TYPE pt){
	this->pxt = pt;
}

//Adds physical objects to the world through fixtures
void PXWorldObject::add2Screen(){
	if (this->body_def.type == b2_dynamicBody){
		this->px_body->CreateFixture(&this->fixture_def);
	}
	else{
		this->px_body->CreateFixture(&this->shape, this->dens);
	}
}