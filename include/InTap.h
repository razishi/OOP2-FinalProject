#pragma once


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "BlueBall.h"


class InTap {
public:
    InTap(b2World* world, const sf::Vector2f& position, const sf::Image& image);
    ~InTap() {};
    void draw(sf::RenderWindow& window);
    void handleCollision(BlueBall* blueBall);
    sf::FloatRect getBoundingBox() const;

private:
    sf::RectangleShape m_shape;
    b2Body* m_body;
    int m_collisionCount;  // Counter to keep track of the number of collisions
    const sf::Image& m_image;  // Reference to the image used for finding new positions

};

