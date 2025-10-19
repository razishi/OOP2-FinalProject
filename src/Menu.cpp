#include "Menu.h"
#include "Texture.h"
#include <iostream>

Menu::Menu(sf::RenderWindow& window, float width, float height)
    : m_window(window), m_MenuSelected(-1) {
    loadTextures();

    m_commands[0] = std::make_unique<PlayCommand>(window);
    m_commands[1] = std::make_unique<HelpCommand>(window);  // Pass window to HelpCommand
    m_commands[2] = std::make_unique<ExitCommand>();

    // Initialize the crocodile animation
    m_crocodileAnimation.load(TextureID::SpiritSheet, sf::Vector2u(16, 16), 0.1f, 0, 5, 0.65);
    float crocodileXPos = (width - m_crocodileAnimation.getTexture().getSize().x / 16) / 2 + 200;
    m_crocodileSprite.setPosition(crocodileXPos, height - 400);
    m_crocodileSprite.setScale(3.0f, 3.0f); // Scale up the sprite for better visibility

    // Calculate total height needed for all menu items
    float totalHeight = 0.0f;
    for (int i = 0; i < MAXMAINMENU; ++i) {
        totalHeight += m_menuSprites[i].getGlobalBounds().height;
    }

    // Initial y position to center the menu vertically
    float yPos = (height - totalHeight) / 2 + 100;

    // Set positions and scale for the menu items
    for (int i = 0; i < MAXMAINMENU; ++i) {
        // Set scale
        m_menuSprites[i].setScale(0.5f, 0.5f);

        float xPos = (width - m_menuSprites[i].getGlobalBounds().width) / 2;

        // Set position
        m_menuSprites[i].setPosition(xPos, yPos);

        // Update yPos for the next button
        yPos += m_menuSprites[i].getGlobalBounds().height + 50.0f;  // Add spacing of 60 pixels
    }
}

Menu::~Menu() {
    // Destructor
}

void Menu::loadTextures() {
    m_menuSprites[0].setTexture(Texture::getInstance().getTexture(TextureID::ButtonPlay));
    m_menuSprites[1].setTexture(Texture::getInstance().getTexture(TextureID::ButtonHelp));
    m_menuSprites[2].setTexture(Texture::getInstance().getTexture(TextureID::Exit));
}

void Menu::draw(sf::RenderWindow& window) const {
    for (int i = 0; i < MAXMAINMENU; ++i) {
        window.draw(m_menuSprites[i]);
    }

    // Draw the crocodile animation
    window.draw(m_crocodileSprite);
}

void Menu::update(sf::Vector2f mousePos) {
    m_MenuSelected = -1;
    for (int i = 0; i < MAXMAINMENU; i++) {
        if (m_menuSprites[i].getGlobalBounds().contains(mousePos)) {
            m_menuSprites[i].setColor(sf::Color::Blue); // Highlight on hover
            m_MenuSelected = i;
        }
        else {
            m_menuSprites[i].setColor(sf::Color::White); // Normal color
        }
    }

    // Update the crocodile animation
    static sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();
    m_crocodileAnimation.update(deltaTime);
    m_crocodileAnimation.applyToSprite(m_crocodileSprite);
}

int Menu::MenuPressed() const {
    return m_MenuSelected;
}

void Menu::executeCommand(int index) {
    if (index >= 0 && index < MAXMAINMENU) {
        m_commands[index]->execute();
    }
}


