#ifndef BLUEBALL_H
#define BLUEBALL_H

#include "Ball.h"

class BlueBall : public Ball {
public:
    BlueBall(b2World* world);
    void create(float x, float y) override;
    void getSmaller();
    ~BlueBall() {};
private:
    b2CircleShape m_circleShape;

};

#endif // BLUEBALL_H