#include "Command.h"
#include "Controller.h"
#include "Sounds.h"
#include "Texture.h"

class PlayCommand : public Command {
public:
    PlayCommand(sf::RenderWindow& window);
    void execute() override;

private:

    void initTexts();
    void showLevelSelectScreen();
    void handleMouseClick(const sf::Vector2f& mousePosition);
    void handleMouseMove(const sf::Vector2f& mousePosition);

    void startLevel(int level);
    sf::RenderWindow& m_window;
    sf::Font m_font;
    std::vector<sf::Text> m_levelTexts;
    int m_selectedLevel;
};
