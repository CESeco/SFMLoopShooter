#pragma once

#include <SFML/Window.hpp>

class Action{
    public:
         Action(const sf::Keyboard::Key& key);
         Action(const sf::Mouse::Button& button);

         bool test()const;

         bool operator==(const sf::Event& event)const;
         bool operator==(const Action& other)const;


         sf::Event _event;
    private:
            template<typename> friend class ActionTarget;
            
            
    };
