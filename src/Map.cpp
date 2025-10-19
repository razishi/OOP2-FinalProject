#include "Map.h"
#include "Texture.h"
#include <iostream>

Map::Map(b2World* world) : m_world(world), m_currentLevel(1), m_transitionToNextLevel(false) {
    loadLevel(m_currentLevel);
}


void Map::loadLevel(int level) {
    m_currentLevel = level;
    Sounds::getInstance().pauseSound(Songs::GAMEWIN);
    Sounds::getInstance().playSound(Songs::GAMEPLAY);
    cleanupWorld();


    if (level == 2) { 
        auto blueBall = std::make_unique<BlueBall>(m_world);
        blueBall->getSmaller();
        blueBall->dropFromTop(150);
        m_blueBalls.push_back(std::move(blueBall));
        m_backgroundSprite.setTexture(Texture::getInstance().getTexture(TextureID::Level2));
        m_backgroundImage.loadFromFile("level2.jpeg");
        m_dirt.loadFromFile("dirt1.jpeg");
    }
    else if (level == 3) {
        auto blueBall = std::make_unique<BlueBall>(m_world);
        blueBall->dropFromPosition(224, 331, 80);
        m_blueBalls.push_back(std::move(blueBall));
        auto pinkBall = std::make_unique<PinkBall>(m_world);
        pinkBall->dropFromPosition(854, 323, 80);
        m_pinkBalls.push_back(std::move(pinkBall));
        m_backgroundSprite.setTexture(Texture::getInstance().getTexture(TextureID::Level3));
        m_backgroundImage.loadFromFile("level3.jpeg");
        m_dirt.loadFromFile("dirt1.jpg");
    }
    else {
        auto blueBall = std::make_unique<BlueBall>(m_world);
        blueBall->dropFromTop(50);
        m_blueBalls.push_back(std::move(blueBall));
        m_backgroundSprite.setTexture(Texture::getInstance().getTexture(TextureID::Level1));
        m_backgroundImage.loadFromFile("level1.jpg");
        m_dirt.loadFromFile("dirt1.jpeg");

    }

    std::vector<sf::CircleShape> shapes = createShapesFromImage(m_dirt);
    processImageForBalls(m_backgroundImage, m_world, m_brownBalls, shapes);
    createStoneBoundariesFromImage(m_backgroundImage, m_world);

    m_crocodile = std::make_unique<Crocodile>(m_world, findCrocodilePosition(m_backgroundImage));

    auto inTapPositions = findInTapPosition(m_backgroundImage);
    for (const auto& position : inTapPositions) {
        auto inTap = std::make_unique<InTap>(m_world, position, m_backgroundImage);
        m_inTaps.push_back(std::move(inTap));
    }

    createDucks();

    // Initialize the button sprites
    m_pauseButtonSprite.setTexture(Texture::getInstance().getTexture(TextureID::ButtonPause));

    // Position the button sprites
    m_pauseButtonSprite.setScale(0.8f, 0.8f);

    float xPosition = 1000.0f - m_pauseButtonSprite.getGlobalBounds().width - 20.0f; // Right side with 10 pixels padding
    m_pauseButtonSprite.setPosition(xPosition, 10.0f);
    m_emptyDuckTexture = &Texture::getInstance().getTexture(TextureID::EmptyDuck);

    float startX = 50.0f;  // Adjust as needed
    float startY = 10.0f;  // Adjust as needed
    float spacingX = m_emptyDuckTexture->getSize().x * 0.9f;  // Adjust spacing between ducks

    // Create positions for the ducks
    m_duckPositions.push_back(sf::Vector2f(startX, startY));
    m_duckPositions.push_back(sf::Vector2f(startX + spacingX, startY));
    m_duckPositions.push_back(sf::Vector2f(startX + 2 * spacingX, startY));

    // Initialize duck sprites and state vector
    for (const auto& position : m_duckPositions) {
        sf::Sprite duckSprite;
        duckSprite.setTexture(*m_emptyDuckTexture);
        duckSprite.setPosition(position);
        m_duckSprites.push_back(duckSprite);
        m_duckStates.push_back(0); // Initialize all to 0 (EMPTYDUCK)


    }
}


void Map::nextLevel() {
    m_transitionToNextLevel = false;
    m_currentLevel++;
    loadLevel(m_currentLevel);
}

void Map::cleanupWorld() {
    // Destroy all Box2D bodies safely
    b2Body* body = m_world->GetBodyList();
    while (body != nullptr) {
        b2Body* nextBody = body->GetNext();
        m_world->DestroyBody(body);
        body = nextBody;
    }

    // Clear the vectors
    m_blueBalls.clear();
    m_pinkBalls.clear();
    m_brownBalls.clear();
    m_Ducks.clear();
    m_inTaps.clear();
    m_blueBallBodies.clear();
    m_pinkBallBodies.clear();
    m_duckSprites.clear();
    m_duckStates.clear();
    m_duckPositions.clear();
}


