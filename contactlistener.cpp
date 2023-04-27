/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "contactlistener.h"
#include <Box2D/Box2D.h>
#include <QDebug>

void ContactListener::BeginContact(b2Contact* contact) {

  //check if fixture A & fixture B are b2Body, then decide what to do based on what kind of hitbox it is.
  void* bodyUserData1 = contact->GetFixtureA()->GetBody();
  void* bodyUserData2 = contact->GetFixtureB()->GetBody();
  //if ( bodyUserData1) qDebug()<< "Found Fixture One";
  //if ( bodyUserData2) qDebug()<< "Found Fixture Two";
  if ( bodyUserData1 && bodyUserData2 )
  {
     int hitboxType1 = static_cast<b2Body*>( bodyUserData1 )->getHitboxType();
     int hitboxType2 = static_cast<b2Body*>( bodyUserData2 )->getHitboxType();
     if (IsValidCollision(hitboxType1, hitboxType2))
     {
        //First determine which fixture is bigger. Since driveable car is always 0,
        // it will always be lower than the other fixture. Thus, based on what the
        // higher fixture's hitbox type is, we will give feedback to the lower fixture.
        if (hitboxType1 > hitboxType2 && ObstacleHitboxIsRightLevel(static_cast<b2Body*>( bodyUserData1 )->getLevel()))
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
               static_cast<b2Body*>( bodyUserData2 )->setFailedPark(true);
               break;
           }
        }
        //This assumes hitbox 1 is the driveable car.
        else if (ObstacleHitboxIsRightLevel(static_cast<b2Body*>( bodyUserData2 )->getLevel()))
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
                static_cast<b2Body*>( bodyUserData1 )->setFailedPark(true);
                break;
            }
        }

     }
  }
}

void ContactListener::EndContact(b2Contact* contact) {

    //check if fixture A & fixture B are b2Body, then decide what to do based on what kind of hitbox it is.
    void* bodyUserData1 = contact->GetFixtureA()->GetBody();
    void* bodyUserData2 = contact->GetFixtureB()->GetBody();
    //if ( bodyUserData1) qDebug()<< "Left Fixture One";
    //if ( bodyUserData2) qDebug()<< "Left Fixture Two";
    if ( bodyUserData1 && bodyUserData2 )
    {
       int hitboxType1 = static_cast<b2Body*>( bodyUserData1 )->getHitboxType();
       int hitboxType2 = static_cast<b2Body*>( bodyUserData2 )->getHitboxType();
       if (IsValidCollision(hitboxType1, hitboxType2))
       {
          //First determine which fixture is bigger. Since driveable car is always 0,
          // it will always be lower than the other fixture. Thus, based on what the
          // higher fixture's hitbox type is, we will give feedback to the lower fixture.
          if (hitboxType1 > hitboxType2 && ObstacleHitboxIsRightLevel(static_cast<b2Body*>( bodyUserData1 )->getLevel()))
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
                 break;
             }
          }
          //This assumes hitbox 1 is the driveable car.
          else if (ObstacleHitboxIsRightLevel(static_cast<b2Body*>( bodyUserData2 )->getLevel()))
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
                  break;
              }
          }

       }
    }
}

bool ContactListener::IsValidCollision(int hitboxType1, int hitboxType2)
{
    //Checks to see if one hit box from either fixture is a driveable car
    // and the other is anything BUT a driveable car.
    return ((hitboxType1==0 && hitboxType2 != 0) || (hitboxType1 != 0 && hitboxType2 == 0));
}

bool ContactListener::ObstacleHitboxIsRightLevel(int hitBoxLevel)
{
    return (hitBoxLevel == 0 || (hitBoxLevel == gameCurrLevel));
    //return true;
}

int ContactListener::getCurrLevel()
{
    return gameCurrLevel;
}

void ContactListener::setCurrLevel(int currLevel)
{
    gameCurrLevel = currLevel;
}
