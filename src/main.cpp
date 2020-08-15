#include <iostream>
#include <Event/Action.hpp>
#include <Event/ActionMap.hpp>
#include <Event/ActionTarget.hpp>
#include <Resources/ResourceHolder.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Entity/Player.hpp>

enum KeyCode{
    Top, Down ,Left ,Right
};

int main(){

    sf::RenderWindow window{sf::VideoMode(800,600),"My window"};
    sf::RectangleShape rect;
    
    gameResources::ResourceHolder::get().texture.load(1,"assets/sdds.png");

    Player::setDefaultMovements();
    Player player(sf::Vector2f(100,100),1,false);
    

   // Player player();
   /*  rect.setSize(sf::Vector2f(100,100));
    sf::Vector2f pos(100,100);
    rect.setPosition(pos); */
    
    



    /* ActionMap<int> keymap;
    Action act(sf::Keyboard::S); */
    
   /*  
    keymap.map(KeyCode::Top,Action(sf::Keyboard::W));
    keymap.map(KeyCode::Down,Action(sf::Keyboard::S));
    keymap.map(KeyCode::Right,Action(sf::Keyboard::D));
    keymap.map(KeyCode::Left,Action(sf::Keyboard::A));
    
    ActionTarget<int> target(keymap);

    target.bind(KeyCode::Down,[&pos](const sf::Event&){pos.y+=.1f;});
    target.bind(KeyCode::Top,[&pos](const sf::Event&){pos.y-=.1f;});
    target.bind(KeyCode::Left,[&pos](const sf::Event&){pos.x-=.1f;});
    target.bind(KeyCode::Right,[&pos](const sf::Event&){pos.x+=.1f;}); */
    
    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
     /*    rect.setPosition(pos);
        target.processEvents(); */
        player.processEvent();
        player.update();
        window.clear();
        //window.draw(rect);
        window.draw(player);
        window.display();

    }


}