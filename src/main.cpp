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
#include <Resources/configuration.hpp>
#include <Views/SplashScreen.hpp>

enum KeyCode{
    Top, Down ,Left ,Right
};

namespace gameResources{
    void loadDefaultResources(){
        gameResources::ResourceHolder::get().texture.load(DefaultResources::game_icon,"assets/game_icon.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::player,"assets/player.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::bullet,"assets/bullet.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::enemy_player,"assets/enemy_player.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::regular_box,"assets/box.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::regular_box,"assets/box.png");  // b
        gameResources::ResourceHolder::get().texture.load(DefaultResources::big_box_horizontal,"assets/big_box_horizontal.png"); // h
        gameResources::ResourceHolder::get().texture.load(DefaultResources::big_box_vertical,"assets/big_box_vertical.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::container_horizontal,"assets/container_horizontal.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::container_vertical,"assets/container_vertical.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::sandbag_horizontal,"assets/sandbag_horizontal.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::sandbag_vertical,"assets/sandbag_vertical.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::tree,"assets/tree.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::bush,"assets/bush.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::stone_blue,"assets/stone_blue.png");
        gameResources::ResourceHolder::get().texture.load(DefaultResources::stone_black,"assets/stone_black.png");

        //fonts
        gameResources::ResourceHolder::get().font.load(DefaultFont::comic,"assets/comic.ttf");
        gameResources::ResourceHolder::get().font.load(DefaultFont::pixel,"assets/pixel.ttf");
    
        //gunshot 
        gameResources::ResourceHolder::get().music.load(DefaultMusic::gunshot,"assets/gunShot.wav");
    }

};
void loadSplashScreen(sf::RenderWindow& window){
     
     SplashScreen splashScreen(window);
     sf::Clock clock;
     sf::Time timeElapsed = sf::Time::Zero;

    while(!NetworkHandler::get().isConnected()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(NetworkHandler::get().isConnected()){
             return;
            }
           splashScreen.processEvent(event);
        }
      //std::cout <<  "checking my presence here " << NetworkHandler::get().isConnected() <<std::endl;
      
      bool repaint = false;
      sf::Time secondPerFrame = sf::seconds(1/60.f);
      timeElapsed += clock.restart();
      
      //tile.processEvents(event);
      while(timeElapsed > secondPerFrame){
        repaint = true;
        timeElapsed -= secondPerFrame;
        // tile.update();
       
      } 
      if(repaint){
        window.clear(sf::Color::White);
        //window.draw(tile);
        window.draw(splashScreen);
        window.display();
      }

    }
}
int main(){

gameResources::loadDefaultResources();

/* 
    NetworkHandler::get().setIp(sf::IpAddress("192.168.0.110"));
                    NetworkHandler::get().setMode(Mode::Client);
                    NetworkHandler::get().setPort(12345);
                    NetworkHandler::get().setLocalPort(15452);  */ 

sf::RenderWindow window{sf::VideoMode(1200,800),"SFMLoopshooter"};

loadSplashScreen(window);
//std::cout << " i am here officially " << std::endl;
TileContainerView tile("assets/tile.txt",window);
sf::Clock clock;
sf::Time timeElapsed = sf::Time::Zero;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
   
      bool repaint = false;
      sf::Time secondPerFrame = sf::seconds(1/60.f);
      timeElapsed += clock.restart();
      
      tile.processEvents(event);
      while(timeElapsed > secondPerFrame){
        repaint = true;
        timeElapsed -= secondPerFrame;
        tile.update();
       
      } 
      if(repaint){
        window.clear(sf::Color::White);
        window.draw(tile);
        window.display();
      }

    }


}