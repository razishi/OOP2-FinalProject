
#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Globals.h"

class Ball {
public:
    Ball(b2World* world);
    virtual ~Ball() = default;
    void dropFromTop(int count);
    virtual void create(float x, float y) = 0;
    void draw(sf::RenderWindow& window);
    virtual void applyForces(float threshold);

    const std::vector<b2Body*>& getBodies() const;
    sf::FloatRect getBoundingBox(size_t index) const;
    std::vector<sf::CircleShape>& getCircles();
    void dropFromPosition(float x, float y, int count);
protected:
    b2World* m_world;
    std::vector<b2Body*> m_bodies;
    std::vector<sf::CircleShape> m_circles;
    sf::Color m_ballColor;
};

