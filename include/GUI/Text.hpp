#pragma once
#include <SFML/Graphics.hpp>
#include "Widget.hpp"

class Text : public sf::Drawable{
    public:
        Text(sf::Vector2f position,DefaultFont fontResourceID)
        
        {
            text.setFont(gameResources::ResourceHolder::get().font.get(fontResourceID));
            text.setPosition(position);
        }

        void setText(std::string textString,int characterSize,sf::Color color){
            text.setCharacterSize(characterSize);
            text.setString(textString);
            text.setFillColor(color);
        }

        void Emphasis(){
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        }
        void setPosition(sf::Vector2f position){
            position = position;
        }

    private:
        sf::Text text;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const{
            target.draw(text);
        }
};