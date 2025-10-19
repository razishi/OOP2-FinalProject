#include "Duck.h"
#include "Sounds.h"
#include <iostream>

Duck::Duck()
{
}

Duck::Duck(b2World* world, const sf::Vector2f& position)
    : m_isWaitAnimationPlaying(true), m_currentAnimationTime(0.0f) {
    // Load sprites from the sprite sheet
    m_emptyDuck.setTexture(Texture::getInstance().getTexture(TextureID::EmptyDuck));
    m_lessThanHalfDuck.setTexture(Texture::getInstance().getTexture(TextureID::LessThanHalfDuck));
    m_HalfDuck.setTexture(Texture::getInstance().getTexture(TextureID::MoreThanHalfDuck));
    m_FullDuck.setTexture(Texture::getInstance().getTexture(TextureID::FullyDuck));
    m_disapperDuck.setTexture(Texture::getInstance().getTexture(TextureID::DissapperDuck));

    m_emptyDuck.setOrigin(m_emptyDuck.getTexture()->getSize().x / 2.0f, m_emptyDuck.getTexture()->getSize().y / 2.0f);
    m_lessThanHalfDuck.setOrigin(m_lessThanHalfDuck.getTexture()->getSize().x / 2.0f, m_lessThanHalfDuck.getTexture()->getSize().y / 2.0f);
    m_HalfDuck.setOrigin(m_HalfDuck.getTexture()->getSize().x / 2.0f, m_HalfDuck.getTexture()->getSize().y / 2.0f);
    m_FullDuck.setOrigin(m_FullDuck.getTexture()->getSize().x / 2.0f, m_FullDuck.getTexture()->getSize().y / 2.0f);
    m_disapperDuck.setOrigin(m_disapperDuck.getTexture()->getSize().x / 2.0f, m_disapperDuck.getTexture()->getSize().y / 2.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(position.x / 100.0f, position.y / 100.0f);
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = CATEGORY_DUCK;
    fixtureDef.filter.maskBits = CATEGORY_BLUEBALL;  // Can collide with other objects and blue balls

    b2Fixture* fixture = m_body->CreateFixture(&fixtureDef);
    fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);  // Correctly set user data

    m_sprite.setPosition(position.x * 100.0f, position.y * 100.0f);
    m_sprite = m_emptyDuck;
    m_BlueBallsColided = 0; 
}

void Duck::update(float deltaTime, const std::vector<b2Body*>& blueBallBodies) {
    b2Vec2 position = m_body->GetPosition();
    m_sprite.setPosition(position.x * 100.0f, position.y * 100.0f);

    if (m_BlueBallsColided == 3) {
        m_sprite = m_lessThanHalfDuck;
        b2Vec2 position = m_body->GetPosition();
        m_sprite.setPosition(position.x * 100.0f, position.y * 100.0f);
        Sounds::getInstance().playSound(Songs::DUCK);

    }
    if (m_BlueBallsColided == 7) {
        m_sprite = m_HalfDuck;
        b2Vec2 position = m_body->GetPosition();
        m_sprite.setPosition(position.x * 100.0f, position.y * 100.0f);
        Sounds::getInstance().playSound(Songs::DUCK);
    }
    if (m_BlueBallsColided >= 11) {
        if (!m_startDisappearing) {
            Sounds::getInstance().playSound(Songs::REMOVEDUCK);
            m_sprite = m_FullDuck;
            b2Vec2 position = m_body->GetPosition();
            m_sprite.setPosition(position.x * 100.0f, position.y * 100.0f);
            m_startDisappearing = true;
            m_disappearingTimer = 0.0f; // Reset the timer
        }
        if (m_startDisappearing) {
            m_disappearingTimer += deltaTime;
            if (m_disappearingTimer >= 0.2f) {
                m_sprite = m_disapperDuck;
                m_sprite.setPosition(position.x * 100.0f, position.y * 100.0f);
            }
            if (m_disappearingTimer >= 2.0f) {
                m_shouldRemove = true; // Mark the duck for removal
            }
        }
    }
}



void Duck::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void Duck::show() {
    std::cout << "Duck shown." << std::endl;
}

std::unique_ptr<Object> Duck::createDuck(b2World* world, const sf::Vector2f& position) {
    return std::make_unique<Duck>(world, position);
}

bool Duck::shouldBeRemoved() const {
    return m_shouldRemove;
}


void Duck::increaseBlueBallCollisionCount() {
    m_BlueBallsColided++;
}

sf::FloatRect Duck::getBoundingBox() const {
    return m_sprite.getGlobalBounds();
}

sf::FloatRect Duck::getTopBoundingBox() const {
    sf::FloatRect boundingBox = m_sprite.getGlobalBounds();
    boundingBox.height *= 1.25f;  // Only consider the top 25% for collision
    boundingBox.width *= 1.25f;  // Only consider the top 25% for collision

    return boundingBox;
}


bool Duck::isLessThanHalfDuck() const {
   
    return m_BlueBallsColided >= 3 && m_BlueBallsColided < 7;
}

bool Duck::isHalfDuck() const {
    return m_BlueBallsColided >= 7 && m_BlueBallsColided < 11;
}

bool Duck::isFullyDuck() const {
    return m_BlueBallsColided > 11;
}

