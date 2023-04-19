#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H



#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    bool IsValidCollision(int hitboxType1, int hitboxType2);
};

#endif // CONTACTLISTENER_H