#ifndef HELPERS_H
#define HELPERS_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include "BrownBall.h"
#include "Globals.h"

void createStoneBoundariesFromImage(const sf::Image& image, b2World* world);
sf::Vector2f findCrocodilePosition(const sf::Image& image);
std::vector<sf::Vector2f>  findDuckPosition(const sf::Image& image);
std::vector<sf::Vector2f>  findInTapPosition(const sf::Image& image);
std::vector<sf::Vector2f>  findOutTapPosition(const sf::Image& image);
void processImageForBalls(const sf::Image& image, b2World* world, std::vector<std::unique_ptr<BrownBall>>& brownBalls, const std::vector<sf::CircleShape>& shapes);
std::vector<sf::CircleShape> createShapesFromImage(const sf::Image& image); 

#endif // HELPERS_H
