#pragma once
#include <unordered_map>
#include <stdexcept>
#include <SFML/Audio.hpp>
#include <string>
#include<memory>
#include <utility>

template<typename RESOURCE, typename IDENTIFIER = int>
class ResourceManager
{
    public:
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        ResourceManager() = default;

        template<typename ... Args>
        void load(const IDENTIFIER& id, Args&& ... args);

        RESOURCE& get(const IDENTIFIER& id) const;

    private:
        std::unordered_map<IDENTIFIER,std::unique_ptr<RESOURCE>> _map;

};

//template specialiazation
template<typename IDENTIFIER>
class ResourceManager<sf::Music,IDENTIFIER>
{
    public:
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        ResourceManager() = default;

        template<typename ... Args>
        void load(const IDENTIFIER& id, Args&& ... args);

        sf::Music& get(const IDENTIFIER& id) const;

    private:
        std::unordered_map<IDENTIFIER,std::unique_ptr<sf::Music>> _map;

};

#include "ResourceManager.tpl"
