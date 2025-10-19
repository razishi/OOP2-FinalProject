#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Controller.h"
#include "Sounds.h"

#include <SFML/Audio.hpp>



class Play {
public:
    Play();
    void CreatMenu();

private:
    sf::RenderWindow m_window;
    Menu m_menu;
    sf::Music m_menuMusic;  
};


