
#pragma once

#include <SFML/Graphics.hpp>
#include "Texture.h" 
class Animation {
public:
    Animation();
    ~Animation() {};
    void loadVedio(TextureID textureID, sf::Vector2u imageCount, float switchTime, unsigned int row);
    void load(TextureID textureID, sf::Vector2u imageCount, float switchTime, unsigned int row, float heightScale = 1.0f, float WidthScale = 1.0f);
    void VedioUpdate(float deltaTime);
    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite);
    const sf::Texture& getTexture() const { return m_texture; }
    void setTexture(sf::Sprite& sprite);
    void reset();
private:
    sf::Texture m_texture;
    sf::Vector2u m_imageCount;
    sf::Vector2u m_currentImage;
    float m_totalTime;
    float m_switchTime;
    unsigned int m_row;
    sf::IntRect m_uvRect;
};
