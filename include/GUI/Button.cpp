#include "Button.hpp"

Button::Button(sf::Vector2f position, sf::Vector2f size, DefaultFont fontResourceID, const sf::RenderWindow &window) : Widget(position, size, fontResourceID), window(window)
{
    //addTargets();
    rectangle.setPosition(position);
    rectangle.setSize(size);
    text.setFont(gameResources::ResourceHolder::get().font.get(fontResourceID));
    text.setPosition(position);
}
void Button::setBackgroundColor(sf::Color color, sf::Color hoverColor)
{
    rectangle.setFillColor(color);
    this->mainColor = color;
    this->hoverColor = hoverColor;
}
// Mappings first

void Button::setPosition(const sf::Vector2f &pos)
{
    position = pos;
}

sf::Vector2f Button::getSize() const
{
    return size;
}

void Button::processEvent(sf::Event event, const sf::RenderWindow &window)
{
    //getting the position of mouse
    bool insideButtonClicked{false};
    auto position = sf::Mouse::getPosition(window);
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            insideButtonClicked = true;
        }
    }
    if (rectangle.getGlobalBounds().contains(position.x, position.y))
    {
        rectangle.setFillColor(hoverColor);
        if (insideButtonClicked)
            function();
    }
    else
    {
        rectangle.setFillColor(mainColor);
    }
}

void Button::setText(const std::string &str, int size, sf::Color color)
{

    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
}
