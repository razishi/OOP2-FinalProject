#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Map.h"
#include "Animation.h"
#include "Sounds.h"
#include "MyContactListener.h"

class Controller {
public:
    Controller(sf::RenderWindow& window);
    void run();
    void handlePauseButtonClick();
    void resetGame();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow& m_gameWindow; 

    std::unique_ptr<b2World> m_world;
    std::unique_ptr<Map> m_map;
    sf::Clock m_clock;

    Animation m_crankyWaitAnimation;
    Animation m_crankyHaveAnimation;

    bool m_isCrankyWaitAnimationPlaying;
    float m_currentAnimationTime;
    std::unique_ptr<MyContactListener> m_myContactListener;

    bool m_isPaused;
    bool m_videoFinished;
    float m_videoDuration;
    float m_videoElapsedTime;

    void startVideo();
};

#endif // CONTROLLER_H
