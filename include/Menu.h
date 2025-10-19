#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <array>
#include "Command.h"
#include "Globals.h"
#include <iostream>
#include "PlayCommand.h"
#include "HelpCommand.h"
#include "ExitCommand.h"

#include "Animation.h"


class Menu {
public:
    Menu(sf::RenderWindow& window, float width, float height);   
    ~Menu();

    void draw(sf::RenderWindow& window) const;
    void update(sf::Vector2f mousePos);
    int MenuPressed() const;
    void executeCommand(int index);

private:
    void loadTextures();

    sf::Texture m_textures[MAXMAINMENU];
    sf::Sprite m_menuSprites[MAXMAINMENU];
    std::unique_ptr<Command> m_commands[MAXMAINMENU];
    int m_MenuSelected;
    sf::RenderWindow& m_window;

    mutable Animation m_crocodileAnimation;
    mutable sf::Sprite m_crocodileSprite;
};

