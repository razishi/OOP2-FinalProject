#include "BrownBall.h"
#include "Sounds.h"

BrownBall::BrownBall(b2World* world) : m_world(world) {}


void BrownBall::create(float x, float y, const sf::CircleShape& shape) {
    float sfmlRadius = 8.f; // New SFML radius in pixels
    float box2dRadius = sfmlRadius / 100.f; // Convert to Box2D scale, assuming 100 pixels = 1 meter

    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(x / 100.0f, y / 100.0f);
    b2Body* body = m_world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = box2dRadius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 15.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = CATEGORY_BROWNBALL;
    fixtureDef.filter.maskBits = CATEGORY_BLUEBALL | CATEGORY_STONE | CATEGORY_PINKBALL | CATEGORY_OTHER;  // Exclude CATEGORY_DUCK

    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    m_bodies.push_back(body);

    sf::CircleShape newShape = shape;
    newShape.setRadius(sfmlRadius);
    newShape.setOrigin(sfmlRadius, sfmlRadius);
    newShape.setPosition(x, y);
    m_circles.push_back(newShape);
}


void BrownBall::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < m_circles.size(); ++i) {
        b2Vec2 position = m_bodies[i]->GetPosition();
        m_circles[i].setPosition(position.x * 100, position.y * 100);  // Convert Box2D position back to SFML
        window.draw(m_circles[i]);
    }
}


void BrownBall::remove(float mouseX, float mouseY) {

    std::vector<size_t> indicesToRemove;

    float removalRadius = 24.0f;
    sf::Vector2f mousePos(mouseX, mouseY);

    for (size_t i = 0; i < m_circles.size(); ++i) {
        sf::Vector2f ballPos = m_circles[i].getPosition();
        float distance = std::sqrt(std::pow(mousePos.x - ballPos.x, 2) + std::pow(mousePos.y - ballPos.y, 2));

        if (distance < removalRadius) {
            indicesToRemove.push_back(i);
        }

    }

    for (auto it = indicesToRemove.rbegin(); it != indicesToRemove.rend(); ++it) {
        Sounds::getInstance().playSound(Songs::REMOVE); 
        m_world->DestroyBody(m_bodies[*it]);
        m_bodies.erase(m_bodies.begin() + *it);
        m_circles.erase(m_circles.begin() + *it);

    }
}
