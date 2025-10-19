#include "InTap.h"
#include "Helpers.h"


InTap::InTap(b2World* world, const sf::Vector2f& position, const sf::Image& image)
    : m_collisionCount(0), m_image(image) {
    m_shape.setSize(sf::Vector2f(50, 50));
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(position);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(position.x / 100.0f, position.y / 100.0f);
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(0.25f, 0.25f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    // Exclude PinkBall and BlueBall
    fixtureDef.filter.categoryBits = CATEGORY_TAP;
    fixtureDef.filter.maskBits = 0;

    m_body->CreateFixture(&fixtureDef);
}


void InTap::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}




void InTap::handleCollision(BlueBall* blueBall) {
    if (m_collisionCount < 10) {
        // Assuming findOutTapPosition returns a vector of positions and we take the first one
        sf::Vector2f newPosition = findOutTapPosition(m_image)[0];

        for (auto& body : blueBall->getBodies()) {
            // Convert SFML coordinates to Box2D coordinates (assuming a scale factor of 100)
            b2Vec2 position(newPosition.x / 100.0f, newPosition.y / 100.0f);
            body->SetTransform(position, body->GetAngle());
        }

        m_collisionCount++;
    }
}


sf::FloatRect InTap::getBoundingBox() const {
    return m_shape.getGlobalBounds();
}
