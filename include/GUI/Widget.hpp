#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <Resources/ResourceHolder.hpp>

class Widget : sf::Drawable{
    public:
        Widget(sf::Vector2f position, sf::Vector2f size, int fontResourceId){}
        virtual void processEvent(const sf::RenderWindow& window) = 0; 
        virtual void setPosition(const sf::Vector2f& position) = 0;
        virtual sf::Vector2f getSize() const = 0;

        
        
    protected:
        sf::RectangleShape outerShape;
        sf::Text text;
        sf::Vector2f size,position;
};
