#include "PinkBall.h"

PinkBall::PinkBall(b2World* world) : Ball(world), m_stop(false) {
    m_ballColor = sf::Color(255, 192, 203, 128); // Light pink color
}

void PinkBall::create(float x, float y) { //create pink ball
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / 100.0f, y / 100.0f);
    b2Body* body = m_world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 0.09f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.6f;
    fixtureDef.filter.categoryBits = CATEGORY_PINKBALL;
    fixtureDef.filter.maskBits = CATEGORY_PINKBALL | CATEGORY_BROWNBALL | CATEGORY_STONE | CATEGORY_OTHER;

    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    m_bodies.push_back(body);

    sf::CircleShape circle(10.f);
    circle.setOrigin(10.f, 10.f);
    circle.setFillColor(m_ballColor);
    circle.setPosition(x, y);
    m_circles.push_back(circle);
}

void PinkBall::applyForces(float threshold) {
    if (m_stop) {
        for (auto& body : m_bodies) {
            body->SetLinearVelocity(b2Vec2(0, 0));
            body->SetAngularVelocity(0);
        }
        return;
    }
    Ball::applyForces(threshold);
}
