#include "Play.h"
#include "Texture.h"

Play::Play() : m_window(sf::VideoMode(1000, 1000), "Where is my water", sf::Style::Close | sf::Style::Titlebar),
m_menu(m_window, m_window.getSize().x, m_window.getSize().y) {
    CreatMenu();
}

void Play::CreatMenu() {
    Sounds::getInstance().playSound(Songs::START);
    sf::RectangleShape Pbackground;
    Pbackground.setSize(sf::Vector2f(1000, 1000));
    Pbackground.setTexture(&Texture::getInstance().getTexture(TextureID::Background));

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                int selectedMenu = m_menu.MenuPressed();
                if (selectedMenu != -1) {
                    m_menu.executeCommand(selectedMenu);
                }
            }
        }

        // Update mouse position for menu highlight
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
        m_menu.update(mousePos);

        // Draw menu and background
        m_window.clear();
        m_window.draw(Pbackground);
        m_menu.draw(m_window);
        m_window.display();
    }
}
