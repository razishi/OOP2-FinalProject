#pragma once


#include "Ball.h"

class PinkBall : public Ball {
public:
    PinkBall(b2World* world);
    void create(float x, float y) override;
    void applyForces(float threshold) override;
    ~PinkBall() {};

private:
    bool m_stop;
};

