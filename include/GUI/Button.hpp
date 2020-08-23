#pragma once
#include "Widget.hpp"
#include <functional>
#include <string>
#include <Event/ActionMap.hpp>
#include <Event/ActionTarget.hpp>
#include <Event/Action.hpp>

//call setMappings before instantiating this class
class Button: public Widget{
    public:
    enum ButtonEvent{
        press
    };
        Button(sf::Vector2f position,sf::Vector2f size,DefaultFont fontResourceID, const sf::RenderWindow& window);
        void setText(const std::string& str,int size,sf::Color color);

        void setBackgroundColor(sf::Color color,sf::Color hoverColor);
        
        sf::Vector2f getSize() const override;
        void setPosition(const sf::Vector2f& position) override;
        void processEvent(sf::Event event,const sf::RenderWindow& window) override;

        void addFunction(std::function<void()> func){
            function = func;
        }
        
        

    private:
        
        const sf::RenderWindow& window;
        sf::RectangleShape rectangle;
        sf::Text text;
        sf::Color mainColor;
        sf::Color hoverColor;
        std::function<void()> function;

        void draw(sf::RenderTarget& target,sf::RenderStates states) const{
            target.draw(rectangle);
            target.draw(text);
        }


        

      
        
};