#include "Texture.h"
#include <iostream>

Texture& Texture::getInstance() {
    static Texture instance;
    return instance;
}

const sf::Texture& Texture::getTexture(TextureID textureID) {
    auto it = m_textures.find(textureID);
    if (it != m_textures.end()) {
        return it->second;
    }

    sf::Texture texture;
    std::string filename;

    switch (textureID) {
    case TextureID::Background:
        filename = "background.png";
        break;
    case TextureID::ButtonPlay:
        filename = "btnplay.png";
        break;
    case TextureID::ButtonHelp:
        filename = "btnhelp.png";
        break;
    case TextureID::Exit:
        filename = "btnexit.png";
        break;
    case TextureID::Crocodile:
        filename = "crocodile.png";
        break;
    case TextureID::SpiritSheet:
        filename = "SpiritSheet.png";
        break;
    case TextureID::Level1:
        filename = "level001.jpg";
        break;
    case TextureID::Level2:
        filename = "level002.jpeg";
        break;
    case TextureID::Level3:
        filename = "level003.jpg";
        break;
    case TextureID::Dirt:
        filename = "dirt1.jpeg";
        break;
    case TextureID::EmptyDuck:
        filename = "EmptyDuck.png";
        break;
    case TextureID::LessThanHalfDuck:
        filename = "LessThanHalfDuck.png";
        break;
    case TextureID::MoreThanHalfDuck:
        filename = "MoreThanHalfDuck.png";
        break;
    case TextureID::FullyDuck:
        filename = "FullyDuck.png";
        break;
    case TextureID::DissapperDuck:
        filename = "drop.png";
        break;
    case TextureID::ButtonPause:
        filename = "btnpause.png";
        break;
    case TextureID::ButtonRestart:
        filename = "btnrestart.png";
        break;
    case TextureID::SelectLevel:
        filename = "selectlevel.jpg";
        break;
    case TextureID::VideoSprite:
        filename = "videosprite.png";
        break;

    case TextureID::FULLDUCK:
        filename = "ducky_duck_water5.png";
        break;
    case TextureID::Win:
        filename = "crocwin.png";
        break;
    case TextureID::Light:
        filename = "lightlarge11.png";
        break;
    case TextureID::Super:
        filename = "super.png";
        break;
    case TextureID::GoodJob:
        filename = "goodjob.png";
        break;
    case TextureID::Excellent:
        filename = "excellent.png";
        break;
    case TextureID::NEXT:
        filename = "btnnextlevel.png";
        break;
    default:
        std::cerr << "Unhandled TextureID requested" << std::endl;
        break;
    }

    if (!texture.loadFromFile(filename)) { // load textures
        std::cerr << "Error loading texture: " << filename << std::endl;
    }

    m_textures[textureID] = texture;
    return m_textures[textureID];
}
