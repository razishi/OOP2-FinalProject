#ifndef CROCODILE_H
#define CROCODILE_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include "Animation.h"
#include "Object.h"  
#include "Texture.h"

class Crocodile : public Object {
public:
    Crocodile();
    ~Crocodile() {};
    Crocodile(b2World* world, const sf::Vector2f& position);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    std::unique_ptr<Object> createCrocodile(b2World* world, const sf::Vector2f& position);

    void show() override;

private:
    sf::Sprite m_sprite;
    b2Body* m_body;

    Animation m_waitAnimation;
    Animation m_haveAnimation;

    bool m_isWaitAnimationPlaying;
    float m_currentAnimationTime;
    static bool m_registerif;
    void switchAnimationIfNeeded(float deltaTime);
};

#endif // CROCODILE_H