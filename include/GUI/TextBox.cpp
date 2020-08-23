#include "TextBox.hpp"

#include <iostream>
TextBox::TextBox(sf::Vector2f position,sf::Vector2f size,DefaultFont fontResourceID, const sf::RenderWindow& window,std::string& str):
Widget(position,size,fontResourceID),
textString(str)
{
    
    rectangle.setSize(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(sf::Color::Red);
    text.setFont(gameResources::ResourceHolder::get().font.get(fontResourceID));
    text.setPosition(position);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
}

void TextBox::setColor(sf::Color boxColor, sf::Color textColor){
    rectangle.setFillColor(boxColor);
    text.setFillColor(textColor);
}

void TextBox::setCharacterSize(int size){
    text.setCharacterSize(50);
}
sf::Vector2f TextBox::getSize() const{
    return size;
}


void TextBox::setPosition(const sf::Vector2f& pos){
    position = pos;
    text.setPosition(position);
    text.move(5, position.y/2.5f);
}

//is Active is bool that defines whether to input anything into the box or not
void TextBox::handleClick(sf::Event event, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);
    if(rectangle.getGlobalBounds().contains(pos.x,pos.y))
    {
        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left){
                isActive=true;
            }
        }
        
    }
    //click outside the textBox or press the escape key
    else if(event.type == sf::Event::MouseButtonPressed or event.type == sf::Event::KeyPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left or event.key.code == sf::Keyboard::Escape){
            isActive = false;
        }
    }
}
void TextBox::processEvent(sf::Event event,const sf::RenderWindow& window){
    handleClick(event,window);
    handleTextInput(event);

}
//handle chars invoked by sf::Event::TextEntered if the textBox is active

void TextBox::handleTextInput(sf::Event event)
{
    if(event.type == sf::Event::TextEntered)
    {
       
            if(isActive)
            {
                unsigned char keyCode = event.text.unicode;
            
            if(isValidCharacter(keyCode))
            {
                if(text.getGlobalBounds().width+80 <= rectangle.getGlobalBounds().width){
                    textString.push_back(keyCode);
                }
            }
           else if(isBackspace(keyCode))
           {
                if(textString.length() > 0 )
                    textString.pop_back();
           }

            }
    }
    text.setString(textString);
}

bool TextBox::isValidCharacter(unsigned char keyCode)
{
    return 
    keyCode == 46 or  // period sign(.) for ip address placement 
    keyCode >= 48 and keyCode <=57 or //Numbers
    keyCode >=65 and keyCode <= 90 or //uppercase alphabets
    keyCode >= 97 and keyCode <=122 or // lowercase alphabets
    keyCode  == 32;
}

bool TextBox::isBackspace(unsigned char keycode)
{
    return keycode == 8;
}


