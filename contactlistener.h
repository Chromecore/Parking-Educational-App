/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H



#include <Box2D/Box2D.h>


class ContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    bool IsValidCollision(int hitboxType1, int hitboxType2);
    bool ObstacleHitboxIsRightLevel(int hitBoxLevel);
    int gameCurrLevel = 0;
    int getCurrLevel();
    void setCurrLevel(int);
};

#endif // CONTACTLISTENER_H
