#include "PlayCommand.h"
#include "iostream"

PlayCommand::PlayCommand(sf::RenderWindow& window) : m_window(window), m_selectedLevel(-1) {
    // Load font
    if (!m_font.loadFromFile("C:/Windows/Fonts/BRUSHSCI.ttf")) {
        std::cerr << "Error loading font: BRUSHSCI.ttf" << std::endl;
        return;
    }

    // Initialize texts 
    initTexts();
}

void PlayCommand::initTexts() {
    m_levelTexts.emplace_back("Level1", m_font, 60);
    m_levelTexts.emplace_back("Level2", m_font, 60);
    m_levelTexts.emplace_back("Level3", m_font, 60);

    for (auto& text : m_levelTexts) {
        text.setFillColor(sf::Color::White);
    }

    m_levelTexts[0].setPosition(430, 200);
    m_levelTexts[1].setPosition(430, 300);
    m_levelTexts[2].setPosition(430, 400);
}

void  PlayCommand::execute() {
    Sounds::getInstance().pauseSound(Songs::START);
    Sounds::getInstance().playSound(Songs::SELECTLEVEL);
    showLevelSelectScreen();
}


void  PlayCommand::showLevelSelectScreen() {
    sf::Texture selectLevelTexture;
    if (!selectLevelTexture.loadFromFile("selectlevel.jpg")) {
        std::cerr << "Error loading texture: selectlevel.jpg" << std::endl;
        return;
    }

    sf::Sprite selectLevelSprite(selectLevelTexture);

    // Scale the sprite to fit the window
    sf::Vector2u windowSize = m_window.getSize();
    sf::Vector2u textureSize = selectLevelTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    selectLevelSprite.setScale(scaleX, scaleY);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                handleMouseClick(sf::Vector2f(mousePos));

                // Check if a level text was clicked
                for (size_t i = 0; i < m_levelTexts.size(); ++i) {
                    if (m_levelTexts[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        m_selectedLevel = i;
                        m_window.close();
                        startLevel(i + 1); // Levels are 1-based
                        break;
                    }
                }
            }

            // Handle mouse move events for hover effect
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                handleMouseMove(sf::Vector2f(mousePos));
            }
        }

        m_window.clear();
        m_window.draw(selectLevelSprite);

        // Draw all level texts
        for (const auto& text : m_levelTexts) {
            m_window.draw(text);
        }

        m_window.display();
    }
}

void  PlayCommand::handleMouseClick(const sf::Vector2f& mousePosition) {
    // Reset all texts to white
    for (auto& text : m_levelTexts) {
        text.setFillColor(sf::Color::White);
    }

    // Check if a text was clicked and change its color to black
    for (auto& text : m_levelTexts) {
        if (text.getGlobalBounds().contains(mousePosition)) {
            text.setFillColor(sf::Color::Black);
            break; // Only one text can be clicked at a time
        }
    }
}


void  PlayCommand::handleMouseMove(const sf::Vector2f& mousePosition) {
    // Reset all texts to white
    for (auto& text : m_levelTexts) {
        text.setFillColor(sf::Color::White);
    }

    // Check if a text is hovered over and change its color to black
    for (auto& text : m_levelTexts) {
        if (text.getGlobalBounds().contains(mousePosition)) {
            text.setFillColor(sf::Color::Black);
            break; // Only one text can be hovered over at a time
        }
    }
}

void   PlayCommand::startLevel(int level) {
    Sounds::getInstance().pauseSound(Songs::SELECTLEVEL);
    Controller controller(m_window);
    controller.run();
    // Optionally, you can pass the level information to Controller for specific level setup
}