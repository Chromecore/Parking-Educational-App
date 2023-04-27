/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H



#include <Box2D/Box2D.h>

// Contact listener class for collisions
class ContactListener : public b2ContactListener
{
public:
    // Check for what kind of collision is happening
    void BeginContact(b2Contact* contact);
    // Finish the contact based on what kind of collision is happening
    void EndContact(b2Contact* contact);
    // Checks for valid collision between two hitboxes, one the drivable car
    bool IsValidCollision(int hitboxType1, int hitboxType2);
    // Weeds out hitboxes that are not in this level
    bool ObstacleHitboxIsRightLevel(int hitBoxLevel);
    int gameCurrLevel = 0;
    // Gets the current level in the contact listener
    int getCurrLevel();
    // Sets the current level in the contact listener
    void setCurrLevel(int);
};

#endif // CONTACTLISTENER_H
