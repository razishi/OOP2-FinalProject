
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include <vector>

class BrownBall {
public:
    explicit BrownBall(b2World* world);
    void create(float x, float y, const sf::CircleShape& shape);  
    void draw(sf::RenderWindow& window);
    void remove(float mouseX, float mouseY);
    ~BrownBall() {};

private:
    std::vector<sf::CircleShape> m_circles;  
    std::vector<b2Body*> m_bodies;
    b2World* m_world;
};

#pragma once
