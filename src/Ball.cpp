#include "Ball.h"
#include "Sounds.h"

Ball::Ball(b2World* world) : m_world(world) {}

void Ball::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < m_circles.size(); ++i) {
        b2Vec2 position = m_bodies[i]->GetPosition();
        m_circles[i].setPosition(position.x * 100, position.y * 100);
        window.draw(m_circles[i]);
    }
}

void Ball::applyForces(float threshold) {
    float repulsionFactor = 0.0001f;
    float cohesionFactor = 0.01f;
    float viscosity = 10.0f;

    for (size_t i = 0; i < m_bodies.size(); ++i) {
        b2Vec2 gravityEffect(0, 1.0f);
        m_bodies[i]->ApplyForceToCenter(gravityEffect, true);

        m_bodies[i]->SetLinearDamping(viscosity);

        b2Vec2 posA = m_bodies[i]->GetPosition();
        for (size_t j = 0; j < m_bodies.size(); ++j) {
            b2Vec2 posB = m_bodies[j]->GetPosition();
            b2Vec2 direction = posB - posA;
            float distance = direction.Length();

            if (distance < threshold) {
                float forceMagnitude;
                if (distance < threshold * 0.5) {
                    forceMagnitude = -repulsionFactor * (threshold - distance);
                }
                else {
                    forceMagnitude = cohesionFactor * (threshold - distance);
                }
                b2Vec2 force = forceMagnitude * direction;
                m_bodies[i]->ApplyForceToCenter(force, true);
            }
        }
    }
}

void Ball::dropFromPosition(float x, float y, int count) {
    for (int i = 0; i < count; ++i) {
        create(x, y);
    }
}


const std::vector<b2Body*>& Ball::getBodies() const {
    return m_bodies;
}

sf::FloatRect Ball::getBoundingBox(size_t index) const {
    if (index >= m_circles.size()) {
        return sf::FloatRect();
    }
    return m_circles[index].getGlobalBounds();
}


std::vector<sf::CircleShape>& Ball::getCircles() {
    return m_circles;
}



void Ball::dropFromTop(int count) {
    for (int i = 0; i < count; ++i) {
        float x = std::rand() % 1000;
        float y = 4;
        create(x, y);
    }
}
