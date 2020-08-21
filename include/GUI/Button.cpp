#include "Button.hpp"

// Mappings first
void Button::setMappings(){
    map.map(ButtonEvent::press,Action(sf::Mouse::Left));
}

void Button::addTargets(){
    actionTarget.bind(ButtonEvent::press,[](const sf::Event&){std::cout << "button was pressed" << std::endl;});
}

Button::Button(sf::Vector2f position,sf::Vector2f size,int fontResourceID, const sf::RenderWindow& window) :
 Widget(position,size,fontResourceID),window(window),actionTarget(map)
{
    //addTargets();
    outerShape.setPosition(position);
    outerShape.setSize(size);
    text.setFont(gameResources::ResourceHolder::get().font.get(fontResourceID));

}

void Button::setPosition(const sf::Vector2f& pos){
    position = pos;
}

sf::Vector2f Button::getSize() const{
    return size;
}

void Button::processEvent(const sf::RenderWindow& window){
    actionTarget.processEvents();
}

void Button::setText(const std::string& str,int size,sf::Color color){
    
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
        //text ko setposition
    text.setStyle(sf::Text::Bold);

}


