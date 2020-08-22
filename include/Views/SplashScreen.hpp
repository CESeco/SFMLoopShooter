#pragma once
#include <GUI/Widget.hpp>
#include <GUI/Button.hpp>
#include <GUI/TextBox.hpp>
#include <GUI/Text.hpp>
class SplashScreen : public sf::Drawable
{
    public:
        SplashScreen(const sf::RenderWindow& window):
        window(window),
        forHost(sf::Vector2f(300,600),sf::Vector2f(300,100),DefaultFont::comic,window),
        forClient(sf::Vector2f(700,600),sf::Vector2f(300,100),DefaultFont::comic,window)
        {
            logo.setTexture(gameResources::ResourceHolder::get().texture.get(DefaultResources::game_icon));
            logo.setPosition(sf::Vector2f(350,50));
            sf::Vector2u size = gameResources::ResourceHolder::get().texture.get(DefaultResources::game_icon).getSize();
            logo.setTextureRect(sf::IntRect(0,0,(int)size.x,(int)size.y));

            forHost.setText("Host",75,sf::Color::White);
            forHost.setBackgroundColor(sf::Color::Red,sf::Color::Green);

            forClient.setText("Client",75,sf::Color::White);
            forClient.setBackgroundColor(sf::Color::Red,sf::Color::Green);

            forHost.addFunction([&]()->void{
                isHost = true;
                firstScreen = false;
            });

            forClient.addFunction([&]()->void{
                isHost = false;
                firstScreen = false;
            });
        };
        
        //start splash screen
        void instantiate(){

        }

        void processEvent(sf::Event event){
            forHost.processEvent(event,window);
            forClient.processEvent(event,window);
        }

    private:
        
        const sf::RenderWindow& window;
        Button forHost;
        Button forClient;

        bool isHost{false};
        bool isClient{false};

        //for ServerPart
       /*  Text showIp;
        Text showPort;

        //for ClientPart
        std::string ip;
        std::string port;
        TextBox listenIp;
        TextBox listenPort;
        Button btnConnect; */





        //firstScreen is where user chooses to be host or client
        bool firstScreen{true};
        sf::Sprite logo;
        void draw(sf::RenderTarget& target,sf::RenderStates states) const{
        if(firstScreen)
            target.draw(logo);
            target.draw(forHost);
            target.draw(forClient);
        }

};