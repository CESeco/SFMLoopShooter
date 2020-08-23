#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <GUI/Text.hpp>

class GameHost : public sf::Drawable{


    public:
        GameHost(const sf::RenderWindow& window)
        :ipaddressString(sf::Vector2f(350,200),DefaultFont::comic),
         portString(sf::Vector2f(350,400),DefaultFont::comic)
        {
            listener.listen(sf::Socket::AnyPort);
            port = listener.getLocalPort();
            portString.setText(std::string{"Port "}+std::to_string(port),100,sf::Color::Red);     
            ipaddressString.setText(std::string{"IP "}+sf::IpAddress::getLocalAddress().toString(),100,sf::Color::Red);
            std::thread h([&](){
                 //std::cout << port << std::endl;
               listen();

               listener.close();
               NetworkHandler::get().setIp(getIp());
               NetworkHandler::get().setMode(Mode::Host);
               NetworkHandler::get().setPort(getPort());
               NetworkHandler::get().setLocalPort(getLocalPort());
               NetworkHandler::get().setConnected();
            });
        h.detach();
        }

        void callHost(){
               std::cout << port << std::endl;
               listen();

               listener.close();
               NetworkHandler::get().setIp(getIp());
               NetworkHandler::get().setMode(Mode::Host);
               NetworkHandler::get().setPort(getPort());
               NetworkHandler::get().setLocalPort(getLocalPort());
               NetworkHandler::get().setConnected();
        }

        void launchThread(){


           
        }

        void listen(){
            std::string str{"cts"};
            packet << str;
            bool running{true};
            while(running){
                
                if(listener.accept(client) == sf::Socket::Done){
                     std::cout << " New client connected " << std::endl;
                     cip = client.getRemoteAddress();
                     cport = client.getRemotePort();
                     std::cout << cip << " " << cport << std::endl;
                     client.send(packet);
                     running = false;
                     //client.disconnect();
                }

            }
            
        }
        

        sf::IpAddress getIp(){
            return cip;
        }
        unsigned short getPort(){
            return cport;

        }
        unsigned short getLocalPort(){
            return port;
        }
    private:

        //thread
        

        sf::TcpListener listener;
        sf::TcpSocket client;
        sf::Packet packet;
        std::size_t received;
        sf::IpAddress ip;
        sf::IpAddress cip;
        unsigned short cport;
        unsigned short port;


        Text ipaddressString;
        Text portString;

        //some GUI related member variables

        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const{
            target.draw(ipaddressString);
            target.draw(portString);
        }

};