#pragma once


#include <box2d/box2d.h>
#include "BlueBall.h"
#include "PinkBall.h"  // Include the PinkBall header

class MyContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override {
        uintptr_t bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
        uintptr_t bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;

        if (bodyUserDataA && bodyUserDataB) {
            BlueBall* blueBallA = reinterpret_cast<BlueBall*>(bodyUserDataA);
            PinkBall* pinkBallB = reinterpret_cast<PinkBall*>(bodyUserDataB);

          
        }
    }
};

