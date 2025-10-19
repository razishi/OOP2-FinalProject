#include "Controller.h"

Controller::Controller(sf::RenderWindow& window) : m_gameWindow(window), m_isCrankyWaitAnimationPlaying(true),
m_currentAnimationTime(0.0f), m_videoFinished(false), m_videoDuration(11.0f),
m_videoElapsedTime(0.0f), m_isPaused(false) {
    Sounds::getInstance().playSound(Songs::GAMEPLAY);
    m_gameWindow.create(sf::VideoMode(1000, 1000), "Where's My Water?");
    startVideo();
    resetGame();
}

void Controller::resetGame() {
    m_isPaused = false;

    // Reset the world
    m_world = std::make_unique<b2World>(b2Vec2(0.0f, -0.01f));
    m_myContactListener = std::make_unique<MyContactListener>();
    m_world->SetContactListener(m_myContactListener.get());

    // Reset the map
    m_map = std::make_unique<Map>(m_world.get());
}

void Controller::run() {
    while (m_gameWindow.isOpen()) {
        sf::Time deltaTime = m_clock.restart();
        processEvents();
        update(deltaTime.asSeconds());
        render();
    }
}

void Controller::processEvents() {
    sf::Event event;
    while (m_gameWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_gameWindow.close();
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_gameWindow);

            if (m_map->getPauseButtonBounds().contains(mousePos.x, mousePos.y)) {
                handlePauseButtonClick();
            }
           
            else {
                m_map->handleMouseClick(mousePos.x, mousePos.y);
            }
        }
        // Check for Enter key press to resume game
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            if (m_isPaused) {
                m_isPaused = false;
            }
        }
    }

    // Check for continuous left mouse button press
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gameWindow);
        m_map->handleMouseClick(mousePos.x, mousePos.y);
    }
}


void Controller::update(float deltaTime) {
    if (!m_videoFinished) {
        m_videoElapsedTime += deltaTime;
        m_crankyWaitAnimation.VedioUpdate(deltaTime); // Update the animation
        if (m_videoElapsedTime >= m_videoDuration) {
            m_videoFinished = true; // Ensures the video plays for the full duration
        }
    }
    else if (!m_isPaused) {
        m_world->Step(1.0f / 60.0f, 6, 2); // Physics simulation
        m_map->update(deltaTime); // Updates the map if the video has finished
    }
}

void Controller::render() {
    m_gameWindow.clear();

    if (!m_videoFinished) {
        sf::Sprite backgroundSprite;
        m_crankyWaitAnimation.VedioUpdate(m_clock.restart().asSeconds()); // Update animation with the elapsed time
        m_crankyWaitAnimation.applyToSprite(backgroundSprite);
        backgroundSprite.setScale(
            m_gameWindow.getSize().x / backgroundSprite.getLocalBounds().width,
            m_gameWindow.getSize().y / backgroundSprite.getLocalBounds().height); // Optional scaling
        m_gameWindow.draw(backgroundSprite);
    }
    else {
        m_map->render(m_gameWindow);
    }

    m_gameWindow.display();
}

void Controller::startVideo() {
    m_crankyWaitAnimation.reset(); // Reset the animation to initial frame
    m_crankyWaitAnimation.loadVedio(TextureID::VideoSprite, sf::Vector2u(25, 5), 0.2f, 0);
    m_videoElapsedTime = 0.0f; // Reset the elapsed time
    m_videoFinished = false; // Reset the video finished flag
}

void Controller::handlePauseButtonClick() {
    m_isPaused = !m_isPaused;
}

