#include "BlueBall.h"

BlueBall::BlueBall(b2World* world) : Ball(world) {
    m_ballColor = sf::Color(173, 216, 230, 128); // Light blue color
}

void BlueBall::create(float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / 100.0f, y / 100.0f);
    b2Body* body = m_world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 0.09f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 0.8f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.6f;
    fixtureDef.filter.categoryBits = CATEGORY_BLUEBALL;
    fixtureDef.filter.maskBits = CATEGORY_BLUEBALL | CATEGORY_BROWNBALL | CATEGORY_STONE | CATEGORY_OTHER;

    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    m_bodies.push_back(body);

    sf::CircleShape circle(10.f);
    circle.setOrigin(10.f, 10.f);
    circle.setFillColor(m_ballColor);
    circle.setPosition(x, y);
    m_circles.push_back(circle);
}

void BlueBall::getSmaller() {
    m_circleShape.m_radius = 0.6f;
}

