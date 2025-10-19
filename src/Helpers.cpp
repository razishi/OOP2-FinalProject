#include "Helpers.h"
#include <iostream>

void createStoneBoundariesFromImage(const sf::Image& image, b2World* world) {
    auto isColorInRange = [](const sf::Color& color) {
        return (color.r >= 120 && color.r <= 125) &&
            (color.g >= 100 && color.g <= 110) &&
            (color.b >= 120 && color.b <= 150);
        };

    int width = image.getSize().x;
    int height = image.getSize().y;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (isColorInRange(image.getPixel(x, y))) {
                b2BodyDef bodyDef;
                bodyDef.type = b2_staticBody;
                bodyDef.position.Set(x / 100.0f, y / 100.0f);
                b2Body* body = world->CreateBody(&bodyDef);

                b2PolygonShape box;
                box.SetAsBox(0.1f, 0.1f); // Small box to approximate pixel

                b2FixtureDef fixtureDef;
                fixtureDef.shape = &box;
                fixtureDef.density = 5.0f;
                fixtureDef.friction = 0.3f;
                fixtureDef.filter.categoryBits = CATEGORY_STONE;
                fixtureDef.filter.maskBits = CATEGORY_BLUEBALL | CATEGORY_PINKBALL | CATEGORY_BROWNBALL | CATEGORY_OTHER;

                body->CreateFixture(&fixtureDef);
            }
        }
    }
}

sf::Vector2f findCrocodilePosition(const sf::Image& image) {
    auto isColorInRange = [](const sf::Color& color) {
        return (color.r >= 18 && color.r <= 25) &&
            (color.g >= 18 && color.g <= 25) &&
            (color.b >= 18 && color.b <= 25);
        };    int width = image.getSize().x;
        int height = image.getSize().y;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (isColorInRange(image.getPixel(x, y))) {

                    return sf::Vector2f(x, y);
                }
            }
        }

        return sf::Vector2f(-1, -1); // Return an invalid position if the color is not found
}







std::vector<sf::Vector2f>  findInTapPosition(const sf::Image& image) {

    auto isColorInRange = [](const sf::Color& color) {
        return (color.r >= 145 && color.r <= 155) &&
            (color.g >= 145 && color.g <= 155) &&
            (color.b >= 145 && color.b <= 155);
        };

    int width = image.getSize().x;
    int height = image.getSize().y;

    std::vector<sf::Vector2f> positions;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (isColorInRange(image.getPixel(x, y))) {

                positions.push_back(sf::Vector2f(x, y));
            }
        }
    }

    return positions; // Return an invalid position if the color is not found
}

std::vector<sf::Vector2f>  findOutTapPosition(const sf::Image& image) {
    auto isColorInRange = [](const sf::Color& color) {
        return (color.r >= 178 && color.r <= 182) &&
            (color.g >= 178 && color.g <= 182) &&
            (color.b >= 178 && color.b <= 182);
        };

    int width = image.getSize().x;
    int height = image.getSize().y;
    std::vector<sf::Vector2f> positions;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (isColorInRange(image.getPixel(x, y))) {

                positions.push_back(sf::Vector2f(x, y));
            }
        }
    }

    return positions; // Return an invalid position if the color is not found
}



std::vector<sf::Vector2f>  findDuckPosition(const sf::Image& image) {
    auto isColorInRange = [](const sf::Color& color) {
        return (color.r >= 105 && color.r <= 110) &&
            (color.g >= 105 && color.g <= 110) &&
            (color.b >= 105 && color.b <= 110);
        };


    int width = image.getSize().x;
    int height = image.getSize().y;
    std::vector<sf::Vector2f> positions;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (isColorInRange(image.getPixel(x, y))) {

                positions.push_back(sf::Vector2f(x, y));
            }
        }
    }

    return positions; // Return an invalid position if the color is not found
}

bool isBrown(const sf::Color& color) {
    return (color.r > 95 && color.r < 110) &&  // Red component
        (color.g > 45 && color.g < 60) &&   // Green component
        (color.b > 25 && color.b < 60);     // Blue component
}

void processImageForBalls(const sf::Image& image, b2World* world, std::vector<std::unique_ptr<BrownBall>>& brownBalls, const std::vector<sf::CircleShape>& shapes) {
    int width = image.getSize().x;
    int height = image.getSize().y;
    std::vector<sf::Vector2f> brownPositions;

    // Step size to check every 5th pixel
    const int stepSize = 5;

    for (int y = 0; y < height; y += stepSize) {
        for (int x = 0; x < width; x += stepSize) {
            sf::Color color = image.getPixel(x, y);
            if (isBrown(color)) {
                brownPositions.emplace_back(x, y);
            }
        }
    }

    if (!brownPositions.empty()) {
        int shapeIndex = 0;
        for (const auto& pos : brownPositions) {
            auto brownBall = std::make_unique<BrownBall>(world);
            brownBall->create(pos.x, pos.y, shapes[shapeIndex]);
            brownBalls.push_back(std::move(brownBall));

            shapeIndex = (shapeIndex + 1) % shapes.size(); // Cycle through shapes
        }



    }
}



std::vector<sf::CircleShape> createShapesFromImage(const sf::Image& image) {
    int width = image.getSize().x;
    int height = image.getSize().y;
    std::vector<sf::CircleShape> shapes;

    const int stepSize = 5;

    for (int y = 0; y < height; y += stepSize) {
        for (int x = 0; x < width; x += stepSize) {
            sf::Color color = image.getPixel(x, y);
            sf::CircleShape shape(2.5f); // Circle with a radius of 2.5
            shape.setPosition(static_cast<float>(x), static_cast<float>(y));
            shape.setFillColor(color);
            shapes.push_back(shape);
        }
    }

    return shapes;
}