#pragma once
#include <functional>
#include "Widget.hpp"

class TextBox : public Widget{
    public:
        TextBox(sf::Vector2f position,sf::Vector2f size,DefaultFont fontResourceID, const sf::RenderWindow& window,std::string& string);

        void processEvent(sf::Event e, const sf::RenderWindow& window) override;
        void render(sf::RenderTarget& renderer);
        void setPosition(const sf::Vector2f& pos) override;

        sf::Vector2f getSize() const;
        void setColor(sf::Color boxColor, sf::Color textColor);
        void setCharacterSize(int size);
        
    private:
        void handleClick(sf::Event e, const sf::RenderWindow& window);
        void handleTextInput(sf::Event e);

        bool isValidCharacter(unsigned char keycode);
        bool isBackspace(unsigned char keycode);

        sf::RectangleShape rectangle;
        sf::Text text;
        std::string& textString;
        bool isActive{false};

        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const{
            target.draw(rectangle);
            target.draw(text);
        }


};

