#include "contactlistener.h"
#include <Box2D/Box2D.h>



void ContactListener::BeginContact(b2Contact* contact) {
    /*
  //check if fixture A & fixture B are b2Body, then decide what to do based on what kind of hitbox it is.
  void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
  void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
  if ( bodyUserData1 && bodyUserData2 )
  {
     int hitboxType1 = static_cast<b2Body*>( bodyUserData1 )->getHitboxType();
     int hitboxType2 = static_cast<b2Body*>( bodyUserData1 )->getHitboxType();
     if (IsValidCollision(hitboxType1, hitboxType2))
     {
        //First determine which fixture is bigger. Since driveable car is always 0,
        // it will always be lower than the other fixture. Thus, based on what the
        // higher fixture's hitbox type is, we will give feedback to the lower fixture.
        if (hitboxType1 > hitboxType2)
            //This assumes hitbox 2 is the driveable car.
        {
            //Determine what to do based on what type hitbox 1 is.
           switch (hitboxType1)
           {
           case 1:
               //increment number of goal collisions by 1 for hitboxType2.
               static_cast<b2Body*>( bodyUserData2 )->startGoalContact();
               break;
           case 2:
               //increment number of negative contacts by 1 for hitboxType2.
               static_cast<b2Body*>( bodyUserData2 )->startHazardContact();
               break;
           case 3:
               //increment number of negative contacts by 1 for hitboxType2.
               static_cast<b2Body*>( bodyUserData2 )->startHazardContact();
               break;
           }
        }
        //This assumes hitbox 1 is the driveable car.
        else
        {
            //Determine what to do based on what type hitbox 2 is.
            switch (hitboxType2)
            {
            case 1:
                //increment number of goal collisions by 1 for hitboxType1.
                static_cast<b2Body*>( bodyUserData1 )->startGoalContact();
                break;
            case 2:
                //increment number of negative contacts by 1 for hitboxType1.
                static_cast<b2Body*>( bodyUserData1 )->startHazardContact();
                break;
            case 3:
                //increment number of negative contacts by 1 for hitboxType1.
                static_cast<b2Body*>( bodyUserData1 )->startHazardContact();
                break;
            }
        }

     }
  }
  */

        //GRANDFATHER CODE THAT IS HERE FOR REFERENCE IN CASE CURRENT CODE DOESN'T WORK. DELETE LATER
    //check if fixture A is a b2Body, then decide what to do based on what kind of hitbox it is.
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
      static_cast<b2Body*>( bodyUserData )->startGoalContact();

    //check if fixture B is a b2Body, then decide what to do based on what kind of hitbox it is.
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
      static_cast<b2Body*>( bodyUserData )->startGoalContact();


}

void ContactListener::EndContact(b2Contact* contact) {
    /*
    //check if fixture A & fixture B are b2Body, then decide what to do based on what kind of hitbox it is.
    void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData1 && bodyUserData2 )
    {
       int hitboxType1 = static_cast<b2Body*>( bodyUserData1 )->getHitboxType();
       int hitboxType2 = static_cast<b2Body*>( bodyUserData1 )->getHitboxType();
       if (IsValidCollision(hitboxType1, hitboxType2))
       {
          //First determine which fixture is bigger. Since driveable car is always 0,
          // it will always be lower than the other fixture. Thus, based on what the
          // higher fixture's hitbox type is, we will give feedback to the lower fixture.
          if (hitboxType1 > hitboxType2)
              //This assumes hitbox 2 is the driveable car.
          {
              //Determine what to do based on what type hitbox 1 is.
             switch (hitboxType1)
             {
             case 1:
                 //increment number of goal collisions by 1 for hitboxType2.
                 static_cast<b2Body*>( bodyUserData2 )->endGoalContact();
                 break;
             case 2:
                 //increment number of negative contacts by 1 for hitboxType2.
                 static_cast<b2Body*>( bodyUserData2 )->endHazardContact();
                 break;
             case 3:
                 //increment number of negative contacts by 1 for hitboxType2.
                 static_cast<b2Body*>( bodyUserData2 )->endHazardContact();
                 break;
             }
          }
          //This assumes hitbox 1 is the driveable car.
          else
          {
              //Determine what to do based on what type hitbox 2 is.
              switch (hitboxType2)
              {
              case 1:
                  //increment number of goal collisions by 1 for hitboxType1.
                  static_cast<b2Body*>( bodyUserData1 )->endGoalContact();
                  break;
              case 2:
                  //increment number of negative contacts by 1 for hitboxType1.
                  static_cast<b2Body*>( bodyUserData1 )->endHazardContact();
                  break;
              case 3:
                  //increment number of negative contacts by 1 for hitboxType1.
                  static_cast<b2Body*>( bodyUserData1 )->endHazardContact();
                  break;
              }
          }

       }
    }
    */


     //GRANDFATHER CODE THAT IS HERE FOR REFERENCE IN CASE CURRENT CODE DOESN'T WORK. DELETE LATER
  //check if fixture A is a b2Body, then decide what to do based on what kind of hitbox it is.
  void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  if ( bodyUserData )
    static_cast<b2Body*>( bodyUserData )->endGoalContact();

  //check if fixture B is a b2Body, then decide what to do based on what kind of hitbox it is.
  bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if ( bodyUserData )
    static_cast<b2Body*>( bodyUserData )->endGoalContact();

}

bool ContactListener::IsValidCollision(int hitboxType1, int hitboxType2)
{
    //Checks to see if one hit box from either fixture is a driveable car
    // and the other is anything BUT a driveable car.
    return ((hitboxType1==0 && hitboxType2 != 0) || (hitboxType1 != 0 && hitboxType2 == 0));
}
