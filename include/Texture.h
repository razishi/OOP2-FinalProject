#pragma once


#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <Globals.h>


class Texture {
public:
    static Texture& getInstance();
    const sf::Texture& getTexture(TextureID textureID);

private:
    Texture() = default;
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    std::unordered_map<TextureID, sf::Texture> m_textures;
};
