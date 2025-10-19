#pragma once

#include "Command.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class HelpCommand : public Command {
public:
    HelpCommand(sf::RenderWindow& window) : m_window(window) {}

    void execute() override {
        // Create a sprite to hold the help image
        sf::Texture helpTexture;
        if (!helpTexture.loadFromFile("help.jpeg")) {
            std::cerr << "Error loading help image" << std::endl;
            return;
        }
        sf::Sprite helpSprite(helpTexture);



        bool helpScreen = true;
        while (helpScreen) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    helpScreen = false;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    helpScreen = false;
                }

            }

            m_window.clear();
            m_window.draw(helpSprite);

            m_window.display();
        }
    }

private:
    sf::RenderWindow& m_window;
};
