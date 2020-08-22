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

int main(){
/*     NetworkInterface interface;
    interface.call(); */  
   // Player player();
   /*  rect.setSize(sf::Vector2f(100,100));
    sf::Vector2f pos(100,100);
    rect.setPosition(pos); */
    /* std::cout << NetworkHandler::get().getIp().toString() << " " << NetworkHandler::get().getPort()  << std::endl; */
  
  

gameResources::loadDefaultResources();

    NetworkHandler::get().setIp(sf::IpAddress("192.168.0.110"));
                    NetworkHandler::get().setMode(Mode::Client);
                    NetworkHandler::get().setPort(12345);
                    NetworkHandler::get().setLocalPort(15452);  

 sf::RenderWindow window{sf::VideoMode(1200,800),"SFMLoopshooter"};
  TileContainerView tile("assets/tile.txt",window);

    
    SplashScreen splashScreen(window);

     sf::Clock clock;
     sf::Time timeElapsed = sf::Time::Zero;
     
    

    /*  std::shared_ptr<Button> button{new Button(sf::Vector2f(100,100),sf::Vector2f(500,100),DefaultFont::comic,window)};

     button->setText(std::string{"This is test"},100,sf::Color::White);
     button->setBackgroundColor(sf::Color::Green,sf::Color::Red);
     button->addFunction([]()->void{std::cout << "this is test" << std::endl;}); */
    
    /* std::string data{""};
    TextBox textBox(sf::Vector2f(100,400),sf::Vector2f(500,100),DefaultFont::comic,window,data);
    Text text(sf::Vector2f(100,600),DefaultFont::pixel);
    text.setText("This is also another test",30,sf::Color::Red); */
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
           // splashScreen.processEvent(event);
            /* button->processEvent(event,window);
            textBox.processEvent(event,window);
            if(data != ""){
                std::cout << data << std::endl;
            } */
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
       
      } 
      if(repaint){
        window.clear(sf::Color::White);

        /* window.draw(*button);
        window.draw(textBox);
        window.draw(text); */
         window.draw(tile);
        //window.draw(splashScreen);
        window.display();
      }

    }


}