#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include "Animation.h"
#include "Object.h"
#include "Texture.h"
#include "Globals.h"

class Duck : public Object {
public:
    Duck();
    ~Duck() {};
    Duck(b2World* world, const sf::Vector2f& position);

    void update(float deltaTime, const std::vector<b2Body*>& blueBallBodies);
    void render(sf::RenderWindow& window);
    std::unique_ptr<Object> createDuck(b2World* world, const sf::Vector2f& position);
    bool isLessThanHalfDuck() const;
    bool isHalfDuck() const;
    bool isFullyDuck() const;
    void show() override;
    void increaseBlueBallCollisionCount();
    bool shouldBeRemoved() const;
    sf::FloatRect getBoundingBox() const;  // Existing method
    sf::FloatRect getTopBoundingBox() const;  // Add this method
    sf::Vector2f getPosition() const {
        return m_sprite.getPosition();
    }

    bool isVisible = true;  // Control visibility instead of removing from vectors

private:
    sf::Sprite m_sprite;
    b2Body* m_body;

    sf::Sprite m_emptyDuck;
    sf::Sprite m_lessThanHalfDuck;
    sf::Sprite m_HalfDuck;
    sf::Sprite m_FullDuck;
    sf::Sprite m_disapperDuck;

    bool m_isWaitAnimationPlaying;
    float m_currentAnimationTime;
    static bool m_registerif;

    int m_BlueBallsColided = 0;
    bool m_startDisappearing = false;
    float m_disappearingTimer = 0.0f;
    bool m_shouldRemove = false;

  
};