void Map::createDucks() {
    std::vector<sf::Vector2f> duckPositions = findDuckPosition(m_backgroundImage);
    for (const auto& position : duckPositions) {
        auto duck = std::make_unique<Duck>(m_world, position);
        m_Ducks.push_back(std::move(duck));
    }
}

void Map::render(sf::RenderWindow& window) {
    window.draw(m_backgroundSprite);
    for (auto& ball : m_blueBalls) {
        ball->draw(window);
    }
      for (auto& ball : m_pinkBalls) {
          ball->draw(window);
      }
    for (auto& ball : m_brownBalls) {
        ball->draw(window);
    }
    m_crocodile->render(window);

    for (auto& duck : m_Ducks) {
        if (duck->isVisible)
        {
            duck->render(window);
        }
    }

    renderTopDucks(window);
    window.draw(m_pauseButtonSprite);
}

void Map::update(float deltaTime) {
    // Update blue balls and pink balls
    for (auto& ball : m_blueBalls) {
        ball->applyForces(5);
    }
    for (auto& ball : m_pinkBalls) {
        ball->applyForces(5);
    }

    // Update crocodile
    m_crocodile->update(deltaTime);

    // Update ducks and collect blue ball bodies
    std::vector<b2Body*> blueBallBodies;
    for (const auto& blueBall : m_blueBalls) {
        for (const auto& body : blueBall->getBodies()) {
            blueBallBodies.push_back(body);
        }
    }



    for (auto& duck : m_Ducks) {
        duck->update(deltaTime, blueBallBodies);  // Update each duck

        if (duck->shouldBeRemoved()) {
            duck->isVisible = false;  // Set the visibility to false instead of removing
        }
    }

    updateDuckPositions();

    checkCollisions();
    if (m_transitionToNextLevel && m_levelTransitionClock.getElapsedTime().asSeconds() >= 2.0f) {
        nextLevel();
    }
}

void Map::handleMouseClick(float mouseX, float mouseY) {
    for (auto& ball : m_brownBalls) {
        ball->remove(mouseX, mouseY);
    }
}

void Map::checkCollisions() {


    for (auto& blueBall : m_blueBalls) {
        for (size_t i = 0; i < blueBall->getBodies().size(); ++i) {
            for (auto& duck : m_Ducks) {
                if ((duck->getTopBoundingBox()).intersects(blueBall->getBoundingBox(i))) {
                    duck->increaseBlueBallCollisionCount();
                }
            }
        }
    }

    for (auto& inTap : m_inTaps) {
        for (auto& blueBall : m_blueBalls) {
            for (size_t i = 0; i < blueBall->getBodies().size(); ++i) {
                if (inTap->getBoundingBox().intersects(blueBall->getBoundingBox(i))) {
                    inTap->handleCollision(blueBall.get());
                    m_transitionToNextLevel = true;
                    m_levelTransitionClock.restart();
                    Sounds::getInstance().playSound(Songs::GAMEWIN);
                    Sounds::getInstance().pauseSound(Songs::GAMEPLAY);

                }
            }
        }
    }

        for (auto& blueBall : m_blueBalls) {
        for (size_t i = 0; i < blueBall->getBodies().size(); ++i) {
            for (auto& pinkBall : m_pinkBalls) {
                for (size_t j = 0; j < pinkBall->getBodies().size(); ++j) {
                    if (blueBall->getBoundingBox(i).intersects(pinkBall->getBoundingBox(j))) {
                        for (auto& circle : blueBall->getCircles()) {
                            circle.setFillColor(sf::Color(255, 192, 203, 128)); // Light pink color
                        }
                    }
                }
            }
        }
    }
}

sf::FloatRect Map::getPauseButtonBounds() const {
    return m_pauseButtonSprite.getGlobalBounds();
}




void Map::updateDuckPositions() {
    for (size_t i = 0; i < m_duckSprites.size(); ++i) {

        if (i >= m_Ducks.size()) break;  // Ensure we don't access out of bounds

        auto& duck = m_Ducks[i];
        auto& duckSprite = m_duckSprites[i];
        int currentState = m_duckStates[i];


        if (currentState != 3) {
            if (duck->isFullyDuck() && currentState != 3) {
                duckSprite.setTexture(Texture::getInstance().getTexture(TextureID::FULLDUCK));
                m_duckStates[i] = 3;
            }
            else if (duck->isHalfDuck() && currentState != 2) {
                duckSprite.setTexture(Texture::getInstance().getTexture(TextureID::MoreThanHalfDuck));
                m_duckStates[i] = 2;
            }
            else if (duck->isLessThanHalfDuck() && currentState != 1) {
                duckSprite.setTexture(Texture::getInstance().getTexture(TextureID::LessThanHalfDuck));
                m_duckStates[i] = 1;
            }
        }
    }
}




void Map::renderTopDucks(sf::RenderWindow& window) {
    for (auto& duckSprite : m_duckSprites) {
        window.draw(duckSprite);
    }
}