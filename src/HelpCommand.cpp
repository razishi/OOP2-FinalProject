//#include "HelpCommand.h"
//
//HelpCommand::HelpCommand(sf::RenderWindow& window) : m_window(window) {}
//
//void execute() override {
//    // Create a sprite to hold the help image
//    
//}
//
//
//HelpCommand::HelpCommand(sf::RenderWindow& window) : m_window(window)
//{
//sf::Texture helpTexture;
//if (!helpTexture.loadFromFile("help.jpeg")) {
//    std::cerr << "Error loading help image" << std::endl;
//    return;
//}
//sf::Sprite helpSprite(helpTexture);
//
//
//
//bool helpScreen = true;
//while (helpScreen) {
//    sf::Event event;
//    while (m_window.pollEvent(event)) {
//        if (event.type == sf::Event::Closed) {
//            helpScreen = false;
//        }
//        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
//            helpScreen = false;
//        }
//
//    }
//
//    m_window.clear();
//    m_window.draw(helpSprite);
//
//    m_window.display();
//}