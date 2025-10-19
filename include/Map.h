#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include <vector>
#include "Globals.h"
#include "Helpers.h"
#include "Sounds.h"
#include "BlueBall.h"
#include "PinkBall.h"
#include "Crocodile.h"
#include "Duck.h"
#include "InTap.h"
#include "Animation.h"

class Map {
public:
    explicit Map(b2World* world);
    ~Map() {};
    void render(sf::RenderWindow& window);
    void update(float deltaTime);
    void handleMouseClick(float mouseX, float mouseY);
    sf::FloatRect getPauseButtonBounds() const;
    void renderTopDucks(sf::RenderWindow& window);
    void updateDuckPositions();
    void loadLevel(int level);
    void nextLevel();



private:
    void cleanupWorld();
    void createDucks();
    void checkCollisions();
    int m_currentLevel;
    bool m_transitionToNextLevel;
    sf::Clock m_levelTransitionClock;


    std::vector<std::unique_ptr<BlueBall>> m_blueBalls;
    std::vector<std::unique_ptr<PinkBall>> m_pinkBalls;
    std::vector<std::unique_ptr<BrownBall>> m_brownBalls;
    std::vector<std::unique_ptr<Duck>> m_Ducks;
    std::unique_ptr<Crocodile> m_crocodile;
    b2World* m_world;
    sf::Sprite m_backgroundSprite;
    sf::Image m_backgroundImage;
    sf::Image m_dirt;
    std::vector<b2Body*> m_blueBallBodies;
    std::vector<b2Body*> m_pinkBallBodies;
    std::vector<std::unique_ptr<InTap>> m_inTaps;
    sf::Sprite m_pauseButtonSprite;
    std::vector<sf::Vector2f> m_duckPositions;
    const sf::Texture* m_emptyDuckTexture;
    sf::Sprite  m_emptyDuckSprite;
    std::vector<sf::Sprite> m_duckSprites;
    std::vector<int> m_duckStates; 
};

#endif // MAP_H