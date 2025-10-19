#include "Crocodile.h"
#include <iostream>

Crocodile::Crocodile()
{
}

Crocodile::Crocodile(b2World* world, const sf::Vector2f& position)
    : m_isWaitAnimationPlaying(true), m_currentAnimationTime(0.0f) {


    m_waitAnimation.load(TextureID::SpiritSheet, sf::Vector2u(16, 16), 0.1f, 0, 5, 0.65);
    m_haveAnimation.load(TextureID::SpiritSheet, sf::Vector2u(16, 16), 0.1f, 1, 5, 1);

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

    m_body->CreateFixture(&fixtureDef);

    m_sprite.setPosition(position);
}

void Crocodile::update(float deltaTime) {
    switchAnimationIfNeeded(deltaTime);
    if (m_isWaitAnimationPlaying) {
        m_waitAnimation.update(deltaTime);
        m_waitAnimation.setTexture(m_sprite);
    }
    else {
        m_haveAnimation.update(deltaTime);
        m_haveAnimation.setTexture(m_sprite);
    }

    b2Vec2 position = m_body->GetPosition();
    m_sprite.setPosition(position.x * 100.0f, position.y * 100.0f);
}

void Crocodile::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void Crocodile::show()
{
    std::cout << "Crocodile shown." << std::endl;
}

std::unique_ptr<Object> Crocodile::createCrocodile(b2World* world, const sf::Vector2f& position) {
    return std::make_unique<Crocodile>(world, position);
}


void Crocodile::switchAnimationIfNeeded(float deltaTime) {
    m_currentAnimationTime += deltaTime;
    if (m_currentAnimationTime >= 15.0f) {
        m_currentAnimationTime = 0.0f;
        m_isWaitAnimationPlaying = !m_isWaitAnimationPlaying;
    }
}

