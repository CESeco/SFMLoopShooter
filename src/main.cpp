#include <iostream>
#include <Event/Action.hpp>
#include <Event/ActionMap.hpp>
#include <Event/ActionTarget.hpp>
#include <Resources/ResourceHolder.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Entity/Player.hpp>
#include <Views/TileContainerView.hpp>
#include <Entity/StaticEntities.hpp>
#include <GameLogic/NetworkInterface.hpp>
#include <GameLogic/NetworkHandler.hpp>
#include <GameLogic/GameHost.hpp>
#include <SFML/Network.hpp>
enum KeyCode{
    Top, Down ,Left ,Right
};

int main(){
    
    
    sf::RectangleShape rect;
    
    gameResources::ResourceHolder::get().texture.load(1,"assets/sdds.png");
    gameResources::ResourceHolder::get().texture.load(2,"assets/tree.png");
    gameResources::ResourceHolder::get().texture.load(3,"assets/box.png");
    gameResources::ResourceHolder::get().texture.load(4,"assets/bullet.png");

   
    
  

    NetworkInterface interface;
    interface.call();  
   // Player player();
   /*  rect.setSize(sf::Vector2f(100,100));
    sf::Vector2f pos(100,100);
    rect.setPosition(pos); */
    /* std::cout << NetworkHandler::get().getIp().toString() << " " << NetworkHandler::get().getPort()  << std::endl; */
    
 /*  NetworkHandler::get().setIp(sf::IpAddress("192.168.0.110"));
                    NetworkHandler::get().setMode(Mode::Host);
                    NetworkHandler::get().setPort(12345);
                    NetworkHandler::get().setLocalPort(15452); */

 sf::RenderWindow window{sf::VideoMode(1200,800),"My window"};
 TileContainerView tile("assets/tile.txt",window);
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

    

     sf::Clock clock;
     sf::Time timeElapsed = sf::Time::Zero;
     
 
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
     /*    rect.setPosition(pos);
        target.processEvents(); */
      bool repaint = false;
      sf::Time secondPerFrame = sf::seconds(1/60.f);
      timeElapsed += clock.restart();
      
      tile.processEvents(event);
      while(timeElapsed > secondPerFrame){
        repaint = true;
        timeElapsed -= secondPerFrame;
        tile.update();
        //window.draw(rect);
      } 
      if(repaint){
        window.clear(sf::Color::White);
        window.draw(tile);
        window.display();
      }

    }


}