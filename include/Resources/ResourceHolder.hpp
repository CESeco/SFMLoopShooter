#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "configuration.hpp"
#include "ResourceManager.hpp"
namespace gameResources{
class ResourceHolder {
    public:
        static ResourceHolder& get();
        enum Resource{
            Font,Texture,Music
        };
        ResourceHolder(const ResourceHolder&) = delete;
        ResourceHolder& operator=(const ResourceHolder&) = delete;
        ResourceHolder() = default;
        ResourceManager<sf::Font,DefaultFont> font;
        ResourceManager<sf::Texture,DefaultResources> texture;
        ResourceManager<sf::Music,DefaultMusic> music;

};
}