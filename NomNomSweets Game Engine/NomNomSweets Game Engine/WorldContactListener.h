#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "GameEntity.h"

class WorldContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();


		if (static_cast<GameEntity*>(bodyUserData1)->getType() == CHARACTER && static_cast<GameEntity*>(bodyUserData2)->getType() == SWEET){
			static_cast<GameEntity*>(bodyUserData1)->startContact();
			static_cast<GameEntity*>(bodyUserData2)->startContact();
		}
		if (static_cast<GameEntity*>(bodyUserData1)->getType() == CHARACTER && static_cast<GameEntity*>(bodyUserData2)->getType() == VEGGIE){
			static_cast<GameEntity*>(bodyUserData1)->startContact();
			static_cast<GameEntity*>(bodyUserData2)->startContact();
		}
		if ((static_cast<GameEntity*>(bodyUserData1)->getType() == VEGGIE && static_cast<GameEntity*>(bodyUserData2)->getType() == GROUND) || (static_cast<GameEntity*>(bodyUserData1)->getType() == VEGGIE && static_cast<GameEntity*>(bodyUserData2)->getType() == CEILING)){
			static_cast<GameEntity*>(bodyUserData1)->startContact();
			static_cast<GameEntity*>(bodyUserData2)->startContact();
		}
		//}
		//check if fixture B was a ball

		/*if (bodyUserData2){
			if (static_cast<GameEntity*>(bodyUserData)->getType() == SWEET){
			static_cast<GameEntity*>(bodyUserData)->startContact();
			}
			}*/
	}

	void EndContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
		if (static_cast<GameEntity*>(bodyUserData)->getType() == CHARACTER){
			static_cast<GameEntity*>(bodyUserData)->endContact();
		}

		//check if fixture B was a ball
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
			if (static_cast<GameEntity*>(bodyUserData)->getType() == SWEET || static_cast<GameEntity*>(bodyUserData)->getType() == VEGGIE){
			static_cast<GameEntity*>(bodyUserData)->endContact();
		}

	}
};