#include "Action.hpp"

Action::Action(const sf::Keyboard::Key& key)
{
    _event.type = sf::Event::EventType::KeyPressed;
    _event.key.code = key;

}

Action::Action(const sf::Mouse::Button& button)
{
    _event.type = sf::Event::EventType::MouseButtonPressed;
    _event.mouseButton.button = button;
}

bool Action::operator==(const sf::Event& event)const
    {
        bool res = false;

        switch(event.type)
        {
            case sf::Event::EventType::KeyPressed:
            {
                if(event.type == sf::Event::EventType::KeyPressed)
                    res = event.key.code == _event.key.code;
            }break;
            case sf::Event::EventType::KeyReleased:
            {
                if(_event.type == sf::Event::EventType::KeyPressed)
                    res = event.key.code == _event.key.code;
            }break;

            case sf::Event::EventType::MouseButtonPressed:
            {
                if(_event.type == sf::Event::EventType::MouseButtonPressed)
                    res = event.mouseButton.button == _event.mouseButton.button;
            }break;
            case sf::Event::EventType::MouseButtonReleased:
            {
                if(_event.type == sf::Event::EventType::MouseButtonPressed)
                    res = event.mouseButton.button == _event.mouseButton.button;
            }break;
            default: break;
        }
        return res;
    }

      bool Action::operator==(const Action& other)const
    {
        return  other == _event;
    }


     bool Action::test()const
    {
        bool res = false;
        if(_event.type == sf::Event::EventType::KeyPressed)
        {
                res = sf::Keyboard::isKeyPressed(_event.key.code);
        }
        else if (_event.type == sf::Event::EventType::MouseButtonPressed)
        {
                res = sf::Mouse::isButtonPressed(_event.mouseButton.button);
        }
        return res;
    }
