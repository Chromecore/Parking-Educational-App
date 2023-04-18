#include "contactlistener.h"
#include "yellowlinehitbox.h"
#include <Box2D/Box2D.h>



void ContactListener::BeginContact(b2Contact* contact) {

  //check if fixture A was a ball
  void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  if ( bodyUserData )
    //static_cast<YellowLineHitbox*>( bodyUserData )->startContact();
    static_cast<b2Body*>( bodyUserData )->startContact();
  //check if fixture B was a ball
  bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if ( bodyUserData )
    static_cast<b2Body*>( bodyUserData )->startContact();

}

void ContactListener::EndContact(b2Contact* contact) {

  //check if fixture A was a ball
  void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  if ( bodyUserData )
    static_cast<b2Body*>( bodyUserData )->endContact();

  //check if fixture B was a ball
  bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if ( bodyUserData )
    static_cast<b2Body*>( bodyUserData )->endContact();

}

