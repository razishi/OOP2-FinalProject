#include "Animation.h"

Animation::Animation() : m_imageCount(0, 0), m_currentImage(0, 0), m_totalTime(0.0f), m_switchTime(0.0f), m_row(0) {}

void Animation::loadVedio(TextureID textureID, sf::Vector2u imageCount, float switchTime, unsigned int row) {
    m_texture = Texture::getInstance().getTexture(textureID);

    m_imageCount = imageCount;
    m_switchTime = switchTime;
    m_row = row;
    m_currentImage.y = row;

    m_uvRect.width = m_texture.getSize().x / m_imageCount.x; // Correctly calculate width per frame
    m_uvRect.height = m_texture.getSize().y / m_imageCount.y; // Correctly calculate height per frame
}



void Animation::load(TextureID textureID, sf::Vector2u imageCount, float switchTime, unsigned int row, float heightScale, float WidthScale) {
    m_texture = Texture::getInstance().getTexture(textureID);

    m_imageCount = imageCount;
    m_switchTime = switchTime;
    m_row = row;
    m_currentImage.y = m_row;

    m_uvRect.width = m_texture.getSize().x / m_imageCount.x + WidthScale;
    m_uvRect.height = m_texture.getSize().y / m_imageCount.y * heightScale;
}

void Animation::VedioUpdate(float deltaTime) {
    m_totalTime += deltaTime;

    if (m_totalTime >= m_switchTime) {
        m_totalTime -= m_switchTime;
        m_currentImage.x++;

        if (m_currentImage.x >= m_imageCount.x) {
            m_currentImage.x = 0;
            m_currentImage.y++;

            if (m_currentImage.y >= m_imageCount.y) {
                m_currentImage.y = 0; // Optionally, stop repeating by handling a completion state here.
            }
        }

        m_uvRect.left = m_currentImage.x * m_uvRect.width;
        m_uvRect.top = m_currentImage.y * m_uvRect.height; 
    }
}


void Animation::update(float deltaTime) {
    m_totalTime += deltaTime;
    if (m_totalTime >= m_switchTime) {
        m_totalTime -= m_switchTime;
        m_currentImage.x++;
        if (m_currentImage.x >= m_imageCount.x) {
            m_currentImage.x = 0;
        }
    }
    m_uvRect.left = m_currentImage.x * m_uvRect.width;
    m_uvRect.top = m_row * m_uvRect.height;
}

void Animation::applyToSprite(sf::Sprite& sprite) {
    sprite.setTexture(m_texture);
    sprite.setTextureRect(m_uvRect);
}


void Animation::setTexture(sf::Sprite& sprite) {
    sprite.setTexture(m_texture);
    sprite.setTextureRect(m_uvRect);
    sprite.setOrigin(m_uvRect.width / 2.0f, m_uvRect.height / 2.0f);
}

void Animation::reset()
{
    m_currentImage.x = 0;
    m_currentImage.y = m_row;  //  to start at the same row each time
    m_totalTime = 0.0f;

}
